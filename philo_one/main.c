#include "utils.h"

philo *init_philo(param_philo *arg, int i, forks *fl, forks *fr, pthread_mutex_t *txt, struct timeval start)
{
    philo *p;
    pthread_t *t;

//    printf("INIT PHH l=%p r=%p\n", fl, fr);

    if (!(p = malloc(sizeof(philo))))
        return NULL;
    if (!(t = malloc(sizeof(pthread_t))))
        return NULL;
    p->p = *arg;
    p->n = i;
    p->th = t;
    p->fl = fl;
    p->fr = fr;
    p->txt = txt;
    p->start = start;
    return p;
}

forks *init_forks(int n)
{
    forks *f;
    pthread_mutex_t *m;

    if(!(f = malloc(sizeof(forks))))
        return NULL;
    if(!(m = malloc(sizeof(pthread_mutex_t))))
        return NULL;
    f->n = n;
    pthread_mutex_init(m, 0);
    f->m = m;
    return f;
}

long elapsed(struct timeval t)
{
    struct timeval c;
    long d;

    gettimeofday(&c, NULL);
    d = (c.tv_usec > t.tv_usec) ? c.tv_usec - t.tv_usec : t.tv_usec - c.tv_usec;
    return (((c.tv_sec - t.tv_sec) * 1000000  + d) / 1000);
}

void wrap_sleep(long t)
{
    struct timeval v;
    struct timeval f;

    gettimeofday(&v, NULL);
    gettimeofday(&f,NULL);
    while((((f.tv_sec * 1000000) + (f.tv_usec))
    - ((v.tv_sec * 1000000) + (v.tv_usec))) < t)
    {
        usleep(1);
        gettimeofday(&f, NULL);
    }
    return;
}

void *philo_do(void *arg)
{
    philo *p;
    p = (philo *) arg;
    unsigned int last_meal = 0;

    while (last_meal < p->p.die) {
        printf("%ld philo %d is thinking\n", elapsed(p->start),p->n + 1);
        pthread_mutex_lock(p->txt);
        pthread_mutex_lock(p->fl->m);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        pthread_mutex_lock(p->fr->m);
        printf("%ld philo %d has taken a fork\n", elapsed(p->start),p->n + 1);
        printf("%ld philo %d is eating\n", elapsed(p->start),p->n + 1);
//        usleep(p->p.eat * 1000);
        wrap_sleep(p->p.eat * 1000);
        printf("%ld philo %d END eating\n", elapsed(p->start),p->n + 1);

        last_meal = elapsed(p->start) - last_meal;
        pthread_mutex_unlock(p->fr->m);
        pthread_mutex_unlock(p->fl->m);
        printf("%ld philo %d is sleeping\n", elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        wrap_sleep(p->p.sleep * 1000);
        if (p->n == 1)
            printf("INFO: %u %d\n", last_meal, p->p.die);
    }
    printf("%ld philo %d died\n", elapsed(p->start),p->n + 1);

    return (void*)p;
}

int main(int ac, char **av)
{
    int i;
    param_philo *arg;
    philo *p;
    forks *fl;
    forks *fr;
    forks *last;
    pthread_t *t_list;
    pthread_mutex_t *txt;
    struct timeval start;

    i = 1;
    if (ac < 5 || ac > 6)
        return (error_arg());
    while(i < ac)
    {
        if (!is_number(av[i]))
            return error_arg();
        i++;
    }
    if ((arg = fill_arg(av, ac)) == NULL)
        return error_malloc();
    print_arg(arg);
    if (!(t_list = malloc(sizeof(pthread_t) * arg->ph)))
        return error_malloc();
    if (!(txt = malloc(sizeof(pthread_mutex_t))))
        return error_malloc();
    pthread_mutex_init(txt, 0);
    i = 0;
    last = init_forks(arg->ph - 1);
    fr = last;
    gettimeofday(&start, NULL);
    while(i < arg->ph)
    {
        if (i == arg->ph - 1) {
//            printf("P1\n");
            if (!(p = init_philo(arg, i, last, fr, txt, start)))
                return error_malloc();
        }
        else if (i == 0) {
//            printf("P2\n");
            fl = init_forks(i);
            if (!(p = init_philo(arg, i, fl, last, txt, start)))
                return error_malloc();

        }
        else
        {
            fl = init_forks(i);
//            printf("P3\n");
            if (!(p = init_philo(arg, i, fl, fr, txt, start)))
                return error_malloc();

        }
        fr = fl;
        pthread_create(p->th, NULL, philo_do, p);
        t_list[i] = *(p->th);
        i++;
    }
    i = 0;
    while(i < p->p.ph)
    {
        pthread_join(t_list[i], NULL);
        i++;
    }
}
