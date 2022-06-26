/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:56:33 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/26 19:22:17 by AleXwern         ###   ########.fr       */
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
		if (shouldprint && contents[i] > 1)
		{
			ft_memcpy(line, contents+i+1, contents[i]);
			line[contents[i]] = '\n';
			//write(fd, &i, sizeof(i));	//offset in file
			write(fd, line, contents[i]+1);
		}
	}
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
			contents = malloc(1);
			while (fd > 0)
			{
				ssize_t bytes = read(fd, dummy, BYTES_PER_READ);
				if (bytes < 1)
					break;
				if (!(contents = realloc(contents, filesize + bytes + 1)))
					break;
				ft_memcpy(contents + filesize, dummy, bytes);
				filesize += bytes;
			}
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
	return (NULL);
}

void	reader(void)
{
	pthread_t	threads[NUM_THREADS];
	t_uint32	id[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		id[i] = i;
		pthread_create(&threads[i], NULL, reader_thread, &id[i]);
	}
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
}

int		main(int ac, char **av)
{
	reader();
	return (0);
}
