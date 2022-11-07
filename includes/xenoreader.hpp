/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xenoreader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 23:59:31 by AleXwern          #+#    #+#             */
/*   Updated: 2022/11/07 23:28:00 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XENOREADER_H
# define XENOREADER_H

#include<iostream>
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
	Xenoreader(const char *file);
	~Xenoreader(void);
	//Return a single byte from spesified location
	char	getByte(size_t pos);
	//Get the size of the EVC file
	ssize_t	getLength(void);
	//Modify the memory array at pos to be 'bytes' long
	//Must point to a valid memory area
	void	insertBytes(ssize_t pos, int8_t bytes);
	//Copy string str to spesified memory area.
	//If the string is the wrong size the area will be edited.
	void	strcpy(ssize_t pos, char *str);
	//Allocates and returns size_t position of the string and the string as reference
	size_t	getNextLine(char*& ptr);
	//Sets the line seek position to spesified position
	void	setPosition(size_t newpos);
};

#endif
