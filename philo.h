/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcalik <rcalik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 12:53:24 by rcalik            #+#    #+#             */
/*   Updated: 2023/08/08 12:53:25 by rcalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				death_check;
	long			start_t;
	int				count;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	long		last_eat;
	int			num;
	int			count;
	t_data		*data;
	pthread_t	thread;
}	t_philo;

int		ft_atoi(const char *str);
void	init_data(t_data *data, int ac, char **av);
void	init_philo(t_data *data);
void	my_sleep(long long time);
int		print(char *s, t_philo *philo);
long	gettime(void);
int		death_check(t_philo *philo);
int		eating(t_philo *philo);
int		take_fork(t_philo *philo);
void	*philo_control(void *ptr);
void	free_all(t_data *data);

#endif
