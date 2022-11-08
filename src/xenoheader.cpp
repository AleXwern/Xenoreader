/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:19:06 by AleXwern          #+#    #+#             */
/*   Updated: 2022/11/08 23:47:01 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoheader.hpp"

Xenoheader::Xenoheader(void)
{
}

Xenoheader::~Xenoheader()
{
	while (data.size() > 0)
	{
		free(data.back().line);
		data.pop_back();
	}
}

void	Xenoheader::insert(s_line line)
{
	data.push_back(line);
}

s_line	Xenoheader::get(size_t pos)
{
	return (data.at(pos));
}

size_t	Xenoheader::length(void)
{
	return (data.size());
}

void	Xenoheader::parseDataChunck(Xenoreader& xeno)
{
	insert({0, NULL});
}

void	Xenoheader::parseFile(const char *name)
{
	
}
