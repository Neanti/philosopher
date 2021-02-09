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
	sem_wait(p->txt);
	printf("%ld philo %d died\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
}

void			end_all(t_philo **p, sem_t **s_list, t_param_philo *arg)
{
	int i;

	i = -1;
	waitpid(-1, NULL, WUNTRACED);
	waitpid(-1, NULL, WUNTRACED);
	while (++i < arg->ph)
		kill(p[i]->th, SIGQUIT);
	i = 0;
	sem_close(p[i]->txt);
	sem_close(p[i]->end->end);
	sem_close(p[i]->pool);
	free(p[i]->end);
	while (i < arg->ph)
	{
		free(p[i]);
		i++;
	}
	free(s_list);
	free(p);
	free(arg);
	ft_unlink();
}
