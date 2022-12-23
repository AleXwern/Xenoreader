/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:19:06 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/24 01:09:15 by AleXwern         ###   ########.fr       */
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
		free(data.back().second);
		data.pop_back();
	}
}

void	Xenoheader::insert(t_line line)
{
	data.push_back(line);
}

t_line	Xenoheader::get(size_t pos)
{
	return (data.at(pos));
}

size_t	Xenoheader::length(void)
{
	return (data.size());
}

void	Xenoheader::parseDataChunck(Xenoreader& xeno)
{
	ssize_t		pos;
	char		*ptr = NULL;

	while ((pos = xeno.getNextLine(ptr)) != -1)
		insert({pos, ptr});
}

void	Xenoheader::parseFile(const char *name)
{
}

void	Xenoheader::printDebug(void)
{
	for (t_line line : data)
	{
		std::cout << "At: " << line.first << " Line: (" << line.second << ")";
	}
}
