/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:03:03 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 14:03:04 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_philo		*init_philo_s(t_param_philo *arg, int i, t_forks **f_list)
{
	t_philo			*p;
	pthread_t		*t;
	pthread_mutex_t	*txt;
	struct timeval	start;

	if (!(txt = malloc(sizeof(pthread_mutex_t))))
		return (0);
	pthread_mutex_init(txt, 0);
	if (!(p = malloc(sizeof(t_philo))))
		return (0);
	if (!(t = malloc(sizeof(pthread_t))))
		return (0);
	p->p = *arg;
	p->n = i;
	p->th = t;
	p->fl = f_list[0];
	p->fr = f_list[2];
	p->txt = txt;
	gettimeofday(&start, 0);
	p->start = start;
	p->end = f_list[3];
	return (p);
}

t_philo		*init_philo_m(t_param_philo *arg, int i, t_forks **f_list)
{
	t_philo			*p;
	pthread_t		*t;
	pthread_mutex_t	*txt;
	struct timeval	start;

	if (!(txt = malloc(sizeof(pthread_mutex_t))))
		return (0);
	pthread_mutex_init(txt, 0);
	if (!(p = malloc(sizeof(t_philo))))
		return (0);
	if (!(t = malloc(sizeof(pthread_t))))
		return (0);
	p->p = *arg;
	p->n = i;
	p->th = t;
	p->fl = f_list[0];
	p->fr = f_list[1];
	p->txt = txt;
	gettimeofday(&start, 0);
	p->start = start;
	p->end = f_list[3];
	return (p);
}

t_philo		*init_philo_e(t_param_philo *arg, int i, t_forks **f_list)
{
	t_philo			*p;
	pthread_t		*t;
	pthread_mutex_t	*txt;
	struct timeval	start;

	if (!(txt = malloc(sizeof(pthread_mutex_t))))
		return (0);
	pthread_mutex_init(txt, 0);
	if (!(p = malloc(sizeof(t_philo))))
		return (0);
	if (!(t = malloc(sizeof(pthread_t))))
		return (0);
	p->p = *arg;
	p->n = i;
	p->th = t;
	p->fl = f_list[2];
	p->fr = f_list[1];
	p->txt = txt;
	gettimeofday(&start, 0);
	p->start = start;
	p->end = f_list[3];
	return (p);
}
