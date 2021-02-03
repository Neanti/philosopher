/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:54:36 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 13:54:37 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int				check_elapsed(t_philo *p, struct timeval last)
{
	if (p->end->n == 1)
		return (-1);
	if (elapsed(last) > p->p.die)
	{
		if (p->end->n == -1)
		{
			pthread_mutex_lock(p->end->m);
			p->end->n = 1;
			pthread_mutex_unlock(p->end->m);
		}
		return (-1);
	}
	return (1);
}

int				take_forks(t_philo *p, struct timeval last)
{
	if (check_elapsed(p, last) == -1)
		return (-1);
	if (p->n % 2 == 1)
		pthread_mutex_lock(p->fr->m);
	else
		pthread_mutex_lock(p->fl->m);
	if (check_elapsed(p, last) == -1)
		return (-1);
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d has taken a fork\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
	if (check_elapsed(p, last) == -1)
		return (-1);
	if (p->n % 2 == 1)
		pthread_mutex_lock(p->fl->m);
	else
		pthread_mutex_lock(p->fr->m);
	if (check_elapsed(p, last) == -1)
		return (-1);
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d has taken a fork\n", elapsed(p->start), p->n + 1);
	return (0);
}

void			export_one(t_philo *p)
{
	printf("%ld philo %d is eating\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
	wrap_sleep(p->p.eat * 1000);
	pthread_mutex_unlock(p->fr->m);
	pthread_mutex_unlock(p->fl->m);
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d is sleeping\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
	wrap_sleep(p->p.sleep * 1000);
}

void			disp_dead(t_philo *p)
{
	pthread_mutex_unlock(p->fl->m);
	pthread_mutex_unlock(p->fr->m);
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d died\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
}

void			disp_think(t_philo *p)
{
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d is thinking\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
}
