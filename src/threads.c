/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:20 by smallem           #+#    #+#             */
/*   Updated: 2023/11/06 16:55:59 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print("picked up a fork", philo, 0);
	pthread_mutex_lock(philo->rfork);
	print("picked up a fork", philo, 1);
	pthread_mutex_lock(&philo->meal_lock);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->tte);
	pthread_mutex_lock(&philo->mtime_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mtime_lock);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	print("is sleeping", philo, 0);
	ft_usleep(philo->tts);
	print("is thinking", philo, 0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		flag;
	int		f;

	philo = (t_philo *)arg;
	flag = (*philo->max_meal != -1);
	if (*philo->nb_philos != 1)
	{
		if (philo->ind % 2)
			ft_usleep(philo->tte / 10);
		f = 1;
		while (f)
		{
			if (flag && philo->nb_meals >= *philo->max_meal)
				break ;
			eat(philo);
			pthread_mutex_lock(&philo->alive_lock);
			f = (philo->alive);
			pthread_mutex_unlock(&philo->alive_lock);
		}
	}
	else
		print("picked up a fork", philo, 0);
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
	wait = (data->philos[0].ttd / 2);
	curr = 0;
	i = 0;
	ft_usleep(data->philos[0].ttd);
	rout(data, curr, wait, i);
	i = -1;
	while (++i < data->nb_philos)
		if (pthread_join(data->tid[i], NULL) != 0)
			return (printf("Failed to join threads!\n"), 0);
	return (1);
}
