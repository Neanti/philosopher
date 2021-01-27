/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: augay <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:58:15 by augay             #+#    #+#             */
/*   Updated: 2021/01/27 13:58:17 by augay            ###   ########.fr       */
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
	write(1, "Mutex error\n", 12);
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
