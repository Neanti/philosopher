/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:57:16 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 14:57:17 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int				philo_do_1(t_philo *p, struct timeval *last)
{
	if (check_elapsed(p, *last) == 1)
		return (1);
	sem_wait(p->txt);
	printf("%ld philo %d is thinking\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	if (check_elapsed(p, *last) == 1)
		return (1);
	sem_wait(p->pool);
	if (check_elapsed(p, *last) == 1)
		return (1);
	sem_wait(p->txt);
	printf("%ld philo %d has taken a fork\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	sem_wait(p->pool);
	if (check_elapsed(p, *last) == 1)
		return (1);
	sem_wait(p->txt);
	printf("%ld philo %d has taken a fork\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	if (check_elapsed(p, *last) == 1)
		return (1);
	gettimeofday(last, 0);
	sem_wait(p->txt);
	printf("%ld philo %d is eating\n", elapsed(p->start), p->n + 1);
	return (0);
}

void			start_sync(struct timeval *last, t_philo *p)
{
	if (p->n == p->p->ph - 1)
	{
		gettimeofday(last, 0);
		gettimeofday(&(p->start), 0);
		sem_post(p->begin);
	}
	else
	{
		sem_wait(p->begin);
		sem_post(p->begin);
		gettimeofday(last, 0);
		gettimeofday(&(p->start), 0);
		if (p->n % 2 == 0)
			usleep(500);
	}
}

void			release_sem(t_philo *p)
{
	sem_post(p->pool);
	sem_post(p->pool);
	sem_wait(p->txt);
}

int				philo_do_body(struct timeval *last, t_philo *p)
{
	sem_post(p->txt);
	if (check_elapsed(p, *last) == 1)
		return (1);
	wrap_sleep(p->p->eat * 1000);
	if (check_elapsed(p, *last) == 1)
		return (1);
	release_sem(p);
	printf("%ld philo %d is sleeping\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	wrap_sleep(p->p->sleep * 1000);
	if (check_elapsed(p, *last) == 1)
		return (1);
	return (0);
}

void			*philo_do(void *arg)
{
	t_philo			*p;
	struct timeval	last;
	int				i;

	i = 0;
	p = (t_philo *)arg;
	start_sync(&last, p);
	while (((elapsed(last) < p->p->die)) || (i == 0))
	{
		if ((p->p->nb > 0 && i == p->p->nb))
			break ;
		if (philo_do_1(p, &last) == 1)
			break ;
		if (philo_do_body(&last, p) == 1)
			break ;
		i++;
	}
	philo_die(p);
	free(p->p);
	free(p->th);
	free(p);
	exit(0);
}
