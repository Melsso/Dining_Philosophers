/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:13 by smallem           #+#    #+#             */
/*   Updated: 2023/11/03 18:55:46 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("Insufficient arguments!\n"), 1);
	if (!parse_input(&data, argc, argv))
		return (printf("Invaild Arguments!\n"), 1);
	launch(&data);
	pthread_mutex_destroy(&data.print);
	i = -1;
	while (++i < data.nb_philos)
		pthread_mutex_destroy(&data.forks[i]);
	return (0);
}
