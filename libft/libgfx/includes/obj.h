/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:20:43 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/21 15:20:43 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H
# ifdef __cplusplus
extern "C" {
# endif

# include "libft.h"
# include <fcntl.h>

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_face
{
	int			v;
	int			vn;
	int			vt;
}				t_face;

/*
# is a comment
usemtl and mtllib describe the look of the model.
v is a vertex
vt is the texture coordinate of one vertex
vn is the normal of one vertex
f is a face
*/

typedef struct	s_obj
{
	t_vector	*v;
	t_vector	*vt;
	t_vector	*vn;
	t_face		*(f[3]);
	int			vertexes;
	int			vtextures;
	int			vnormals;
	char		*usemtl;
	char		*mtllib;
}				t_obj;

int			is_valid(char **s, size_t len);

# ifdef __cplusplus
}
# endif
#endif
