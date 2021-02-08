/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:29:41 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 09:29:43 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int				is_number(char *s)
{
	int i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i != ft_strlen(s))
		return (0);
	return (1);
}

int				ft_toint(char *s)
{
	int i;
	int r;

	i = 1;
	r = 0;
	r = r + (s[0] - 48);
	while (i < ft_strlen(s))
	{
		r = (10 * r) + (s[i] - 48);
		i++;
	}
	return (r);
}

t_param_philo	*fill_arg(char **av, int ac)
{
	int				*t;
	int				i;
	t_param_philo	*p;

	if (!(p = malloc(sizeof(t_param_philo))))
		return (NULL);
	if (!(t = (int *)malloc(sizeof(int) * 5)))
		return (NULL);
	i = 1;
	while (i < ac)
	{
		t[i - 1] = ft_toint(av[i]);
		i++;
	}
	p->ph = t[0];
	p->die = t[1];
	p->eat = t[2];
	p->sleep = t[3];
	if (ac == 5)
		p->nb = -1;
	else
		p->nb = t[4];
	free(t);
	return (p);
}
