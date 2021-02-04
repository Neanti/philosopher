/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:45:52 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 09:46:01 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include "struct.h"

int				error_arg();
int				error_thread();
int				error_mutex();
int				error_malloc();
int				ft_strlen(char *s);
int				is_number(char *s);
int				ft_toint(char *s);
t_param_philo	*fill_arg(char **av, int ac);

#endif
