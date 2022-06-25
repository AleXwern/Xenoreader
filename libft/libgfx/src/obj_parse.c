/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:35:01 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/21 16:35:01 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void	parse_vertexes(t_obj *obj, char **line)
{
	if (line[0][1] == 't')
		read_texcoordinate(obj, line);
	else if (line[0][1] == 'n')
		read_vectnormal(obj, line);
	else if (line[0][1] == '\0')
		read_vertex(obj, line);
}

void	parse_faces(t_obj *obj, char **line)
{
	return;
}

void	parse_misc(t_obj *obj, char **line)
{
	if (line[0][0] == '#')
		return ;
	else if (!ft_strcmp(line[0], "mtllib"))
		obj->mtllib = ft_strdup(line[1]);
	else if (!ft_strcmp(line[0], "usemtl"))
		obj->usemtl = ft_strdup(line[1]);
}