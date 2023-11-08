/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:34 by smallem           #+#    #+#             */
/*   Updated: 2023/11/08 17:53:47 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_philo
{
	long long		last_meal;
	long long		*start_time;
	long long		tte;
	long long		tts;
	long long		ttd;
	int				*max_meal;
	int				*nb_philos;
	int				ind;
	int				nb_meals;
	int				alive;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*print;
	pthread_mutex_t	alive_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	mtime_lock;
}	t_philo;

typedef struct s_data
{
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_t		tid[200];
	long long		start_time;
	int				alive;
	int				nb_philos;
	int				max_meal;
	pthread_mutex_t	print;
}	t_data;

int			parse_input(t_data *data, int argc, char **argv);
int			launch(t_data *data);
void		*routine(void *arg);
void		eat(t_philo *philo);
void		print(char *str, t_philo *philo, int flag);
void		ft_usleep(long long time);
long long	get_time(void);
void		kill_all(t_data *data);
void		check_meals(t_data *data);
int			ft_atoi(char *str);
void		rout(t_data *d, long long curr, int *k, int i);
void		ft_destroy(t_data *data, int ind);

#endif