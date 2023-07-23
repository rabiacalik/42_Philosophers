#include "philo.h"

t_philo *init_philo(t_data *data)
{
    t_philo *philo;
    int i;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->num_philo); //her filo icin yer ayiriyoruz

    while (i < data->num_philo)
    {
        philo[i].philo_id = i + 1; // filo sayisi birden baslamasi gerektigi icin +1
        philo[i].left_fork = i;     // solundaki catalin indexi filo nun bir eksigi olacak
        philo[i].right_fork = i + 1;
        philo[i].last_meal = get_time() // filo nun son yeme saatini sistemden cekiyoruz
        philo[i].ate = 0;               // kaç kez yemek yedi
        philo[i].data_of_philo = data;  // her filo için verileri ilk structtan alıyoruz
        pthread_mutex_init(&data->fork_lock[i], NULL);  // çatal kilitlerini başlatıyoruz
        i++;
    }
    i--;
    philo[i].right_fork = 0;        // son filozofun sağındaki catal herzaman 0 numara
    return (philo);
}

void init_data(t_data *data, int argc, char **argv)
{
    data->num_philo = ft_atoi(argv[1]);

    if(data->num_philo == 1)
    {
        printf("philo 1 öldü");
        exit(1);
    }

    data->t_die = ft_atoi(argv[2]);
    data->t_eat = ft_atoi(argv[3]);
    data->t_sleep = ft_atoi(argv[4]);

    data->must_eat = 0;
    if(argc == 6)
        data->must_eat = ft_atoi(argv[5]);
    
    data->is_died = 0;
    data->sum_meal = 0;

    data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->num_philo);
    pthread_mutex_init(&data->print_lock, NULL); // belirtilen mutex baslatilir
}

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philo;

    if(argc != 5 && argc != 6)
    {
        printf("Gecerli arguman gir ayoll..\n");
        exit(1);
    }

    init_data(&data, argc, argv);
    check_args(&data);
    philo = init_philo(&data);
    start_dinner(philo);
}