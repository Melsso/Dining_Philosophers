/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:34 by smallem           #+#    #+#             */
/*   Updated: 2023/11/03 16:05:52 by smallem          ###   ########.fr       */
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
	long long	last_meal;
	long long	tte;
	long long	tts;
	long long	ttd;
	int			ind;
	int			nb_meals;
	int			alive;
	int			rfork;
	int			lfork;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_t		tid[200];
	long long		start_time;
	int				alive;
	int				nb_philos;
	int				max_meals;
	pthread_mutex_t	print;
}	t_data;

int			parse_input(t_data *data, int argc, char **argv);
int			launch(t_data *data);
void		*routine(void *arg);
void		eat(t_philo *philo, t_data *data);
void		print(char *str, t_philo *philo, t_data *data, int flag);
void		ft_usleep(long long time);
long long	get_time(void);
void		kill_all(t_data *data);
void		check_meals(t_data *data);
int			ft_atoi(char *str);
void		get_forks(t_philo *philo, t_data *data, int rfork, int lfork);
void		get_forks1(t_philo *philo, t_data *data, int rfork, int lfork);
void		rout(t_data *data, long long curr, int wait, int i);

#endif