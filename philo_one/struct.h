/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:54:14 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 13:54:18 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct	{
	int				ph;
	int				die;
	int				eat;
	int				sleep;
	int				nb;
}					t_param_philo;

typedef struct	{
	int				n;
	pthread_mutex_t	*m;
}					t_forks;

typedef struct	{
	int				n;
	t_param_philo	p;
	t_forks			*fl;
	t_forks			*fr;
	pthread_t		*th;
	pthread_mutex_t	*txt;
	struct timeval	start;
	t_forks			*end;
}					t_philo;

#endif
