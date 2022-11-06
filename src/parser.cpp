/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:56:36 by AleXwern          #+#    #+#             */
/*   Updated: 2022/11/07 00:21:37 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xenoreader.hpp"

const size_t	NUM_THREADS = 20;

void	*parser(void *dat)
{
	uint32_t	nameid = *(t_uint32*)dat;
	char		name[22];

	while (nameid < 1'000'000)
	{
		sprintf(name, "maptool/%03d_%03d.evc", nameid / 1000, nameid % 1000);
		Xenoreader	rawfile(name);
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
