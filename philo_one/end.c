/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:17:00 by augay             #+#    #+#             */
/*   Updated: 2021/02/08 15:17:01 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			free_all_p1(t_philo **p, t_param_philo *arg)
{
	int i;

	i = 0;
	while (i < arg->ph)
	{
		pthread_join(*(p[i]->th), 0);
		i++;
	}
	i = 0;
	if (p[i]->end->m != 0)
	{
		free(p[i]->end->m);
		p[i]->end->m = 0;
	}
	if (p[i]->end != 0)
	{
		free(p[i]->end);
		p[i]->end = 0;
	}
}

void			free_all_loop(t_philo **p, int i)
{
	if (p[i]->fr->m != 0)
	{
		free(p[i]->fr->m);
		p[i]->fr->m = 0;
	}
	if (p[i]->fr != 0)
	{
		free(p[i]->fr);
		p[i]->fr = 0;
	}
	if (p[i]->txt != 0)
	{
		free(p[i]->txt);
		p[i]->txt = 0;
	}
	if (p[i]->th != 0)
	{
		free(p[i]->th);
		p[i]->th = 0;
	}
	if (p[i] != 0)
	{
		free(p[i]);
		p[i] = 0;
	}
}

void			free_all_p2(t_philo **p, t_param_philo *arg)
{
	int i;

	i = 0;
	while (i < arg->ph)
	{
		free_all_loop(p, i);
		i++;
	}
}

void			free_all(t_philo **p, t_param_philo *arg, t_forks **f_list)
{
	free_all_p1(p, arg);
	free_all_p2(p, arg);
	free(p);
	free(arg);
	free(f_list);
}
