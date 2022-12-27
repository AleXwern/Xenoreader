/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:59:31 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/27 21:02:49 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XENOREADER_H
# define XENOREADER_H

#include <iostream>
#include "utils.hpp"
extern "C" {
	#include <string.h>
	#include <pthread.h>
	#include <dirent.h>
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include "libft.h"
}

#define BYTEHEADER		0x4d
#define BYTES_PER_READ	200

class Xenoreader
{
private:
	int		fd;
	char	*content;
	ssize_t	len;
	size_t	pos;
public:
	Xenoreader(const char *file, bool silenceOut = false);
	~Xenoreader(void);
	//Check if the file is a valid one.
	bool	isValidFile(void);
	//Return a single byte from spesified location
	char	getByte(size_t pos);
	//Get the size of the EVC file
	ssize_t	getLength(void);
	//Checks if pos is a valid string size for an area
	//The length byte must also be >0
	bool	isValidRange(size_t pos);
	//Modify the memory array at pos to be 'bytes' long
	//Must point to a valid memory area
	void	insertBytes(ssize_t pos, int8_t bytes);
	//Copy string str to spesified memory area.
	//If the string is the wrong size the area will be edited.
	void	strcpy(ssize_t pos, const char *str);
	//Allocates and returns size_t position of the string and the string as reference
	//If no string can be retrieved then -1 is returned and ptr is unchanged
	ssize_t	getNextLine(char*& ptr);
	//Sets the line seek position to spesified position
	void	setPosition(size_t newpos);
};

#endif
