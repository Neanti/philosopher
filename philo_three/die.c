/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:57:21 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 14:57:22 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			philo_die(t_philo *p)
{
	sem_post(p->pool);
	sem_post(p->pool);
}

void			wrap_close(t_philo **p, int i)
{
	sem_close(p[i]->txt);
	sem_close(p[i]->end->end);
	sem_close(p[i]->pool);
}

void			end_all(t_philo **p, sem_t **s_list, t_param_philo *arg)
{
	int i;

	i = -1;
	if (arg->nb > 0)
	{
		while (++i < arg->ph)
			waitpid(-1, NULL, WUNTRACED);
		exit(0);
	}
	else
	{
		sem_wait(p[0]->end_all);
		while (++i < arg->ph)
			kill(p[i]->th, SIGQUIT);
	}
	i = 0;
	wrap_close(p, i);
	free(p[i]->end);
	while (i < arg->ph)
		free(p[i++]);
	free(s_list);
	free(p);
	free(arg);
	ft_unlink();
}

int				wrap_free(t_philo *p)
{
	free(p->p);
	free(p);
	return (0);
}
