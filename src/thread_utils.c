/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:17 by smallem           #+#    #+#             */
/*   Updated: 2023/11/05 12:33:04 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print(char *str, t_philo *philo, t_data *data, int flag)
{
	long long	curr_time;

	pthread_mutex_lock(&data->print);
	if (philo->alive)
	{
		curr_time = get_time() - data->start_time;
		printf("%lld %d %s\n", curr_time, philo->ind, str);
		if (flag)
			printf("%lld %d is eating\n", curr_time, philo->ind);
	}
	pthread_mutex_unlock(&data->print);
}

void	get_forks(t_philo *philo, t_data *data, int rfork, int lfork)
{
	pthread_mutex_lock(&data->forks[lfork]);
	print("picked up a fork", philo, data, 0);
	pthread_mutex_lock(&data->forks[rfork]);
	print("picked up a fork", philo, data, 1);
}

void	get_forks1(t_philo *philo, t_data *data, int rfork, int lfork)
{
	pthread_mutex_lock(&data->forks[rfork]);
	print("picked up a fork", philo, data, 0);
	pthread_mutex_lock(&data->forks[lfork]);
	print("picked up a fork", philo, data, 1);
}

static int	all_ate(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		if (data->philos[i].nb_meals < data->max_meals)
			return (0);
	}
	i = -1;
	while (++i < data->nb_philos)
		data->philos[i].alive = 0;
	return (1);
}

void	rout(t_data *data, long long curr, int wait, int i)
{
	ft_usleep(data->philos[0].ttd);
	while (1)
	{
		usleep(wait);
		if (data->max_meals > 0 && all_ate(data))
			break ;
		i = -1;
		while (++i < data->nb_philos)
		{
			if (data->max_meals != -1 && data->philos[i].nb_meals
				>= data->max_meals)
				continue ;
			curr = get_time();
			if (curr - data->philos[i].last_meal > data->philos[i].ttd)
			{
				pthread_mutex_lock(&data->print);
				kill_all(data);
				printf("%lld %d died\n", curr - data->start_time, i + 1);
				pthread_mutex_unlock(&data->print);
				break ;
			}
		}
		if (i != data->nb_philos)
			break ;
	}
}
