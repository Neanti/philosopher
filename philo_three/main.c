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

t_philo	*init_philo(t_param_philo *arg, int i, sem_t **s_list, t_fin *end, struct timeval start)
{
	t_philo			*p;
	pthread_t		*t;

	if (!(p = malloc(sizeof(t_philo))))
		return (NULL);
	if (!(t = malloc(sizeof(pthread_t))))
		return (NULL);
	p->p = *arg;
	p->n = i;
	p->th = t;
	p->pool = s_list[0];
	p->txt = s_list[2];
	p->start = start;
	p->end = end;
	return (p);
}

long	elapsed(struct timeval t)
{
	struct timeval c;

	gettimeofday(&c, NULL);
	return (((c.tv_sec * 1000000 + c.tv_usec) -
	(t.tv_sec * 1000000 + t.tv_usec)) / 1000);
}

void	wrap_sleep(long t)
{
	struct timeval	v;
	struct timeval	f;
	long			val;

	gettimeofday(&v, NULL);
	gettimeofday(&f, NULL);
	val = (f.tv_sec * 1000000 + f.tv_usec) - (v.tv_sec * 1000000 + v.tv_usec);
	while (val < t)
	{
		usleep(10);
		gettimeofday(&f, NULL);
		val = (f.tv_sec * 1000000 + f.tv_usec) -
				(v.tv_sec * 1000000 + v.tv_usec);
	}
	return ;
}

int		time_diff(struct timeval last, struct timeval actual)
{
	return (((actual.tv_sec * 1000000 + actual.tv_usec) -
	(last.tv_sec * 1000000 + last.tv_usec)) / 1000);
}

int			check_elapsed(t_philo *p, struct timeval last)
{
	if (p->end->n == 1)
		return (1);
	if (elapsed(last) > p->p.die)
	{
		if (p->end->n == -1)
		{
			sem_wait(p->end->end);
			p->end->n = 1;
			sem_post(p->end->end);
		}
		sem_post(p->txt);
		sem_post(p->pool);
		sem_post(p->pool);
		return (1);
	}
	return (0);
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
		if (check_elapsed(p, last) == 1)
			break ;
		sem_wait(p->txt);
		printf("%ld philo %d is thinking\n", elapsed(p->start), p->n + 1);
		sem_post(p->txt);
		if (check_elapsed(p, last) == 1)
			break ;
		sem_wait(p->pool);
		if (check_elapsed(p, last) == 1)
			break ;
		sem_wait(p->txt);
		printf("%ld philo %d has taken a fork\n", elapsed(p->start), p->n + 1);
		sem_post(p->txt);
		sem_wait(p->pool);
		if (check_elapsed(p, last) == 1)
			break ;
		sem_wait(p->txt);
		printf("%ld philo %d has taken a fork\n", elapsed(p->start), p->n + 1);
		sem_post(p->txt);
		if (check_elapsed(p, last) == 1)
			break ;
		gettimeofday(&last, 0);
		sem_wait(p->txt);
		printf("%ld philo %d is eating\n", elapsed(p->start), p->n + 1);
		sem_post(p->txt);
		if (check_elapsed(p, last) == 1)
			break ;
		wrap_sleep(p->p.eat * 1000);
		if (check_elapsed(p, last) == 1)
			break ;
		sem_post(p->pool);
		sem_post(p->pool);
		sem_wait(p->txt);
		printf("%ld philo %d is sleeping\n", elapsed(p->start), p->n + 1);
		sem_post(p->txt);
		wrap_sleep(p->p.sleep * 1000);
		if (check_elapsed(p, last) == 1)
			break ;
		i++;
	}
	sem_post(p->pool);
	sem_post(p->pool);
	sem_wait(p->txt);
	printf("%ld philo %d died\n", elapsed(p->start), p->n + 1);
	sem_post(p->txt);
	exit(0);
}

t_param_philo *check_arg(int ac, char **av)
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

void ft_unlink(void)
{
	sem_unlink("pool");
	sem_unlink("txt");
	sem_unlink("end");
}

sem_t **prep_sem(t_param_philo *arg)
{
	sem_t	*pool;
	sem_t	*endf;
	sem_t	*txt;
	sem_t	**s_list;

	ft_unlink();
	if (!(s_list = malloc(sizeof(sem_t*) * 3)))
		return (0);
	txt = sem_open("txt", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXU, 1);
	pool = sem_open("pool", O_CREAT, S_IRWXU, arg->ph);
	endf = sem_open("end", O_CREAT, S_IRWXU, 1);
	s_list[0] = pool;
	s_list[1] = endf;
	s_list[2] = txt;
	if (pool == 0 || endf == 0 || txt == 0)
		return (0);
	return (s_list);
}

pid_t	body_main(t_param_philo *arg, int i, sem_t **s_list, t_fin *end, struct timeval last)
{
	t_philo	*p;
	pid_t	j;
	if (!(p = init_philo(arg, i, s_list, end, last)))
		return (0);
	if ((j = fork()) == 0)
	{
		philo_do((void *)p);
	}
	else
		return (j);
	return (0);
}

int		main(int ac, char **av)
{
	int				i;
	t_param_philo	*arg;
	pid_t			*t_list;
	t_fin			*end;
	sem_t			**s_list;

	if (!(arg = check_arg(ac, av)))
		return (error_arg());
	if (!(t_list = malloc(sizeof(pid_t) * arg->ph)))
		return (error_malloc());
	if (!(end = malloc(sizeof(t_fin))))
		return (error_malloc());
	if (!(s_list = prep_sem(arg)))
		return (error_mutex());
	end->end = s_list[1];
	end->n = -1;
	i = -1;
	struct timeval last;
	gettimeofday(&last, 0);
	while (++i < arg->ph)
		if (!(t_list[i] = body_main(arg, i, s_list, end, last)))
			return (error_thread());
	i = -1;
	int j = 0;
	while (++i < arg->ph)
	{
		waitpid(-1, NULL, WUNTRACED);
		while(j < arg->ph)
		{
			kill(t_list[j], SIGABRT);
			j++;
		}
	}
	ft_unlink();
	return (0);
}
