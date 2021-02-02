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

int		check_elapsed(t_philo *p, struct timeval last)
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

int		take_forks(t_philo *p, struct timeval last)
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

void	export_one(t_philo *p, struct timeval last)
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

void	disp_dead(t_philo *p)
{
	pthread_mutex_unlock(p->fl->m);
	pthread_mutex_unlock(p->fr->m);
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d died\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
}

void	disp_think(t_philo *p)
{
	pthread_mutex_lock(p->txt);
	printf("%ld philo %d is thinking\n", elapsed(p->start), p->n + 1);
	pthread_mutex_unlock(p->txt);
}

void	*philo_do(void *arg)
{
	t_philo			*p;
	struct timeval	last;
	int				i;

	i = 0;
	p = (t_philo *)arg;
	last = p->start;
	while (((elapsed(last) < p->p.die)) || (i == 0))
	{
		if ((p->p.nb > 0 && i == p->p.nb))
			break ;
		if (check_elapsed(p, last) == -1)
			break ;
		disp_think(p);
		if (check_elapsed(p, last) == -1)
			break ;
		if (take_forks(p, last) == -1)
			break ;
		gettimeofday(&last, 0);
		export_one(p, last);
		i++;
	}
	disp_dead(p);
	return ((void *)p);
}

//pthread_t *create_philo(t_param_philo *arg)
//{
//
//}

int		main(int ac, char **av)
{
	int				i;
	t_param_philo	*arg;
	t_philo			*p;
	t_forks			*fl;
	t_forks			*fr;
	t_forks			*last;
	t_forks			*end;
	pthread_t		*t_list;

	i = 1;
	if (ac < 5 || ac > 6)
		return (error_arg());
	while (i < ac)
	{
		if (!is_number(av[i]))
			return (error_arg());
		i++;
	}
	if ((arg = fill_arg(av, ac)) == NULL)
		return (error_malloc());
	if (!(t_list = malloc(sizeof(pthread_t) * arg->ph)))
		return (error_malloc());
	i = 0;
	last = init_forks(arg->ph - 1);
	end = init_forks(-1);
	fr = last;
	while (i < arg->ph)
	{
		if (i == arg->ph - 1)
		{
			if (!(p = init_philo(arg, i, last, fr, end)))
				return (error_malloc());
		}
		else if (i == 0)
		{
			fl = init_forks(i);
			if (!(p = init_philo(arg, i, fl, last, end)))
				return (error_malloc());
		}
		else
		{
			fl = init_forks(i);
			if (!(p = init_philo(arg, i, fl, fr, end)))
				return (error_malloc());
		}
		fr = fl;
		pthread_create(p->th, 0, philo_do, p);
		t_list[i] = *(p->th);
		i++;
	}
	i = 0;
	while (i < p->p.ph)
	{
		pthread_join(t_list[i], NULL);
		i++;
	}
}
