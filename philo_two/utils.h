/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:29:14 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 07:29:16 by augay            ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
# include "struct.h"

int				error_arg();
int				error_thread();
int				error_mutex();
int				error_malloc();
int				ft_strlen(char *s);
int				is_number(char *s);
int				ft_toint(char *s);
t_param_philo	*fill_arg(char **av, int ac);
t_philo			*init_p(t_param_philo *arg, int i, sem_t **s_list, t_fin *end);
long			elapsed(struct timeval t);
void			wrap_sleep(long t);
int				time_diff(struct timeval last, struct timeval actual);
int				check_elapsed(t_philo *p, struct timeval last);
void			end_philo(t_philo *p);
void			philo_body_2(t_philo *p);
void			wrap(t_philo *p);
void			*philo_do(void *arg);
int				philo_body(t_philo *p, struct timeval *last);

#endif
