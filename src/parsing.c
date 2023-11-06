/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:07:38 by smallem           #+#    #+#             */
/*   Updated: 2023/11/06 17:12:10 by smallem          ###   ########.fr       */
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

static void	init_philo(t_philo *philo, long long *arr, int ind, t_data *data)
{
	philo->alive = 1;
	philo->ind = ind;
	philo->ttd = arr[0];
	philo->tte = arr[1];
	philo->tts = arr[2];
	philo->last_meal = 0;
	philo->nb_meals = 0;
	philo->lfork = &data->forks[ind - 1];
	philo->print = &data->print;
	philo->start_time = &data->start_time;
	philo->max_meal = &data->max_meal;
	philo->nb_philos = &data->nb_philos;
	pthread_mutex_init(&philo->alive_lock, NULL);
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_mutex_init(&philo->mtime_lock, NULL);
}

int	parse_input(t_data *data, int argc, char **argv)
{
	long long	arr[4];

	if (!check_args(argv))
		return (0);
	data->nb_philos = ft_atoi(argv[1]);
	arr[0] = (long long)ft_atoi(argv[2]);
	arr[1] = (long long)ft_atoi(argv[3]);
	arr[2] = (long long)ft_atoi(argv[4]);
	data->max_meal = -1;
	if (argc == 6)
		data->max_meal = ft_atoi(argv[5]);
	if (data->max_meal != -1 && data->max_meal <= 0)
		return (0);
	pthread_mutex_init(&data->print, NULL);
	arr[3] = -1;
	while (++arr[3] < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[arr[3]], NULL);
		init_philo(&data->philos[arr[3]], arr, arr[3] + 1, data);
	}
	arr[3] = -1;
	while (++arr[3] < data->nb_philos - 1)
		data->philos[arr[3]].rfork = &data->forks[arr[3] + 1];
	data->philos[arr[3]].rfork = &data->forks[0];
	return (1);
}
