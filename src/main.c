/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:34:08 by AleXwern          #+#    #+#             */
/*   Updated: 2020/08/03 15:34:08 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int		writefile(unsigned char *filecont, int filelen, int fdwr)
{
	int		i;
	int		lc;

	i = 0;
	lc = 0;
	while (i < filelen)
	{
		if (ft_isprint(filecont[i]))
		{
			if (!lc)
				write(fdwr, "\t", 1);
			write(fdwr, &filecont[i], 1);
			lc = 1;
		}
		else if (filecont[i] >= 0x80)
		{
			if (!lc)
				write(fdwr, "\t", 1);
			write(fdwr, &filecont[i], 1);
			i++;
			write(fdwr, &filecont[i], 1);
			lc = 1;
		}
		else if (lc == 1)
		{
			lc = 0;
			write(fdwr, "\n", 1);
			char *num = ft_itoa(filecont[i]);
			write(fdwr, num, ft_strlen(num));
			free(num);
		}
		else
		{
			char *num = ft_itoa(filecont[i]);
			write(fdwr, num, ft_strlen(num));
			free(num);
		}
		
		i++;
		//write(fdwr, filecont, filelen);
		//i += 10000000;
	}
}

int		main(int ac, char **av)
{
	unsigned char	*filecont;
	unsigned char	*tmp;
	unsigned char	rdcont[1];
	int				filelen;
	int				filename[6];
	char			*file;
	int				fdrd;
	int				fdwr;

	ft_bzero(filename, sizeof(int) * 6);
	printf("Preparing read\n");
	while (filename[0] < 10)
	{
		file = (char*)malloc(sizeof(char) * 19);
		sprintf(file, "script/%d%d%d_%d%d%d.evc", filename[0], filename[1], filename[2], filename[3], filename[4], filename[5]);
		fdrd = open(file, O_RDONLY);
		if (fdrd == -1)
		{
			//printf("Cannot open %s.\n", file);
			free(file);
		}
		else
		{
			printf("Opened %s.\n", file);
			free(file);
			file = (char*)malloc(sizeof(char) * 23);
			sprintf(file, "script/out/%d%d%d_%d%d%d.txt", filename[0], filename[1], filename[2], filename[3], filename[4], filename[5]);
			fdwr = open(file, O_WRONLY | O_CREAT | O_EXCL, 0644);
			if (fdwr == -1)
			{
				printf("Error: File exists or bad flag\n");
			}
			else
			{
				printf("Success\n");
				filecont = ft_strnew(1);
				while (read(fdrd, rdcont, 1))
				{
					//printf("READ: %s:END:\n", rdcont);
					tmp = ft_strjoin(filecont, rdcont);
					free(filecont);
					filecont = ft_strdup(tmp);
					free(tmp);
				}
				filelen = ft_strlen(filecont);
				writefile(filecont, filelen, fdwr);
			}
			close(fdwr);
			free(file);
		}
		close(fdrd);
		filename[5]++;
		if (filename[5] > 9)
		{
			filename[5] = 0;
			filename[4]++;
		}
		if (filename[4] > 9)
		{
			filename[4] = 0;
			filename[3]++;
		}
		if (filename[3] > 9)
		{
			filename[3] = 0;
			filename[2]++;
		}
		if (filename[2] > 9)
		{
			filename[2] = 0;
			filename[1]++;
		}
		if (filename[1] > 9)
		{
			filename[1] = 0;
			filename[0]++;
		}
	}
	return (0);
}