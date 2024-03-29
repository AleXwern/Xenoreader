/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isshiftjis.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:38:49 by AleXwern          #+#    #+#             */
/*   Updated: 2023/02/05 19:24:42 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

inline int	is_shiftjis(t_uint8 b1, t_uint8 b2)
{
	//Single-byte kanji
	if (b1 >= 0xA1 && b1 <= 0xDF)
		return (1);
	//double byte kanji
	// This is definitely not how it's done but it's accurate enough
	if ((b1 >= 0x81 && b1 <= 0x9F) || (b1 >= 0xE0 && b1 <= 0xFC))
	{
		if ((b2 >= 0x40 && b2 <= 0x7E) || (b2 >= 0x80 && b2 <= 0xFC))
			return (2);
	}
	return (ft_isprint(b1));
}

bool		is_stringJis(const char *str, u_int8_t len)
{
	for (int i = 0; i < len; i++)
	{
		int	check = is_shiftjis(str[i], str[i+1]);
		if (!check)
			return (false);
		else if (check == 2)
			i++;
	}
	return (true);
}
