/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:54:36 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 13:54:37 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *philo_do(void *arg)
{
    t_philo *p;
    p = (t_philo *) arg;
    struct timeval last;
    int i;

    i = 0;
    last = p->start;
    while (((elapsed(last) < p->p.die)) || (i == 0)) {
        if ((p->p.nb > 0 && i == p->p.nb))
            break;
        if(p->end->n == 1)
            break;
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d is thinking\n", elapsed(p->start),p->n + 1);
        if(p->end->n == 1)
            break;
        pthread_mutex_unlock(p->txt);
        if (p->n % 2 == 1) {
            pthread_mutex_lock(p->fr->m);
        }
        else {
            pthread_mutex_lock(p->fl->m);
        }
        if(p->end->n == 1)
            break;
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        if (p->n % 2 == 1) {
            pthread_mutex_lock(p->fl->m);
        }
        else {
            pthread_mutex_lock(p->fr->m);
        }
        if(p->end->n == 1)
            break;
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d has taken a fork\n",elapsed(p->start),p->n + 1);
        if (elapsed(last) > p->p.die)
        {
            pthread_mutex_unlock(p->txt);
            if (p->end->n == -1)
            {
                pthread_mutex_lock(p->end->m);
                p->end->n = 1;
                pthread_mutex_unlock(p->end->m);
            }
            pthread_mutex_unlock(p->fl->m);
            pthread_mutex_unlock(p->fr->m);
            pthread_mutex_unlock(p->txt);
            break;
        }
        gettimeofday(&last, 0);
        printf("%ld philo %d is eating\n", elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        if(p->end->n == 1)
            break;
        wrap_sleep(p->p.eat * 1000);
        if(p->end->n == 1)
            break;
        pthread_mutex_unlock(p->fr->m);
        pthread_mutex_unlock(p->fl->m);
        pthread_mutex_lock(p->txt);
        printf("%ld philo %d is sleeping\n", elapsed(p->start),p->n + 1);
        pthread_mutex_unlock(p->txt);
        wrap_sleep(p->p.sleep * 1000);
        if(p->end->n == 1)
            break;
        i++;
    }
    pthread_mutex_unlock(p->fl->m);
    pthread_mutex_unlock(p->fr->m);
    pthread_mutex_lock(p->txt);
    printf("%ld philo %d died bc %ld||%d AND %d\n", elapsed(p->start),p->n + 1, elapsed(last), p->p.die, i);
    pthread_mutex_unlock(p->txt);
    if (p->end->n == -1)
    {
        pthread_mutex_lock(p->end->m);
        p->end->n = 0;
        pthread_mutex_unlock(p->end->m);
    }
    return (void*)p;
}

int main(int ac, char **av)
{
    int i;
    t_param_philo *arg;
    t_philo *p;
    t_forks *fl;
    t_forks *fr;
    t_forks *last;
    t_forks *end;
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
    if (!(t_list = malloc(sizeof(pthread_t) * arg->ph)))
        return error_malloc();
    if (!(txt = malloc(sizeof(pthread_mutex_t))))
        return error_malloc();
    pthread_mutex_init(txt, 0);
    i = 0;
    last = init_forks(arg->ph - 1);
    end = init_forks(-1);
    fr = last;
    gettimeofday(&start, NULL);
    while(i < arg->ph)
    {
        if (i == arg->ph - 1) {
            if (!(p = init_philo(arg, i, last, fr, txt, start, end)))
                return error_malloc();
        }
        else if (i == 0) {
            fl = init_forks(i);
            if (!(p = init_philo(arg, i, fl, last, txt, start, end)))
                return error_malloc();

        }
        else
        {
            fl = init_forks(i);
            if (!(p = init_philo(arg, i, fl, fr, txt, start, end)))
                return error_malloc();

        }
        fr = fl;
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
}
