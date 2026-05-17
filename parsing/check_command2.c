/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:55:16 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 16:10:12 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operates(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	count_non_quote_chars(char *value, int i)
{
	int	len;

	len = 0;
	while (value[i] != '\0')
	{
		if (value[i] != '\'')
			len++;
		i++;
	}
	return (len);
}

void	copy_without_quotes(char *value, char *copy, int *i, int *len)
{
	while (value[*i] != '\0')
	{
		if (value[*i] != '\'')
		{
			copy[*len] = value[*i];
			(*len)++;
		}
		(*i)++;
	}
}

char	*without_q_s(char *value, int i, char *copy)
{
	int	len;

	len = count_non_quote_chars(value, i);
	copy = malloc(len + 2);
	if (!copy)
		return (NULL);
	if (is_operates(value) == 1)
	{
		free(copy);
		return (value);
	}
	i = 0;
	len = 0;
	copy_without_quotes(value, copy, &i, &len);
	if (len == 0)
	{
		copy[len] = ' ';
		len++;
	}
	copy[len] = '\0';
	free(value);
	return (copy);
}

int	have_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			return (1);
		if (s[i] == '\"')
			return (-1);
		i++;
	}
	return (0);
}
