/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:56:33 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/26 22:30:48 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.h"

static int	is_shiftjis(t_uint8 b1, t_uint8 b2)
{
	//Single-byte kanji
	if (b1 >= 0xA1 && b1 <= 0xDF)
		return (1);
	//double byte kanji
	// This is definitely not how it's done but it's accurate enough
	if (b1 >= 0x81 && b1 <= 0x9F)
	{
		if (b2 >= 0x40 && b2 <= 0xFC && b2 != 0x7f)
			return (2);
	}
	if (b1 >= 0xE0 && b1 <= 0xEF)
	{
		if (b2 >= 0x40 && b2 <= 0xFC && b2 != 0x7f)
			return (2);
	}
	return (ft_isprint(b1));
	return (0);
}

void			parsefile(t_uint8 *contents, size_t length, t_name *id)
{
	char		line[256];
	t_uint16	len;
	char		name[16];
	int			fd;
	
	sprintf(name, "out/%03d_%03d.txt", id->high, id->low);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	for (size_t i = 0; i < length; i++)
	{
		char shouldprint = 1;
		for (size_t c = 1; c < contents[i]; c++)
		{
			char val = is_shiftjis(contents[i+c], contents[i+c+1]);
			if (val == 0)
			{
				shouldprint = 0;
				break;
			}
			if (val == 2)
				c++;
		}
		if (shouldprint && contents[i] > 1 && contents[i+contents[i]+1] == 0)
		{
			ft_memcpy(line, contents+i+1, contents[i]);
			line[contents[i]] = '\n';
			//char num[13];
			//sprintf(num, "%ld\n", i);
			write(fd, &i, sizeof(i));	//offset in file
			write(fd, line, contents[i]+1);
		}
	}
}



char		*get_file_contents(int fd, size_t *filesize)
{
	t_uint8		dummy[BYTES_PER_READ];
	t_uint8		*contents;
	size_t		size;

	contents = malloc(1);
	size = 0;
	while (fd > 0)
	{
		ssize_t bytes = read(fd, dummy, BYTES_PER_READ);
		if (bytes < 1)
			break;
		if (!(contents = realloc(contents, size + bytes + 1)))
			break;
		ft_memcpy(contents + size, dummy, bytes);
		size += bytes;
	}
	*filesize = size;
	return (contents);
}

void		*reader_thread(void *dat)
{
	t_name		id;
	char		name[20];
	char		dummy[BYTES_PER_READ];
	t_uint8		*contents;
	size_t		filesize = 0;
	int			fd;

	id.high = 0;
	id.low = *(t_uint32*)dat;
	name[22] = 0;

	while (id.high < 1000)
	{
		sprintf(name, "maptool/%03d_%03d.evc", id.high, id.low);
		fd = open(name, O_RDONLY, 0);
		if (fd > 0)
		{
			contents = get_file_contents(fd, &filesize);
			parsefile(contents, filesize, &id);
			free(contents);
		}
		id.low += NUM_THREADS;
		if (id.low > 999)
		{
			id.low -= 1000;
			id.high++;
		}
		close(fd);
	}
	printf("Thread %d done!\n", *(t_uint32*)dat);
	return (NULL);
}

void			*write_thread(void *dat)
{
	char		outname[21];
	char		inname[16];
	t_name		id = {0,0};
	int			outfile, infile;
	t_uint8		*contents;
	size_t		filesize = 0;
	size_t		oldpos;
	t_line		line;
	char 		c;

	id.low = *(t_uint32*)dat;
	while (id.high < 1000)
	{
		sprintf(outname, "maptool2/%03d_%03d.evc", id.high, id.low);
		sprintf(inname, "out/%03d_%03d.txt", id.high, id.low);
		outfile = open(outname, O_RDONLY, 0);
		contents = get_file_contents(outfile, &filesize);
		close(outfile);

		outfile = open(outname, O_WRONLY | O_TRUNC, 0);
		infile = open(inname, O_RDONLY, 0);
		if (outfile > 0)
			printf("%s\n", outname);

		oldpos = 0;
		while ((outfile | infile) > 0)
		{
			if (read(infile, &line.offset, sizeof(size_t)) < 1)
				break;
			//read(infile, &c, 1);
			line.length = 0;
			line.line = malloc(16);
			while (1)
			{
				read(infile, &c, 1);
				line.line[line.length] = c;
				//printf("dat %d -> %c\n", line.length, c);
				if (c == '\n')
					break;
				line.length++;
				if (line.length % 16 == 0)
					line.line = realloc(line.line, line.length+16);
			}
			//line.length--;
			write(outfile, contents + oldpos, line.offset - oldpos);
			write(outfile, &line.length, 1);
			write(outfile, line.line, line.length-1);
			free(line.line);
			oldpos = line.offset + line.length;
		}
		if ((outfile | infile) > 0)
		{
			write(outfile, contents + oldpos, filesize - oldpos);
		}
		free(contents);
		close(infile);
		close(outfile);
		id.low += NUM_THREADS;
		if (id.low > 999)
		{
			id.low -= 1000;
			id.high++;
		}
	}
	printf("Thread %d done!\n", *(t_uint32*)dat);
	return (NULL);
}

void	reader(char where)
{
	pthread_t	threads[NUM_THREADS];
	t_uint32	id[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		id[i] = i;
		if (where == 'r')
			pthread_create(&threads[i], NULL, reader_thread, &id[i]);
		else
			pthread_create(&threads[i], NULL, write_thread, &id[i]);
	}
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
}

int		main(int ac, char **av)
{
	if (ac < 2)
		return (1);
	if (av[1][0] == 'r')
		reader('r');
	else if (av[1][0] == 'w')
		reader('w');
	return (0);
}
