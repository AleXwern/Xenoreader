/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:56:36 by AleXwern          #+#    #+#             */
/*   Updated: 2022/11/20 00:15:16 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.hpp"
#include "xenoheader.hpp"

const size_t	NUM_THREADS = 20;

void	*parser(void *dat)
{
	uint32_t	nameid = *(t_uint32*)dat;
	char		name[22];
	size_t		pos;
	char		*line;

	while (nameid < 20)//1'000'000)
	{
		sprintf(name, "maptool/%03d_%03d.evc", nameid / 1000, nameid % 1000);
		Xenoreader	rawfile(name);
		Xenoheader	lines;
		while (true)
		{
			pos = rawfile.getNextLine(line);
			if (!pos)
				break;
			lines.insert({static_cast<ssize_t>(pos), line});
		}
		lines.printDebug();
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
