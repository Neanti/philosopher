/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 07:40:55 by augay             #+#    #+#             */
/*   Updated: 2021/02/04 07:40:56 by augay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	error_arg(void)
{
	write(1, "Args error\n", 11);
	return (1);
}

int	error_thread(void)
{
	write(1, "Thread error\n", 13);
	return (1);
}

int	error_mutex(void)
{
	write(1, "Semaphore error\n", 16);
	return (1);
}

int	error_malloc(void)
{
	write(1, "Malloc error\n", 13);
	return (1);
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
