/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:54:14 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 07:37:04 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "utils.h"

struct				s_fin{
	sem_t			*end;
	int				n;
};

typedef struct s_fin	t_fin;

typedef struct	{
	int				ph;
	int				die;
	int				eat;
	int				sleep;
	int				nb;
}					t_param_philo;

typedef struct	{
	int				n;
	t_param_philo	*p;
	sem_t			*pool;
	pid_t			*th;
	sem_t			*txt;
	struct timeval	start;
	t_fin			*end;
	sem_t			*begin;
}					t_philo;

#endif
