#include "philo.h"

int ft_atoi(char *str)
{
    int nbr;
    int i;
    int sign;

    nbr = 0;
    i = 0;
    sign = 1;

    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            sign = -1;

        i++;
    }

    if(str[i] >= '0' && str[i] <= '9')
    {
        while (str[i] >= '0' && str[i] <= '9')
            nbr = (nbr * 10) + (str[i++] - '0');
    }

    else
    {
        printf("Hata : rakam girmelisin");
        exit(1);
    }
    return (nbr * sign);
}

void check_args(t_data *data)
{
    if(data->num_philo < 1 || data->num_philo > 200 || data->t_die < 0 || \
        data->t_eat < 0 || data->t_sleep < 0)
        {
            printf("Hata : Yanlis arguman. \n");
            exit (1);

        }
}

long get_time(void)
{
    struct timeval time;        // "sys/time.h"de default tanımlı struct çağırıyoruz

    gettimeofday(&time, NULL);      // 2i arguman saat dilimini temsil ediyor. posixde artık kullanılan bir arguman degil

    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


/*
filozoflarin durumunu ekrana yazdirirken, ekrana yazdirme islemlerinin tutarli ve dogru
bir sekilde gerceklesmesini saglar. Mutex kullanarak senkronize edilen bu ekrana yazdirma
islemi, yaris kosullarina(race condition) onler ve verilerin tutarliligini korur.
*/
void print(t_philo *philo, char *state)
{
    long current_time;  // simdiki zaman

    current_time = get_time() - philo->data_of_philo->start_time // ne kadar süredir masanin basinda
    pthread_mutex_lock(&philo->data_of_philo->print_lock);      // outputlar tutarlı olsun diye kilit kullaniyoruz

    if(!philo->data_of_philo->is_died)
        print("%31d %3d %s\n", current_time, philo->philo_id, state);
    pthread_mutex_unlock(&philo->data_of_philo->print_lock);
}

int check_meals(t_philo *philo)
{
    int i;

    i = 0;
    if(philo->data_of_philo->must_eat > 0) //opsiyonel arguman girildiyse
    {
        while(i < philo->data_of_philo->num_philo)
        {
            if(philo[i].ate >= philo->data_of_philo->must_eat) //her filo yemesi gereken ogunu yemismi
                philo->data_of_philo->sum_meal++;
            i++;
        }
        if(philo->data_of_philo->sum_meal >= philo->data_of_philo->num_philo)
        {
            philo->data_of_philo->is_died = 1;
            return (1);
        }
    }
    return (0);
}