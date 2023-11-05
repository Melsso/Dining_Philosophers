/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:20 by smallem           #+#    #+#             */
/*   Updated: 2023/11/05 12:47:05 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo, t_data *data)
{
	int	rfork;
	int	lfork;

	rfork = philo->rfork;
	lfork = philo->lfork;
	if (philo->ind % 2)
	{
		get_forks(philo, data, rfork, lfork);
		philo->nb_meals++;
		ft_usleep(philo->tte);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&data->forks[rfork]);
		pthread_mutex_unlock(&data->forks[lfork]);
	}
	else
	{
		get_forks1(philo, data, rfork, lfork);
		philo->nb_meals++;
		ft_usleep(philo->tte);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&data->forks[lfork]);
		pthread_mutex_unlock(&data->forks[rfork]);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		flag;

	philo = (t_philo *)arg;
	data = philo->data;
	flag = (data->max_meals != -1);
	if (data->nb_philos != 1)
	{
		if (philo->ind % 2)
			ft_usleep(15);
		while (philo->alive)
		{
			if (flag && philo->nb_meals >= data->max_meals)
				break ;
			eat(philo, data);
			print("is sleeping", philo, data, 0);
			ft_usleep(philo->tts);
			print("is thinking", philo, data, 0);
		}
	}
	else
		print("picked up a fork", philo, data, 0);
	pthread_exit(NULL);
}

int	launch(t_data *data)
{
	int			i;
	long long	curr;
	int			wait;

	i = -1;
	data->start_time = get_time();
	while (++i < data->nb_philos)
		if (pthread_create(&data->tid[i], NULL, routine, &data->philos[i]) != 0)
			return (printf("Failed to create threads!\n"), 0);
	wait = (10000 / data->nb_philos);
	curr = 0;
	i = 0;
	rout(data, curr, wait, i);
	i = -1;
	while (++i < data->nb_philos)
		if (pthread_join(data->tid[i], NULL) != 0)
			return (printf("Failed to join threads!\n"), 0);
	return (1);
}
