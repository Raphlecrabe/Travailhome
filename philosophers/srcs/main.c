/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:06:30 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/29 15:53:46 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	ft_freeall(t_data *datas)
{
	int	i;

	i = 0;
	if (datas == NULL)
		return ;
	if (datas->philo == NULL)
		return ;
	while (i < datas->amount)
	{
		pthread_mutex_destroy(&datas->philo[i].lockfork);
		pthread_mutex_destroy(&datas->philo[i].lockmeal);
		pthread_mutex_destroy(&datas->philo[i].locklast);
		pthread_mutex_destroy(&datas->philo[i].lockdead);
		i++;
	}
	pthread_mutex_destroy(&datas->msgs);
	pthread_mutex_destroy(&datas->protectstate);
	free(datas->philo);
	free(datas);
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

int	ft_initthreads(t_data **datas, char **argv, int argc)
{
	int	i;

	i = 0;
	if (ft_init(datas, argv, argc) == -1)
	{
		ft_freeall(*datas);
		return (-1);
	}
	while (i < (*datas)->amount)
	{
		pthread_create(&(*datas)->philo[i].thread, NULL,
			&ft_routine, &(*datas)->philo[i]);
		i++;
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
	if (ft_initthreads(&datas, argv, argc) == -1)
		return (-1);
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
	ft_freeall(datas);
	return (0);
}
