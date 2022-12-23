/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:14:47 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/16 23:07:03 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XENOHEADER_HPP
#define XENOHEADER_HPP

#include "libft.h"
#include "xenoreader.hpp"
#include <vector>

struct	s_line
{
	ssize_t		offset;
	char		*line;
};

class Xenoheader
{
private:
	std::vector<s_line>	data;

	friend class Xenoreader;
public:
	Xenoheader(void);
	~Xenoheader();
	void	insert(s_line line);
	s_line	get(size_t pos);
	size_t	length(void);
	void	parseDataChunck(Xenoreader& xeno);
	void	parseFile(const char *name);
	void	printDebug(void);
};

#endif
