/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:56:36 by AleXwern          #+#    #+#             */
/*   Updated: 2022/12/26 23:53:40 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.hpp"
#include "xenoheader.hpp"

const size_t	NUM_THREADS = 20;

void	*parser(void *dat)
{
	uint32_t	nameid = *(t_uint32*)dat;
	char		name[32];

	while (nameid < 1'000'000)
	{
		sprintf(name, "maptool/%03d_%03d.evc", nameid / 1000, nameid % 1000);
		Xenoreader	rawfile(name, true);
		if (rawfile.isValidFile())
		{
			sprintf(name, "out/%03d_%03d.txt", nameid / 1000, nameid % 1000);
			Xenoheader	lines;
			lines.parseDataChunck(rawfile);
			lines.outputFile(name);
			//printf("Parsed %lu lines\n", lines.length());
		}
		nameid += NUM_THREADS;
	}
	return (NULL);
}

void	deploy_threads(void)
{
	pthread_t	threads[NUM_THREADS];
	t_uint32	id[NUM_THREADS];

	for (size_t i = 0; i < NUM_THREADS; i++)
	{
		id[i] = i;
		pthread_create(&threads[i], NULL, parser, &id[i]);
	}
	for (size_t i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);
}
