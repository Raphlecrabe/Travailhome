/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:12:52 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/29 11:55:47 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_protectstate(t_philo *philo)
{
	pthread_mutex_lock(&philo->datas->protectstate);
	if (philo->datas->state == 0)
	{
		pthread_mutex_unlock(&philo->datas->protectstate);
		return (-1);
	}
	pthread_mutex_unlock(&philo->datas->protectstate);
	return (0);
}

int	ft_isok(t_philo *philo)
{
	pthread_mutex_lock(&philo->lockdead);
	if (philo->isdead == 1)
	{
		pthread_mutex_unlock(&philo->lockdead);
		return (-1);
	}
	pthread_mutex_unlock(&philo->lockdead);
	if (ft_protectstate(philo) == -1)
		return (-1);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	if (ft_fork1(philo) == -1)
		return (-1);
	if (ft_fork2(philo) == -1)
		return (-1);
	pthread_mutex_lock(&philo->locklast);
	philo->lastmeal = ft_gettime();
	pthread_mutex_unlock(&philo->locklast);
	ft_message("is eating", philo, ft_realtime(philo, philo->lastmeal));
	ft_usleep(philo->datas->time_eat);
	pthread_mutex_lock(&philo->lockmeal);
	philo->nbrfeast += 1;
	pthread_mutex_unlock(&philo->lockmeal);
	if (ft_unlockfork(philo) == -1)
		return (-1);
	return (0);
}

int	ft_thinksleep(t_philo *philo)
{
	unsigned long long	time;

	time = ft_gettime();
	ft_message("is sleeping", philo, ft_realtime(philo, time));
	ft_usleep(philo->datas->time_sleep);
	time = ft_gettime();
	ft_message("is thinking", philo, ft_realtime(philo, time));
	return (0);
}
