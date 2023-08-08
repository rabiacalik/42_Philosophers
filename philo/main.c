/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:53:08 by rcalik            #+#    #+#             */
/*   Updated: 2023/08/08 12:53:09 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long long time)
{
	long long	now;

	now = gettime();
	while (gettime() - now < time)
		usleep(100);
}

int	print(char *s, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	pthread_mutex_lock(&(philo->data->death));
	if (philo->data->death_check)
	{
		pthread_mutex_unlock(&(philo->data->death));
		pthread_mutex_unlock(&(philo->data->fork[philo->num]));
		pthread_mutex_unlock(&(philo->data->fork[(philo->num + 1)
				% philo->data->num_philo]));
		pthread_mutex_unlock(&(philo->data->print));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->death));
	printf("%lu %d %s\n", gettime() - philo->data->start_t, philo->num + 1, s);
	if (s[0] == 'd')
	{
		pthread_mutex_lock(&(philo->data->death));
		philo->data->death_check = 1;
		pthread_mutex_unlock(&(philo->data->death));
	}
	pthread_mutex_unlock(&(philo->data->print));
	return (1);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (0);
	init_data(&data, ac, av);
	init_philo(&data);
	free_all(&data);
}
