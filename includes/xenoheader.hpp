/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoheader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:14:47 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/27 23:02:42 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XENOHEADER_HPP
#define XENOHEADER_HPP

#include "libft.h"
#include "xenoreader.hpp"
#include <vector>
#include <utility>

using t_line = std::pair<ssize_t, char*>;

class Xenoheader
{
private:
	std::vector<t_line>	data;

	friend class Xenoreader;
public:
	Xenoheader(void);
	~Xenoheader();
	void	insert(t_line);
	t_line	get(size_t pos);
	size_t	length(void);
	void	parseDataChunck(Xenoreader& xeno);
	void	outputFile(const char *name);
	bool	inputFile(const char *name);
	void	printDebug(void);
};

#endif
