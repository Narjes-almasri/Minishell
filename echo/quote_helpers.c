/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:15:43 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 12:15:43 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_until_char(char *s, int fd, char stop, int start)
{
	int	i;

	i = start;
	while (s[i] && s[i] != stop)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_whats_inside_qouts(char *s, int f_idenify_qout, int fd)
{
	if (f_idenify_qout == 1)
	{
		print_until_char(s, fd, '\"', 1);
		return ;
	}
	if (f_idenify_qout == -1)
	{
		print_until_char(s, fd, '\"', 0);
		return ;
	}
	print_until_char(s, fd, '\'', 1);
}
