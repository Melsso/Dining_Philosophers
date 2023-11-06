/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:22 by smallem           #+#    #+#             */
/*   Updated: 2023/11/06 16:55:59 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int	a[2];

	a[0] = 0;
	a[1] = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '+' || *str == '-') && (*str++ == '-'))
		a[1] = -1;
	while (*str >= '0' && *str <= '9')
		a[0] = a[0] * 10 + (*str++ - '0');
	return (a[0] * a[1]);
}

void	ft_usleep(long long time)
{
	long long	start;
	long long	end;

	start = get_time();
	end = start + time;
	while (get_time() < end)
		usleep(50);
}

long long	get_time(void)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * (long long)1000) + (curr.tv_usec / 1000));
}

void	kill_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].alive_lock);
		data->philos[i].alive = 0;
		pthread_mutex_unlock(&data->philos[i].alive_lock);
	}
}

void	check_meals(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		if (data->philos[i].nb_meals == data->max_meal)
			data->philos[i].alive = 0;
	}
}
