/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:54:25 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 13:54:27 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include "struct.h"

int					error_arg();
int					error_thread();
int					error_mutex();
int					error_malloc();
int					ft_strlen(char *s);
int					is_number(char *s);
int					ft_toint(char *s);
t_param_philo		*fill_arg(char **av, int ac);
t_philo				*init_philo(t_param_philo *arg, int i, t_forks *fl, t_forks *fr, t_forks *end);
t_forks				*init_forks(int n);
long				elapsed(struct timeval t);
void				wrap_sleep(long t);
int					time_diff(struct timeval last, struct timeval actual);

#endif
