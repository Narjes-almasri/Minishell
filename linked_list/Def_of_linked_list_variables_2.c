/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Def_of_linked_list_variables_2.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:41:29 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 17:42:24 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_pipe(int i, char *s)
{
	char	*str;

	if (s[i] == '|')
	{
		str = malloc(1 * 2);
		if (!str)
			return (NULL);
		str[0] = '|';
		str[1] = '\0';
		return (str);
	}
	return (NULL);
}

char	*is_redirection_lessthan(int i, char *s)
{
	char	*str;

	if (s[i] == '<' && s[i + 1] == '<')
	{
		str = malloc(3);
		if (!str)
			return (NULL);
		str[0] = '<';
		str[1] = '<';
		str[2] = '\0';
		return (str);
	}
	else if (s[i] == '<')
	{
		str = malloc(2);
		if (!str)
			return (NULL);
		str[0] = '<';
		str[1] = '\0';
		return (str);
	}
	return (NULL);
}
