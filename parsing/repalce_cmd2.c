/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repalce_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:01:06 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 11:13:12 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(fd, env[i], ft_strlen(env[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
}

int	len_without_q(char *value, int start)
{
	int	len;

	len = 0;
	while (value[start] != '\0')
	{
		if (value[start] != '\"')
			len++;
		start++;
	}
	return (len);
}

char	*without_q(char *value, int i, char *copy)
{
	int	len;

	len = len_without_q(value, i);
	copy = malloc(len + 2);
	if (!copy)
		return (NULL);
	i = 0;
	len = 0;
	while (value[i] != '\0')
	{
		if (value[i] != '\"')
		{
			copy[len] = value[i];
			len++;
		}
		i++;
	}
	if (len == 0)
	{
		copy[len] = ' ';
		len++;
	}
	copy[len] = '\0';
	free(value);
	return (copy);
}
