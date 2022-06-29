/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:06:30 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/09 17:08:19 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_test(t_data *datas)
{
	unsigned long long	time;
	int					i;
	int					eat;

	i = 0;
	eat = 1;
	while (i < datas->amount)
	{
		pthread_mutex_lock(&datas->philo[i].lockmeal);
		if (datas->maxmeals != -1 && datas->philo[i].nbrfeast < datas->maxmeals)
			eat = 0;
		pthread_mutex_unlock(&datas->philo[i].lockmeal);
		pthread_mutex_lock(&datas->philo[i].locklast);
		time = ft_gettime();
		if (time - datas->philo[i].lastmeal
			>= (unsigned long long) datas->time_die)
		{
			pthread_mutex_unlock(&datas->philo[i].locklast);
			time = ft_gettime();
			ft_message("died", &datas->philo[i],
				ft_realtime(&datas->philo[i], time));
			pthread_mutex_lock(&datas->protectstate);
			datas->state = 0;
			pthread_mutex_unlock(&datas->protectstate);
			pthread_mutex_lock(&datas->philo[i].lockdead);
			datas->philo[i].isdead = 1;
			pthread_mutex_unlock(&datas->philo[i].lockdead);
			return (0);
		}
		pthread_mutex_unlock(&datas->philo[i].locklast);
		i++;
		usleep(500);
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

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->nbr % 2 == 0)
		ft_usleep(philo->datas->time_eat);
	while (1)
	{
		if (ft_isok(philo) == -1)
			return (0);
		if (ft_eat(philo) == -1)
			return (0);
		if (ft_thinksleep(philo) == -1)
			return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	*datas;

	i = 0;
	datas = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("%s\n", "error : bad arguments, pls be smart");
		return (0);
	}
	if (ft_init(&datas, argv, argc) == -1)
	{
		//freeall
		return (-1);
	}
	while (i < datas->amount)
	{
		pthread_create(&datas->philo[i].thread, NULL,
			&ft_routine, &datas->philo[i]);
		i++;
	}
	while (1)
	{
		if (ft_test(datas) == 0)
			break ;
	}
	i = 0;
	while (i < datas->amount)
	{
		pthread_join(datas->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
