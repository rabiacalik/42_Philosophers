#include "philo.h"


/*
filozofun sol ve sağ tarafindaki catallari kilitleyerek baslar
sonra ekrana catalları aldığını ve yemek yedigini belirtmek icin yazı yazar
usleed ile yemek yeme suresi kadar bekletilir
filozofun son yemek yedigi zaman guncellenir
catallar serbest birakilir
*/
void eat_func(t_philo *philo)
{
    pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->left_fork]);  // sol ve sag çatal kilidi aktif edilir
    pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->right_fork]);

    print(philo, "Sol catali aldi");
    print(philo, "Sag catali aldi");
    print(philo, "Yemek yiyor");

    usleep(philo->data_of_philo->t_eat * 1000);
    philo->last_meal = get_time();      // yemek bitince son yemek yedigi zamani guncelliyoruz

    pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->left_fork]); // kilitleri aciyoruz
    pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->right_fork]);

}

void *loop(void *ptr)
{
    t_philo *philo;

    philo = (t_philo *)ptr;
    if(philo->philo_id % 2 == 0) //çift numaralı filoları bir miktar bekletiyoruz ve o arada tek numaralılar koşuyor
        usleep(1600);
    
    while(philo->data_of_philo->is_died != 1)
    {
        eat_func(philo);
        print(philo, "uyuyor");
        usleep(philo->data_of_philo->t_sleep * 1000); // disaridan gelen sure milisaniye cinsi 1000 ile carpip mikrosaniye cinsi uyutuyoruz
        print(philo, "dusunuyor");      //hicbir sey yapmiyorsa geri kalan tum surede dusunur
        philo->ate++; // yedigi yemek sayacini bir arttırıyoruz
    }
    return (NULL);  
}

void *monitoring(void *ptr) // threadin gönderileceği fonksiyon parametre olarak sadece (void *) alir
{
    t_philo *philo;
    int i;

    philo = (t_philo *)ptr; //degisken turu donusumu yapilir

    while(!check_meals(philo)) // opsiyonel arguman gonderilmisse bu durum saglanmısmı diye kontrol ediyoruz
    {                          // arguman yoksa her zaman 0 donecek sonsuz dongude calısacak
        i = 0;
        while(i < philo->data_of_philo->num_philo)
        {
            if(get_time() - philo[i].last_meal > philo->data_of_philo->t_die)
            {
                print(&philo[i], "oldu");
                philo->data_of_philo->is_died = 1;
                return (NULL);
            }
            i++;
        }
        usleep(1000); // 1 ms bekleyip checkc_meals fonksiyonuna gidecek
    }
    return (NULL);
}


void start_dinner(t_philo *philo)
{
    int i;
    pthread_t monitor;      //surakli gözlemleme yapacak bir thread daha tanimliyoruz

    i = -1;
    philo->data_of_philo->start_time = get_time();  // surecin basladigi zaman
    while (++i < philo->data_of_philo->num_philo)
    {
        if (pthread_create(&philo[i].thread, NULL, &loop, &philo[i]) != 0) // 2. parametre attr, threadin özelliklerini belirtir, Null atanınca varsayılan ozellikler yuklenir
        {
            print("is parcacigi olusturulamadi");
            exit(1);
        }
    }

    pthread_create(&monitor, NULL, &monitoring, philo);  //monitor thread (iplik) i yaratıyoruz

    i = -1;

    while(++i < philo->data_of_philo->num_philo)
    {
        if(pthread_join(philo[i].thread, NULL) != 0)
        {
            print("thread olulsturulamadi");
            exit(2);
        }
    }
    pthread_join(monitor, NULL);
}
