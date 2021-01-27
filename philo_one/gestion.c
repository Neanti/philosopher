/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:03:03 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 14:03:04 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_philo		*init_philo(t_param_philo *arg, int i, t_forks *fl, t_forks *fr, pthread_mutex_t *txt, struct timeval start, t_forks *end)
{
	t_philo		*p;
	pthread_t	*t;

	if (!(p = malloc(sizeof(t_philo))))
		return (NULL);
	if (!(t = malloc(sizeof(pthread_t))))
		return (NULL);
	p->p = *arg;
	p->n = i;
	p->th = t;
	p->fl = fl;
	p->fr = fr;
	p->txt = txt;
	p->start = start;
	p->end = end;
	return (p);
}

t_forks		*init_forks(int n)
{
	t_forks			*f;
	pthread_mutex_t	*m;

	if (!(f = malloc(sizeof(t_forks))))
		return (NULL);
	if (!(m = malloc(sizeof(pthread_mutex_t))))
		return (NULL);
	f->n = n;
	pthread_mutex_init(m, 0);
	f->m = m;
	return (f);
}

long		elapsed(struct timeval t)
{
	struct timeval c;

	gettimeofday(&c, NULL);
	return ((c.tv_sec * 1000000 + c.tv_usec) -
	(t.tv_sec * 1000000 + t.tv_usec)) / 1000;
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
		usleep(50);
		gettimeofday(&f, NULL);
		val = (f.tv_sec * 1000000 + f.tv_usec) -
				(v.tv_sec * 1000000 + v.tv_usec);
	}
}

int			time_diff(struct timeval last, struct timeval actual)
{
	return (((actual.tv_sec * 1000000 + actual.tv_usec) -
	(last.tv_sec * 1000000 + last.tv_usec)) / 1000);
}
