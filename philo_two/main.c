#include "utils.h"

extern int errno;

philo *init_philo(param_philo *arg, int i, sem_t *pool, sem_t *txt, struct timeval start, fin *end)
{
    philo *p;
    pthread_t *t;

    if (!(p = malloc(sizeof(philo))))
        return NULL;
    if (!(t = malloc(sizeof(pthread_t))))
        return NULL;
    p->p = *arg;
    p->n = i;
    p->th = t;
    p->pool = pool;
    p->txt = txt;
    p->start = start;
    p->end = end;
    return p;
}

long elapsed(struct timeval t)
{
    struct timeval c;

    gettimeofday(&c, NULL);
    return ((c.tv_sec * 1000000 + c.tv_usec) - (t.tv_sec * 1000000 + t.tv_usec)) / 1000;
}

void wrap_sleep(long t)
{
    struct timeval v;
    struct timeval f;
    long val;

    gettimeofday(&v, NULL);
    gettimeofday(&f,NULL);
    val = (f.tv_sec * 1000000 + f.tv_usec) - (v.tv_sec * 1000000 + v.tv_usec);
    while(val < t)
    {
        usleep(50);
        gettimeofday(&f, NULL);
        val = (f.tv_sec * 1000000 + f.tv_usec) - (v.tv_sec * 1000000 + v.tv_usec);
    }
    return;
}

int time_diff(struct timeval last, struct timeval actual)
{
    return ((actual.tv_sec * 1000000 + actual.tv_usec) - (last.tv_sec * 1000000 + last.tv_usec)) / 1000;
}

void *philo_do(void *arg)
{
    philo *p;
    p = (philo *) arg;
    struct timeval last;
    int i;

    i = 0;
    last = p->start;
    if (p->n != 1)
        usleep(500);
    while (((elapsed(last) < p->p.die)) || (i == 0)) {
        if ((p->p.nb > 0 && i == p->p.nb))
            break;
        if(p->end->n == 1)
            break;
        sem_wait(p->txt);
        printf("%ld philo %d is thinking\n", elapsed(p->start),p->n + 1);
        if(p->end->n == 1)
            break;
        sem_post(p->txt);
//        printf("WAIT POO\n");
        sem_wait(p->pool);
        if(p->end->n == 1)
            break;
        sem_wait(p->txt);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        sem_post(p->txt);
        sem_wait(p->pool);
        if(p->end->n == 1)
            break;
        sem_wait(p->txt);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        if (elapsed(last) > p->p.die)
        {
            sem_post(p->txt);
            if (p->end->n == -1)
            {
                sem_wait(p->end->end);
                p->end->n = 1;
                sem_post(p->end->end);
            }
            sem_post(p->pool);
            sem_post(p->pool);
            break;
        }
        gettimeofday(&last, 0);
        printf("%ld philo %d is eating\n", elapsed(p->start),p->n + 1);
        sem_post(p->txt);
        if(p->end->n == 1)
            break;
        wrap_sleep(p->p.eat * 1000);
        if(p->end->n == 1)
            break;
        sem_post(p->pool);
        sem_post(p->pool);
        sem_wait(p->txt);
        printf("%ld philo %d is sleeping\n", elapsed(p->start),p->n + 1);
        sem_post(p->txt);
        wrap_sleep(p->p.sleep * 1000);
        if(p->end->n == 1)
            break;
        i++;
    }
    sem_post(p->pool);
    sem_post(p->pool);
    sem_wait(p->txt);
    printf("%ld philo %d died bc %ld||%d AND %d\n", elapsed(p->start),p->n + 1, elapsed(last), p->p.die, i);
    sem_post(p->txt);
    if (p->end->n == -1)
    {
        sem_wait(p->end->end);
        p->end->n = 0;
        sem_post(p->end->end);
    }
    return (void*)p;
}

int main(int ac, char **av)
{
    int i;
    param_philo *arg;
    philo *p;
    sem_t *pool;
    sem_t *endf;
    pthread_t *t_list;
    sem_t *txt;
    struct timeval start;
    fin *end;

    sem_unlink("pool");
    sem_unlink("txt");
    sem_unlink("end");
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
    if (!(t_list = malloc(sizeof(pthread_t) * arg->ph)))
        return error_malloc();
    if (!(end = malloc(sizeof(fin))))
        return error_malloc();
//    if (!(txt = malloc(sizeof(pthread_mutex_t))))
//        return error_malloc();
    txt = sem_open("txt", O_CREAT, S_IRWXU, 1);
    i = 0;
    pool = sem_open("pool", O_CREAT, S_IRWXU, arg->ph);
    printf("arg ph %d\n", arg->ph);
    sem_wait(pool);
    sem_post(pool);
    endf = sem_open("end", O_CREAT, S_IRWXU, 1);
    end->end = endf;
    end->n = -1;
    gettimeofday(&start, NULL);
    while(i < arg->ph)
    {
        if (!(p = init_philo(arg, i, pool, txt, start, end)))
                return error_malloc();
        pthread_create(p->th, 0, philo_do, p);
        t_list[i] = *(p->th);
        i++;
    }
    i = 0;
    while(i < p->p.ph)
    {
        pthread_join(t_list[i], NULL);
        i++;
    }
    sem_unlink("txt");
    sem_unlink("pool");
    sem_unlink("end");
}
