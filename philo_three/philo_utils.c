/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:46:47 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 09:46:50 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_philo		*init_philo(t_param_philo *arg, int i, sem_t **s_list, t_fin *end)
{
	t_philo			*p;

	if (!(p = malloc(sizeof(t_philo))))
		return (NULL);
	p->p = arg;
	p->n = i;
	p->pool = s_list[0];
	p->txt = s_list[2];
	p->end = end;
	p->begin = s_list[3];
	p->end_all = s_list[4];
	return (p);
}

long		elapsed(struct timeval t)
{
	struct timeval c;

	gettimeofday(&c, NULL);
	return (((c.tv_sec * 1000000 + c.tv_usec) -
	(t.tv_sec * 1000000 + t.tv_usec)) / 1000);
}

void		wrap_sleep(long t)
{
	struct timeval	v;
	struct timeval	f;
	long			val;

	gettimeofday(&v, NULL);
	gettimeofday(&f, NULL);
	val = (f.tv_sec * 1000000 + f.tv_usec) - (v.tv_sec * 1000000 + v.tv_usec);
	while (val < t)
	{
		usleep(10);
		gettimeofday(&f, NULL);
		val = (f.tv_sec * 1000000 + f.tv_usec) -
				(v.tv_sec * 1000000 + v.tv_usec);
	}
	return ;
}

int			time_diff(struct timeval last, struct timeval actual)
{
	return (((actual.tv_sec * 1000000 + actual.tv_usec) -
	(last.tv_sec * 1000000 + last.tv_usec)) / 1000);
}

int			check_elapsed(t_philo *p, struct timeval last)
{
	if (p->end->n == 1)
		return (1);
	if (elapsed(last) > p->p->die)
	{
		if (p->end->n == -1)
		{
			sem_wait(p->end->end);
			p->end->n = 1;
			sem_wait(p->txt);
			printf("%ld philo %d died\n", elapsed(p->start), p->n + 1);
			sem_post(p->txt);
			sem_post(p->end_all);
			sem_post(p->end->end);
		}
		sem_post(p->txt);
		sem_post(p->pool);
		sem_post(p->pool);
		return (1);
	}
	return (0);
}
