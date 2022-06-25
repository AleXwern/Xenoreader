/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:19:04 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/21 15:19:04 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

static void	parse_file(t_obj *obj, int fd)
{
	char	*buffer;
	char	**line;

	while (get_next_line(fd, &buffer) > 0)
	{
		if (!(line = ft_strsplit(buffer, ' ')))
			return;
		free(buffer);
		if (line[0][0] == 'v')
			parse_vertexes(obj, line);
		else if (line[0][0] == 'f')
			parse_faces(obj, line);
		else
			parse_misc(obj, line);
		ft_splitfree(line);
	}
}

t_obj		read_obj(char *file)
{
	t_obj	obj;
	int		fd;

	ft_bzero(&obj, sizeof(obj));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (obj);
	parse_file(&obj, fd);
	return (obj);
}