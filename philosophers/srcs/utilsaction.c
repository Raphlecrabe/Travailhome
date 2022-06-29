
#include "../incs/philo.h"

int ft_printout(t_philo *philo)
{
    printf("%d is out\n", philo->nbr);
    return (-1);
}

int ft_unlockfork(t_philo *philo)
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
    if (ft_protectstate(philo) == -1)
		return (-1);
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

int ft_fork2(t_philo *philo)
{
    unsigned long long	time;
    int                 checkfork;

    checkfork = 0;
    //printf("philo %d is stuck protectstate fork2\n", philo->nbr);
    if (ft_protectstate(philo) == -1)
		return (-1);
    //printf("philo %d is stuck fork2\n", philo->nbr);
	if (philo->nbr == 1)
    {
        while (checkfork == 0)
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
            if (ft_protectstate(philo) == -1)
			    return (-1);
        }
    }
	if (philo->nbr != 1)
    {
        while (checkfork == 0)
    	{
           //printf("philo %d is stuck fork2\n", philo->nbr);
		    pthread_mutex_lock(
                &philo->datas->philo[philo->nbr - 2].lockfork);
            if (philo->datas->philo[philo->nbr - 2].fork == 1)
            {
                philo->datas->philo[philo->nbr - 2].fork = 0;
                checkfork = 1;
            }
            pthread_mutex_unlock(
                &philo->datas->philo[philo->nbr - 2].lockfork);
            //printf("philo %d is stuck protect fork2\n", philo->nbr);
            if (ft_protectstate(philo) == -1)
			    return (-1);
            usleep(500);
        }
    }
	time = ft_gettime();
	ft_message("has taken a fork", philo, ft_realtime(philo, time));
    return (0);
}

int ft_fork1(t_philo *philo)
{
    unsigned long long	time;
    int                 checkfork;

	checkfork = 0;
   // printf("philo %d is stuck protectstate fork1\n", philo->nbr);
	if (ft_protectstate(philo) == -1)
		return (-1);
   // printf("philo %d is stuck fork1\n", philo->nbr);
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