#ifndef PHILO_H
# define PHİLO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    int     num_philo;  // toplam filozof sayisi
    int     t_die;      // filozoflarin olum suresi (milisaniye)
    int     t_eat;      // filozoflarin yemek suresi (milisaniye)
    int     t_sleep;    // filozoflarin uyku suresi
    int     must_eat;   // yemeleri gereken min sayida ogun
    int     sum_meal;   // tum filozoflarin toplam yemek sayisi
    long    start_time; // programin baslangic zamani
    int     is_died;    // herhangi bir filozofun oldugunu belirtmek icin
    pthread_mutex_t     print_lock;     // ekrana yazdirma islemlerinin senkro eden mutex
    pthread_mutex_t     *fork_lock;     // catal kilitlerinin (mutex) adreslerini tutar
}t_data;


typedef struct s_philo
{
    pthread_t   thread;     //is parcacigi kimligi
    long        last_meal;  // son yemek zamani
    int         ate;        // kac kez yemek yedi
    int         philo_id;   // filozofun kimligi
    int         left_fork;  // sol catal indexi
    int         right_fork; // sag catal indexi
    t_data      *data_of_philo; // filozofun bagli oldugu yapı
}t_philo;


//init
void	init_data(t_data *data, int ac, char **av);
t_philo	*init_philo(t_data *data);
//utils
void	check_args(t_data *data);
void	print(t_philo *philo, char *state);
long	get_time(void);
int		check_meals(t_philo *philo);
int		ft_atoi(char *str);
//dinner
void	fin_dinner(t_philo *philo, t_data *data);
void	eat_func(t_philo *philo);
void	*loop(void *ptr);
void	*monitoring(void *ptr);
void	start_dinner(t_philo *philo);


#endif
