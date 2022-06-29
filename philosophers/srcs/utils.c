/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmonacho <rmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:31:39 by rmonacho          #+#    #+#             */
/*   Updated: 2022/06/29 14:46:17 by rmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2 || !n)
		return (0);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && i + 1 < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_usleep(unsigned long long time)
{
	unsigned long long	countstart;
	unsigned long long	countend;

	time = time / 1000;
	countstart = ft_gettime();
	usleep(time * 0.95 * 1000);
	countend = ft_gettime();
	while (countend - countstart < time * 1000)
	{
		usleep(500);
		countend = ft_gettime();
	}
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	ft_message(char *s, t_philo *philo, unsigned long long time)
{
	pthread_mutex_lock(&philo->lockmeal);
	if (philo->datas->maxmeals != -1
		&& philo->nbrfeast >= philo->datas->maxmeals)
	{
		pthread_mutex_unlock(&philo->lockmeal);
		return (0);
	}
	pthread_mutex_unlock(&philo->lockmeal);
	if (ft_protectstate(philo) == -1)
		return (0);
	pthread_mutex_lock(&philo->datas->msgs);
	if (philo->datas->message == 0)
	{
		pthread_mutex_unlock(&philo->datas->msgs);
		return (0);
	}
	if (ft_strncmp(s, "died", 4) == 0)
	{
		philo->datas->message = 0;
		printf("%llu %d %s\n", time / 1000, philo->nbr, s);
	}
	if (philo->datas->message != 0)
		printf("%llu %d %s\n", time / 1000, philo->nbr, s);
	pthread_mutex_unlock(&philo->datas->msgs);
	return (0);
}

unsigned long long	ft_realtime(t_philo *philo, unsigned long long time)
{
	unsigned long long	real;

	real = time - philo->datas->start;
	return (real);
}
