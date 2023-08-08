/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:53:18 by rcalik            #+#    #+#             */
/*   Updated: 2023/08/08 12:53:19 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->death));
	if (philo->data->death_check)
	{
		pthread_mutex_unlock(&(philo->data->death));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->death));
	if (((gettime() - philo->data->start_t) - philo->last_eat)
		>= (philo->data->time_die))
	{
		print("died ⚰️", philo);
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	if (!print("is eating", philo))
		return (0);
	philo->last_eat = gettime() - philo->data->start_t;
	my_sleep(philo->data->time_eat);
	philo->count++;
	pthread_mutex_unlock(&(philo->data->fork[philo->num]));
	pthread_mutex_unlock(&(philo->data->fork[(philo->num + 1)
			% philo->data->num_philo]));
	pthread_mutex_lock(&(philo->data->eat));
	if (philo->count == philo->data->num_eat)
		philo->data->count++;
	if (philo->data->count == philo->data->num_philo)
	{
		pthread_mutex_unlock(&(philo->data->eat));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->eat));
	if (!print("is sleeping", philo))
		return (0);
	my_sleep(philo->data->time_sleep);
	if (!print("is thinking", philo))
		return (0);
	return (1);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->fork[philo->num]));
	if (!print("has taken a fork", philo))
		return (0);
	if (philo->data->num_philo == 1)
	{
		my_sleep(philo->data->time_die);
		pthread_mutex_unlock(&(philo->data->fork[philo->num]));
		print("died", philo);
		return (0);
	}
	pthread_mutex_lock(&(philo->data->fork[(philo->num + 1)
			% philo->data->num_philo]));
	if (!print("has taken a fork", philo))
		return (0);
	return (1);
}

void	*philo_control(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2)
		usleep(1000);
	while (death_check(philo))
	{
		if (!take_fork(philo))
			break ;
		if (death_check(philo))
		{
			if (!eating(philo))
				break ;
		}
		else
			break ;
	}
	return (NULL);
}
