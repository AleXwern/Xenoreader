/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:19:06 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/27 21:16:15 by AleXwern         ###   ########.fr       */
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

void	Xenoheader::outputFile(const char *name)
{
	int		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	char	linedata[0xff+10];

	if (fd == -1)
		return;
	for (t_line line : data)
	{
		ssize_t datalen = strlen(line.second) + sizeof(line.first);
		memcpy(linedata, &line.first, sizeof(line.first));
		linedata[sizeof(line.first)] = (char)strlen(line.second);
		strcpy(linedata+1+sizeof(line.first), line.second);
		linedata[datalen+1] = '\n';
		write(fd, linedata, datalen+2);
	}
	close(fd);
}

void	Xenoheader::inputFile(const char *name)
{
	int		fd = open(name, O_RDONLY);
	ssize_t pos;
	char	str[0xff];
	char	len;

	if (fd == -1)
		return;
	while (true)
	{
		if (read(fd, &pos, sizeof(pos)) < 1)
			break;
		read(fd, &len, 1);
		read(fd, str, len+1);
		str[len] = '\0';
		insert({pos, strdup(str)});
	}
	close(fd);
}

void	Xenoheader::printDebug(void)
{
	for (t_line line : data)
	{
		std::cout << "At: " << line.first << " Line: (" << line.second << ")\n";
	}
}
