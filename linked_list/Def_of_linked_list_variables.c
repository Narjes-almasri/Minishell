/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Def_of_linked_list_variables.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:56:02 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 23:02:58 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_single_redirection(int i, char *s)
{
	char	*str;

	if (s[i] == '>')
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = '>';
		str[1] = '\0';
		return (str);
	}
	return (NULL);
}

char	*is_redirection(int i, char *s)
{
	char	*str;

	if (s[i] == '>' && s[i + 1] == '>')
	{
		str = malloc(3);
		if (!str)
			return (NULL);
		str[0] = '>';
		str[1] = '>';
		str[2] = '\0';
		return (str);
	}
	str = is_single_redirection(i, s);
	if (str != NULL)
		return (str);
	str = is_redirection_lessthan(i, s);
	return (str);
}

char	*is_double_qoutes(int i, int *q, char *value)
{
	char	*str;
	int		open;

	open = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\"' && open == 0)
			open++;
		if (value[i] == '\"' && open != 0)
			open--;
		i++;
	}
	if (value[i] == '\0' && open == 0 && value[i] != '\"' && value[0] == '\"')
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = '"';
		str[1] = '\0';
		return (str);
	}
	else if (value[0] == '\"')
		*q = -1;
	return (NULL);
}

char	*is_single_qoutes(int i, char *s, int *q)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	if (s[i] == '\'')
	{
		i++;
		while (i < len - 1)
			i++;
		if (s[i] == '\'')
		{
			str = malloc(2);
			if (!str)
				return (NULL);
			str[0] = '\'';
			str[1] = '\0';
			return (str);
		}
		else
			*q = -1;
	}
	return (NULL);
}

int	search_valid_command(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && isalpha(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}
