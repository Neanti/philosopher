/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:29:30 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 07:29:32 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_param_philo	*check_arg(int ac, char **av)
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

sem_t			**create_sem(t_param_philo *arg)
{
	sem_t	**list;
	sem_t	*pool;
	sem_t	*txt;
	sem_t	*endf;

	if (!(list = malloc(sizeof(sem_t*) * 3)))
		return (0);
	sem_unlink("pool");
	sem_unlink("txt");
	sem_unlink("end");
	txt = sem_open("txt", O_CREAT, S_IRWXU, 1);
	pool = sem_open("pool", O_CREAT, S_IRWXU, arg->ph);
	endf = sem_open("end", O_CREAT, S_IRWXU, 1);
	list[0] = pool;
	list[1] = endf;
	list[2] = txt;
	if (list == 0 || txt == 0 || pool == 0 || endf == 0)
		return (0);
	return (list);
}

void			ft_unlink(void)
{
	sem_unlink("txt");
	sem_unlink("pool");
	sem_unlink("end");
}

t_philo			*c_philo(int i, t_param_philo *arg, sem_t **s_list, t_fin *end)
{
	t_philo		*p;

	if (!(p = init_p(arg, i, s_list, end)))
		return (0);
	pthread_create(p->th, 0, philo_do, p);
	return (p);
}

int				main(int ac, char **av)
{
	int				i;
	t_param_philo	*arg;
//	pthread_t		*t_list;
	t_fin			*end;
	sem_t			**s_list;
	t_philo			**p;

	if (!(arg = check_arg(ac, av)))
		return (error_arg());
//	if (!(t_list = malloc(sizeof(pthread_t) * arg->ph)))
//		return (error_malloc());
	if (!(p = malloc(sizeof(t_philo*) * arg->ph)))
		return (error_malloc());
	if (!(end = malloc(sizeof(t_fin))))
		return (error_malloc());
	if ((s_list = create_sem(arg)) == 0)
		return (error_mutex());
	end->end = s_list[1];
	end->n = -1;
	i = -1;
	while (++i < arg->ph)
		if (!(p[i] = c_philo(i, arg, s_list, end)))
			return (error_malloc());
	i = 0;
	while (i < arg->ph)
		pthread_join(*(p[i++]->th), NULL);
	i = 0;
	sem_close(p[i]->txt);
	sem_close(p[i]->end->end);
	sem_close(p[i]->pool);
//	free(p[i]->txt);
//	free(p[i]->end->end);
	free(p[i]->end);
//	free(p[i]->pool);
	while(i < arg->ph)
	{
		free(p[i]->th);
		free(p[i]);
		i++;
	}
	free(s_list);
	free(p);
	free(arg);
	ft_unlink();
	return (0);
}
