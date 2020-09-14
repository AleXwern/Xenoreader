/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:42:30 by anystrom          #+#    #+#             */
/*   Updated: 2020/08/03 17:15:11 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*array;
	int		i;
	int		a;
	int		len = ft_strlen(s2);

	a = 0;
	if (!(array = (char *)malloc(sizeof(char) *
			(ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		array[a] = (char)s1[i];
		a++;
		i++;
	}
	i = 0;
	while (i < len)
	{
		array[a] = (char)s2[i];
		if (array[a] == '\0')
			array[a]++;
		a++;
		i++;
	}
	array[a] = '\0';
	return (array);
}
