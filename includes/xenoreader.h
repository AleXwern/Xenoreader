/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:59:31 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/26 15:51:01 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XENOREADER_H
# define XENOREADER_H

#include <pthread.h>
#include <dirent.h>
#include <stdio.h>
#include "libft.h"

#define NUM_THREADS		20
#define BYTEHEADER		0x4d
#define BYTES_PER_READ	200

typedef struct	s_name
{
	t_uint16	high;
	t_uint16	low;
}				t_name;

#endif
