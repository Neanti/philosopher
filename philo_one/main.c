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

void			*philo_do(void *arg)
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
		export_one(p);
		i++;
	}
	disp_dead(p);
	return ((void *)p);
}

t_forks			**create_forks(t_param_philo *arg)
{
	t_forks **list;

	if (!(list = malloc(sizeof(t_forks*) * 4)))
		return (0);
	list[2] = init_forks(arg->ph - 1);
	list[3] = init_forks(-1);
	if (list[2] == 0 || list[3] == 0)
		return (0);
	list[1] = list[2];
	return (list);
}

t_param_philo	*arg_check(int ac, char **av)
{
	int				i;
	t_param_philo	*arg;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		if (!is_number(av[i]))
			return (0);
		i++;
	}
	if ((arg = fill_arg(av, ac)) == NULL)
		return (0);
	return (arg);
}

pthread_t		run_philo(int i, t_param_philo *arg, t_forks **f_list)
{
	t_philo *p;

	if (i == arg->ph - 1)
	{
		if (!(p = init_philo_e(arg, i, f_list)))
			return (0);
	}
	else if (i == 0)
	{
		f_list[0] = init_forks(i);
		if (!(p = init_philo_s(arg, i, f_list)))
			return (0);
	}
	else
	{
		f_list[0] = init_forks(i);
		if (!(p = init_philo_m(arg, i, f_list)))
			return (0);
	}
	f_list[1] = f_list[0];
	pthread_create(p->th, 0, philo_do, p);
	return (*(p->th));
}

int				main(int ac, char **av)
{
	int				i;
	t_param_philo	*arg;
	t_forks			**f_list;
	pthread_t		*t_list;

	i = 1;
	if (!(arg = arg_check(ac, av)))
		return (error_arg());
	if (!(t_list = malloc(sizeof(pthread_t) * arg->ph)))
		return (error_malloc());
	i = 0;
	if ((f_list = create_forks(arg)) == 0)
		return (error_malloc());
	while (i < arg->ph)
	{
		if (!(t_list[i] = run_philo(i, arg, f_list)))
			return (error_malloc());
		i++;
	}
	i = 0;
	while (i < arg->ph)
	{
		pthread_join(t_list[i], NULL);
		i++;
	}
}
