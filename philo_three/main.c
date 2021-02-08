/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:51:51 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 09:51:52 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_param_philo	*check_arg(int ac, char **av)
{
	t_param_philo	*arg;
	int				i;

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

int				ft_unlink(void)
{
	sem_unlink("pool");
	sem_unlink("txt");
	sem_unlink("end");
	sem_unlink("begin");
	return (0);
}

sem_t			**prep_sem(t_param_philo *arg)
{
	sem_t	*pool;
	sem_t	*endf;
	sem_t	*begin;
	sem_t	**s_list;

	ft_unlink();
	if (!(s_list = malloc(sizeof(sem_t*) * 4)))
		return (0);
	s_list[2] = sem_open("txt", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXU, 1);
	pool = sem_open("pool", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXU, arg->ph);
	endf = sem_open("end", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXU, 1);
	begin = sem_open("begin", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXU, 1);
	s_list[0] = pool;
	s_list[1] = endf;
	s_list[3] = begin;
	sem_wait(begin);
	if (pool == 0 || endf == 0 || s_list[2] == 0 || begin == 0)
		return (0);
	return (s_list);
}

t_philo			*body_main(t_param_philo *arg, int i, sem_t **s_list, t_fin *end)
{
	t_philo	*p;
	pid_t	j;

	if (!(p = init_philo(arg, i, s_list, end)))
		return (0);
	if ((j = fork()) == 0)
		philo_do((void *) p);
	else
	{
		p->th = j;
		return (p);
	}
	return (0);
}

int				main(int ac, char **av)
{
	int				i;
	t_param_philo	*arg;
//	pid_t			*t_list;
	t_fin			*end;
	sem_t			**s_list;
	t_philo			**p;

	if (!(arg = check_arg(ac, av)))
		return (error_arg());
	if (!(p = malloc(sizeof(t_philo*) * arg->ph)))
		return (error_malloc());
	if (!(end = malloc(sizeof(t_fin))))
		return (error_malloc());
	if (!(s_list = prep_sem(arg)))
		return (error_mutex());
	end->end = s_list[1];
	end->n = -1;
	i = -1;
	while (++i < arg->ph)
		if ((p[i] = body_main(arg, i, s_list, end)) == 0)
			return (error_thread());
	i = -1;
	while (++i < arg->ph)
		waitpid(-1, NULL, WUNTRACED);
	i = 0;
	sem_close(p[i]->txt);
	sem_close(p[i]->end->end);
	sem_close(p[i]->pool);
	free(p[i]->end);
	while(i < arg->ph)
	{
		free(p[i]);
		i++;
	}
	free(s_list);
	free(p);
	free(arg);
	ft_unlink();
	return (0);
}
