/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 17:06:32 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/21 17:06:32 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void			read_texcoordinate(t_obj *obj, char **line)
{
	t_vector	vec;

	if (!is_valid(line, 2))
		return ;
	
}