/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repalce_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:49:49 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 22:53:03 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*without_bin(char *s, int i)
{
	while (s[i] != '\0' && s[i] == '/')
		i++;
	if (ft_strncmp(s + i, "usr", 3) == 0)
	{
		i = i + 3;
		while (s[i] != '\0' && s[i] == '/')
			i++;
		if (ft_strncmp(s + i, "bin", 3) == 0)
		{
			i += 3;
			while (s[i] != '\0' && s[i] == '/')
				i++;
			while (s[i] != '\0' && s[i] != '/')
			{
				i++;
			}
		}
		return (s);
	}
	return (NULL);
}

int	check_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '$')
		i++;
	if (s[i] == '$')
		return (1);
	return (0);
}

int	find_dollar(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '$')
			break ;
		i++;
	}
	return (i);
}
