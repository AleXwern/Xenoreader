/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:17:48 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/28 18:30:33 by AleXwern         ###   ########.fr       */
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
	
	fd = open(file, O_RDWR, 0);
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
	if (offset)
		content = static_cast<char*>(realloc(content, len + offset));
	if (offset >= 0)
		memcpy(content + pos + offset + 1, content + pos + 1, len - pos - 1);
	else
		memcpy(content + pos + 1, content + pos - offset + 1, len + offset - pos - 1);
	len += offset;
	content[pos] = bytes;
}

void	Xenoreader::strcpy(ssize_t pos, const char *str)
{
	int8_t	newlen;

	if (!isValidRange(pos))
		return ;
	newlen = static_cast<uint8_t>(strlen(str));
	//printf("Lengths: %u - %u at %ld\n", (unsigned char)getByte(pos), newlen, pos);
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
			if (!is_stringJis(content+pos+1, getByte(pos)))
				continue;
			size_t	ret = pos;
			ptr = strdup(content+pos+1);
			pos += 1;//content[pos]+2;
			//printf("Str found: %u at %lu\n", (unsigned char)strlen(ptr), ret);
			return (ret);
		}
	}
	return (-1);
}

void	Xenoreader::setPosition(size_t newpos)
{
	pos = newpos;
}

bool	Xenoreader::updateFile(void)
{
	if (lseek(fd, 0, SEEK_SET) != 0)
		return (false);
	if (ftruncate(fd, 1) < 0)
		return (false);
	for (ssize_t written = 0; written < len; written += write(fd, content+written, len-written)) {}
	return (true);
}
