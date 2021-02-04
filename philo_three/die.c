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
