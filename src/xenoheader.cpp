/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:19:06 by AleXwern          #+#    #+#             */
/*   Updated: 2023/02/11 18:35:20 by AleXwern         ###   ########.fr       */
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

void	Xenoheader::outputFile(const char *name, const char *header)
{
	int		fd_file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int		fd_head = open(header, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd_file == -1)
		return;
	for (t_line line : data)
	{
		if (strlen(line.second) > 250)
			continue;
		write(fd_head, &line.first, sizeof(line.first));
		write(fd_file, line.second, static_cast<uint8_t>(strlen(line.second)));
		write(fd_file, "\n", 1);
	}
	close(fd_file);
	close(fd_head);
}

static char	**readFile(int fd)
{
	char	*str = NULL;
	char	buffer[BYTES_PER_READ];
	ssize_t	bytes;
	ssize_t	len = 0;

	while (true)
	{
		bytes = read(fd, buffer, BYTES_PER_READ);
		if (bytes < 1)
			break;
		str = static_cast<char*>(realloc(str, len + bytes + 1));
		memcpy(str + len, buffer, bytes);
		len += bytes;
	}
	str[len] = '\0';
	return (ft_strsplit(str, '\n'));
}

bool	Xenoheader::inputFile(const char *name, const char *header)
{
	int		fd_file = open(name, O_RDONLY);
	int		fd_head = open(header, O_RDONLY);
	ssize_t pos;
	char	**str = NULL;
	char	len;

	if (fd_file == -1)
		return (false);
	str = readFile(fd_file);
	//while (true)
	for (int i = 0; i < 255; i++)
	{
		if (read(fd_head, &pos, sizeof(pos)) != sizeof(pos) || *str == NULL)
			break;
		printf("HH\n");
		insert({pos, strdup(*str+i)});
		free(*str+i);
	}
	free(str);
	close(fd_head);
	close(fd_file);
	return (true);
}

void	Xenoheader::printDebug(void)
{
	for (t_line line : data)
	{
		std::cout << "At: " << line.first << " Line: (" << line.second << ")\n";
	}
}
