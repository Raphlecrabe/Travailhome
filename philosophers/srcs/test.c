/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:49:22 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/29 14:57:46 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_test2(t_data *datas, int *eat, int *i)
{
	unsigned long long	time;

	pthread_mutex_lock(&datas->philo[*i].lockmeal);
	if (datas->maxmeals != -1 && datas->philo[*i].nbrfeast < datas->maxmeals)
		*eat = 0;
	pthread_mutex_unlock(&datas->philo[*i].lockmeal);
	pthread_mutex_lock(&datas->philo[*i].locklast);
	time = ft_gettime();
	if (time - datas->philo[*i].lastmeal
		>= (unsigned long long) datas->time_die)
	{
		pthread_mutex_unlock(&datas->philo[*i].locklast);
		time = ft_gettime();
		ft_message("died", &datas->philo[*i],
			ft_realtime(&datas->philo[*i], time));
		pthread_mutex_lock(&datas->protectstate);
		datas->state = 0;
		pthread_mutex_unlock(&datas->protectstate);
		pthread_mutex_lock(&datas->philo[*i].lockdead);
		datas->philo[*i].isdead = 1;
		pthread_mutex_unlock(&datas->philo[*i].lockdead);
		return (0);
	}
	pthread_mutex_unlock(&datas->philo[*i].locklast);
	return (1);
}

int	ft_test(t_data *datas)
{
	int					i;
	int					eat;

	i = 0;
	eat = 1;
	while (i < datas->amount)
	{
		if (ft_test2(datas, &eat, &i) == 0)
			return (0);
		usleep(500);
		i++;
	}
	if (datas->maxmeals != -1 && eat == 1)
	{
		pthread_mutex_lock(&datas->protectstate);
		datas->state = 0;
		pthread_mutex_unlock(&datas->protectstate);
		pthread_mutex_lock(&datas->msgs);
		datas->message = 0;
		pthread_mutex_unlock(&datas->msgs);
		return (0);
	}
	return (1);
}
