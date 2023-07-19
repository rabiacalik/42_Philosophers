#include "philo.h"




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
}