/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:08:17 by rmonacho          #+#    #+#             */
/*   Updated: 2022/07/19 11:54:44 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_printout(t_philo *philo)
{
	printf("%d is out\n", philo->nbr);
	return (-1);
}

int	ft_unlockfork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lockfork);
	philo->fork = 1;
	pthread_mutex_unlock(&philo->lockfork);
	if (ft_protectstate(philo) == -1)
		return (-1);
	if (philo->nbr == 1)
	{
		pthread_mutex_lock(
			&philo->datas->philo[philo->datas->amount - 1].lockfork);
		philo->datas->philo[philo->datas->amount - 1].fork = 1;
		pthread_mutex_unlock(
			&philo->datas->philo[philo->datas->amount - 1].lockfork);
	}
	if (philo->nbr != 1)
	{
		pthread_mutex_lock(
			&philo->datas->philo[philo->nbr - 2].lockfork);
		philo->datas->philo[philo->nbr - 2].fork = 1;
		pthread_mutex_unlock(
			&philo->datas->philo[philo->nbr - 2].lockfork);
	}
	return (0);
}

int	ft_fork22(t_philo *philo)
{
	int	checkfork;

	checkfork = 0;
	if (philo->nbr != 1)
	{
		while (checkfork == 0)
		{
			pthread_mutex_lock(
				&philo->datas->philo[philo->nbr - 2].lockfork);
			if (philo->datas->philo[philo->nbr - 2].fork == 1)
			{
				philo->datas->philo[philo->nbr - 2].fork = 0;
				checkfork = 1;
			}
			pthread_mutex_unlock(
				&philo->datas->philo[philo->nbr - 2].lockfork);
			usleep(500);
		}
	}
	return (0);
}

int	ft_fork2(t_philo *philo)
{
	unsigned long long	time;
	int					checkfork;

	checkfork = 0;
	if (ft_protectstate(philo) == -1)
		return (-1);
	if (philo->nbr == 1)
	{
		while (checkfork == 0 && !philo->isdead)
		{
			usleep(500);
			pthread_mutex_lock(
				&philo->datas->philo[philo->datas->amount - 1].lockfork);
			if (philo->datas->philo[philo->datas->amount - 1].fork == 1)
			{
				philo->datas->philo[philo->datas->amount - 1].fork = 0;
				checkfork = 1;
			}
			pthread_mutex_unlock(
				&philo->datas->philo[philo->datas->amount - 1].lockfork);
		}
	}
	time = ft_gettime();
	ft_message("has taken a fork", philo, ft_realtime(philo, time));
	return (0);
}

int	ft_fork1(t_philo *philo)
{
	unsigned long long	time;
	int					checkfork;

	checkfork = 0;
	while (checkfork == 0)
	{
		pthread_mutex_lock(&philo->lockfork);
		if (philo->fork == 1)
		{
			checkfork = 1;
			philo->fork = 0;
		}
		pthread_mutex_unlock(&philo->lockfork);
		if (ft_protectstate(philo) == -1)
			return (-1);
		usleep(500);
	}
	time = ft_gettime();
	ft_message("has taken a fork", philo, ft_realtime(philo, time));
	return (1);
}
