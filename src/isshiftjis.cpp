/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isshiftjis.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:38:49 by AleXwern          #+#    #+#             */
/*   Updated: 2022/11/08 23:45:31 by AleXwern         ###   ########.fr       */
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
}
