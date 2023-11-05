/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:07:38 by smallem           #+#    #+#             */
/*   Updated: 2023/11/03 14:55:35 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
		}
	}
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
		return (0);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (0);
	return (1);
}

static void	init_philo(t_philo *philo, long long *arr, int ind)
{
	philo->alive = 1;
	philo->ind = ind;
	philo->ttd = arr[0];
	philo->tte = arr[1];
	philo->tts = arr[2];
	philo->last_meal = 0;
	philo->nb_meals = 0;
	philo->rfork = ind - 1;
	philo->lfork = ind;
}

int	parse_input(t_data *data, int argc, char **argv)
{
	long long	arr[3];
	int			i;

	if (!check_args(argv))
		return (0);
	data->nb_philos = ft_atoi(argv[1]);
	arr[0] = (long long)ft_atoi(argv[2]);
	arr[1] = (long long)ft_atoi(argv[3]);
	arr[2] = (long long)ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	if (data->max_meals != -1 && data->max_meals <= 0)
		return (0);
	pthread_mutex_init(&data->print, NULL);
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		init_philo(&data->philos[i], arr, i + 1);
		data->philos[i].data = data;
	}
	data->philos[i - 1].lfork = 0;
	return (1);
}
