/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:13 by smallem           #+#    #+#             */
/*   Updated: 2023/11/08 16:17:41 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_destroy(t_data *data, int ind)
{
	int	i;

	i = -1;
	while (++i < ind)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].alive_lock);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		pthread_mutex_destroy(&data->philos[i].mtime_lock);
	}
	pthread_mutex_destroy(&data->print);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf("Insufficient arguments!\n"), 1);
	if (!parse_input(&data, argc, argv))
		return (printf("Invaild Arguments!\n"), 1);
	launch(&data);
	ft_destroy(&data, data.nb_philos);
	return (0);
}
