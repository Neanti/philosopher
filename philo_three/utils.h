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
# include <sys/stat.h>
# include <fcntl.h>
//# include <wait.h>
# include "struct.h"

int				error_arg();
int				error_thread();
int				error_mutex();
int				error_malloc();
int				ft_strlen(char *s);
int				is_number(char *s);
int				ft_toint(char *s);
t_param_philo	*fill_arg(char **av, int ac);
t_philo			*init_philo(t_param_philo *arg, int i,
				sem_t **s_list, t_fin *end);
long			elapsed(struct timeval t);
void			wrap_sleep(long t);
int				time_diff(struct timeval last, struct timeval actual);
int				check_elapsed(t_philo *p, struct timeval last);
int				philo_do_1(t_philo *p, struct timeval *last);
void			start_sync(struct timeval *last, t_philo *p);
void			release_sem(t_philo *p);
int				philo_do_body(struct timeval *last, t_philo *p);
void			*philo_do(void *arg);
void			philo_die(t_philo *p);

#endif
