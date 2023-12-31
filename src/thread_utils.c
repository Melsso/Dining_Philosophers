/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:17 by smallem           #+#    #+#             */
/*   Updated: 2023/11/08 17:54:05 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print(char *str, t_philo *philo, int flag)
{
	long long	curr_time;
	int			f;

	pthread_mutex_lock(philo->print);
	pthread_mutex_lock(&philo->alive_lock);
	f = philo->alive;
	pthread_mutex_unlock(&philo->alive_lock);
	if (f)
	{
		curr_time = get_time() - *philo->start_time;
		printf("%lld %d %s\n", curr_time, philo->ind, str);
		if (flag)
			printf("%lld %d is eating\n", curr_time, philo->ind);
	}
	pthread_mutex_unlock(philo->print);
}

static void	ft_print(long long curr, t_data *data, int i)
{
	kill_all(data);
	pthread_mutex_lock(&data->print);
	printf("%lld %d died\n", curr - data->start_time, i + 1);
	pthread_mutex_unlock(&data->print);
}

void	rout(t_data *d, long long curr, int *k, int i)
{
	while (!usleep(k[3]))
	{
		k[0] = 0;
		i = -1;
		while (++i < d->nb_philos)
		{
			pthread_mutex_lock(&d->philos[i].meal_lock);
			k[1] = (d->max_meal != -1 && d->philos[i].nb_meals >= d->max_meal);
			pthread_mutex_unlock(&d->philos[i].meal_lock);
			if (k[1] && k[0]++)
				continue ;
			curr = get_time();
			pthread_mutex_lock(&d->philos[i].mtime_lock);
			k[2] = (curr - d->philos[i].last_meal >= d->philos[i].ttd);
			pthread_mutex_unlock(&d->philos[i].mtime_lock);
			if (k[2])
			{
				ft_print(curr, d, i);
				break ;
			}
		}
		if (i != d->nb_philos || k[0] == d->nb_philos)
			break ;
	}
}
