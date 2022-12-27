/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:17:48 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/27 21:03:34 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.hpp"

Xenoreader::Xenoreader(const char *file, bool silenceOut)
	: fd(0),
	content(NULL),
	len(0),
	pos(0)
{
	char	buffer[BYTES_PER_READ];
	ssize_t	bytes;
	
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		return;
	while (true)
	{
		bytes = read(fd, buffer, BYTES_PER_READ);
		if (bytes < 1)
			break;
		content = static_cast<char*>(realloc(content, len + bytes));
		memcpy(content + len, buffer, bytes);
		len += bytes;
	}
	if (!silenceOut)
		std::cout << "Read file " << file << " with " << len << " bytes.\n";
}

Xenoreader::~Xenoreader(void)
{
	if (fd < 0)
		return ;
	close(fd);
	if (content)
		free(content);
}

bool		Xenoreader::isValidFile(void)
{
	return (fd > 0);
}

char		Xenoreader::getByte(size_t pos)
{
	if (pos < len)
		return (content[pos]);
	return (-1);
}

bool		Xenoreader::isValidRange(size_t pos)
{
	if (!getByte(pos))
		return (false);
	return (!getByte(pos + getByte(pos) + 1));
}

ssize_t	Xenoreader::getLength(void)
{
	return (len);
}

void	Xenoreader::insertBytes(ssize_t pos, int8_t bytes)
{
	ssize_t	offset;

	if (!isValidRange(pos))
		return ;
	offset = bytes - content[pos];
	content = static_cast<char*>(realloc(content, len + offset));
	if (offset > 0)
		memcpy(content + pos + offset + 1, content + pos + 1, len - pos);
	else
		memcpy(content + pos + 1, content + pos - offset + 1, len + offset - pos);
	len += offset;
	content[pos] = bytes;
}

void	Xenoreader::strcpy(ssize_t pos, const char *str)
{
	int8_t	newlen;

	if (!isValidRange(pos))
		return ;
	newlen = static_cast<int8_t>(strlen(str));
	if (newlen != getByte(pos))
		insertBytes(pos, newlen);
	memcpy(content+pos+1, str, newlen);
}

ssize_t	Xenoreader::getNextLine(char*& ptr)
{
	for (; pos < len; pos++)
	{
		if (isValidRange(pos))
		{
			//Check this
			size_t	ret = pos;
			ptr = strdup(content+pos+1);
			pos += 1;//content[pos]+2;
			return (ret);
		}
	}
	return (-1);
}

void	Xenoreader::setPosition(size_t newpos)
{
	pos = newpos;
}
