/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:06:58 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/08 16:22:52 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					nbr;
	unsigned long long	lastmeal;
	int					fork;
	int					nbrfeast;
	int					isdead;
	t_data				*datas;
	pthread_mutex_t		lockfork;
	pthread_mutex_t		lockmeal;
	pthread_mutex_t		locklast;
	pthread_mutex_t		lockdead;
	pthread_t			thread;
}	t_philo;

typedef struct s_data
{
	unsigned long long	start;
	unsigned long long	current;
	int					amount;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					maxmeals;
	pthread_t			speaks;
	pthread_mutex_t		msgs;
	pthread_mutex_t		protectstate;
	t_philo				*philo;
	int					state;
}	t_data;

unsigned long long	ft_gettime(void);
int					ft_init(t_data **datas, char **argv, int argc);
int					ft_thinksleep(t_philo *philo);
int					ft_eat(t_philo *philo);
int					ft_isok(t_philo *philo);
unsigned long long	ft_realtime(t_philo *philo, unsigned long long time);
int					ft_message(char *s, t_philo *philo,
						unsigned long long time);
int					ft_atoi(const char *nptr);
void				ft_usleep(unsigned long long time);

#endif