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
    long val;

    gettimeofday(&v, NULL);
    gettimeofday(&f,NULL);
    printf("start= %ld\n",elapsed(v));

    while(val < t)
    {
        usleep(1);
        gettimeofday(&f, NULL);
        val = ((f.tv_sec * 1000000) + (f.tv_usec) - ((v.tv_sec * 1000000) + (v.tv_usec)));
    }
    printf("end = %ld\n", elapsed(v));
    return;
}

int time_diff(struct timeval last, struct timeval actual)
{
    int s;
    int m;

    s = actual.tv_sec - last.tv_sec;
    m = actual.tv_usec - last.tv_usec;
    if (s < 0)
        s *= -1;
    if (m < 0)
        m *= -1;
    return s * 1000 + m / 1000;
}

void *philo_do(void *arg)
{
    philo *p;
    p = (philo *) arg;
    struct timeval last;
    struct timeval actual;

    last = p->start;
    gettimeofday(&actual, 0);
    while (time_diff(last, actual) < p->p.die) {
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d is thinking\n", elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        if (p->n % 2 == 1) {
            pthread_mutex_lock(p->fr->m);
        }
        else {
            pthread_mutex_lock(p->fl->m);
        }
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        if (p->n % 2 == 1) {
            pthread_mutex_lock(p->fl->m);
        }
        else {
            pthread_mutex_lock(p->fr->m);
        }
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        //pthread_mutex_unlock(p->txt);
//        pthread_mutex_lock(p->fl->m);
//        pthread_mutex_lock(p->fr->m);
        printf("%ld philo %d is eating\n", elapsed(p->start),p->n + 1);
//        usleep(p->p.eat * 1000);
        pthread_mutex_unlock(p->txt);
        wrap_sleep(p->p.eat * 1000);
        //printf("%ld philo %d END eating\n", elapsed(p->start),p->n + 1);
//        if (p->n == 1)
//            printf("ELA LAST: %ld \n", elapsed(p->start));

        gettimeofday(&last, 0);
        pthread_mutex_unlock(p->fr->m);
        pthread_mutex_unlock(p->fl->m);
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d is sleeping\n", elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        wrap_sleep(p->p.sleep * 1000);
//        if (p->n == 1)
//            printf("INFO:  %d\n",  p->p.die);
        gettimeofday(&actual, 0);
    }
    pthread_mutex_lock(p->txt);
    printf("%ld philo %d died bc %d\n", elapsed(p->start),p->n + 1, time_diff(last, actual));
    pthread_mutex_unlock(p->txt);
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
