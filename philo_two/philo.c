/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 08:45:15 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 08:45:16 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int				philo_body(t_philo *p, struct timeval *last)
{
	if (check_elapsed(p, *last) == 1)
		return (1);
	sem_post(p->txt);
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
	if (check_elapsed(p, *last) == 1)
		return (1);
	gettimeofday(last, 0);
	printf("%ld philo %d is eating\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	if (check_elapsed(p, *last) == 1)
		return (1);
	wrap_sleep(p->p.eat * 1000);
	if (check_elapsed(p, *last) == 1)
		return (1);
	return (0);
}

void			end_philo(t_philo *p)
{
	sem_post(p->pool);
	sem_post(p->pool);
}

int				philo_body_2(t_philo *p, struct timeval last)
{
	sem_post(p->pool);
	sem_post(p->pool);
	sem_wait(p->txt);
	if (check_elapsed(p, last) == 1)
	{
		sem_post(p->txt);
		return (1);
	}
	printf("%ld philo %d is sleeping\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	wrap_sleep(p->p.sleep * 1000);
	return (0);
}

void			wrap(t_philo *p)
{
	sem_wait(p->txt);
	printf("%ld philo %d is thinking\n", elapsed(p->start), p->n + 1);
}

void			*philo_do(void *arg)
{
	t_philo			*p;
	struct timeval	last;
	int				i;

	p = (t_philo *)arg;
	i = 0;
	last = p->start;
	if (p->n % 2 == 0)
		usleep(200);
	while (1)
	{
		if ((p->p.nb > 0 && i == p->p.nb))
			break ;
		if (check_elapsed(p, last) == 1)
			break ;
		wrap(p);
		if (philo_body(p, &last) == 1 || philo_body_2(p, last) == 1)
			break ;
		if (check_elapsed(p, last) == 1)
			break ;
		i++;
	}
	end_philo(p);
	return ((void *)p);
}
