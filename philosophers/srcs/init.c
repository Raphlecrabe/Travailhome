/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:30:00 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/06 13:31:37 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

unsigned long long	ft_gettime(void)
{
	struct timeval		time;
	unsigned long long	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000000) + (time.tv_usec);
	return (ms);
}

void	ft_init2(t_data *datas, char **argv, int argc)
{
	datas->state = 1;
	datas->amount = ft_atoi(argv[1]);
	datas->time_die = ft_atoi(argv[2]) * 1000;
	datas->time_eat = ft_atoi(argv[3]) * 1000;
	datas->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		datas->maxmeals = ft_atoi(argv[5]);
	else
		datas->maxmeals = -1;
	datas->current = 0;
}

int	ft_init(t_data **datas, char **argv, int argc)
{
	int	i;

	i = 0;
	*datas = malloc(sizeof(t_data));
	if (*datas == NULL)
		return (-1);
	ft_init2(*datas, argv, argc);
	(*datas)->philo = malloc(sizeof(t_philo) * ((*datas)->amount));
	if ((*datas)->philo == NULL)
		return (-1);
	(*datas)->start = ft_gettime();
	pthread_mutex_init(&(*datas)->msgs, NULL);
	while (i < (*datas)->amount)
	{
		(*datas)->philo[i].nbr = i + 1;
		(*datas)->philo[i].lastmeal = (*datas)->start;
		(*datas)->philo[i].nbrfeast = 0;
		(*datas)->philo[i].fork = 0;
		pthread_mutex_init(&(*datas)->philo[i].lockfork, NULL);
		pthread_mutex_init(&(*datas)->philo[i].lockmeal, NULL);
		pthread_mutex_init(&(*datas)->philo[i].locklast, NULL);
		pthread_mutex_init(&(*datas)->philo[i].lockdead, NULL);
		(*datas)->philo[i].datas = *datas;
		(*datas)->philo[i].isdead = 0;
		i++;
	}
	return (0);
}
