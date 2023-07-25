/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:56:36 by AleXwern          #+#    #+#             */
/*   Updated: 2023/07/24 14:57:45 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.hpp"
#include "xenoheader.hpp"

const size_t	NUM_THREADS = 20;
const uint32_t	FILENUM		= 1111;//1'000'000;

void	*parser(void *dat)
{
	char		name[32];
	char		header[32];

	for (uint32_t nameid = *(t_uint32*)dat; nameid < FILENUM; nameid += NUM_THREADS)
	{
		sprintf(name, "maptool/%03d_%03d.evc", nameid / 1000, nameid % 1000);
		Xenoreader	rawfile(name, true);
		Xenoheader	lines;
		
		if (!rawfile.isValidFile())
			continue;
		sprintf(name, "out/%03d_%03d.txt", nameid / 1000, nameid % 1000);
		sprintf(header, "out/%03d_%03d.hed", nameid / 1000, nameid % 1000);
		lines.parseDataChunck(rawfile);
		if (lines.length() > 0)
			lines.outputFile(name, header);
		printf("Parsed %lu lines from %s\n", lines.length(), name);
	}
	return (NULL);
}

void	*writer(void *dat)
{
	char		name[32];
	char		header[32];

	for (uint32_t nameid = *(t_uint32*)dat; nameid < FILENUM; nameid += NUM_THREADS)
	{
		sprintf(name, "maptool2/%03d_%03d.evc", nameid / 1000, nameid % 1000);
		Xenoreader	rawfile(name, true);
		Xenoheader	lines;
		
		if (!rawfile.isValidFile())
			continue;
		sprintf(name, "out/%03d_%03d.txt", nameid / 1000, nameid % 1000);
		sprintf(header, "out/%03d_%03d.hed", nameid / 1000, nameid % 1000);
		if (!lines.inputFile(name, header))
			continue;
		for (size_t i = lines.length() - 1; i <= lines.length(); i--)
			rawfile.strcpy(lines.get(i).first, lines.get(i).second);
		//lines.printDebug();
		printf(rawfile.updateFile() ? "Success with %s!\n" : "Failure with %s!\n", name);
	}
	return (NULL);
}

void	deploy_threads(char type)
{
	pthread_t	threads[NUM_THREADS];
	t_uint32	id[NUM_THREADS];
	void		*(*thread_func)(void*);

	if (type == 'r')
		thread_func = &parser;
	else if (type == 'w')
		thread_func = &writer;
	else
		exit(1);
	for (size_t i = 0; i < NUM_THREADS; i++)
	{
		id[i] = i;
		pthread_create(&threads[i], NULL, thread_func, &id[i]);
	}
	for (size_t i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);
}
