/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:37:09 by AleXwern          #+#    #+#             */
/*   Updated: 2021/01/21 16:37:09 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size, size_t len)
{
	char	*oldptr;
	char	*newptr;
	size_t	i;

	oldptr = (char*)ptr;
	if (!(newptr = (char*)ft_memalloc(size)))
		return (NULL);
	i = 0;
	while (i < size && i < len)
	{
		newptr[i] = oldptr[i];
		i++;
	}
	if (oldptr)
		free(oldptr);
	return (newptr);
}