/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Def_of_linked_list_variables_3.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:44:15 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 13:27:51 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_pipe(char *s, int *num_of_pipe)
{
	char	*str;

	str = is_pipe(0, s);
	if (str != NULL)
	{
		(*num_of_pipe)++;
		return (str);
	}
	return (NULL);
}

static char	*handle_builtin(char *s)
{
	if (ft_strcmp(s, "echo") == 0)
		return (ft_strdup("echo"));
	return (NULL);
}

static char	*handle_redirection(char *s, int *f)
{
	char	*str;

	str = is_redirection(0, s);
	if (str != NULL)
	{
		*f = 1;
		return (str);
	}
	return (NULL);
}

static char	*handle_quotes(char *s, int *q)
{
	char	*str;

	str = is_double_qoutes(0, q, s);
	if (str != NULL)
		return (str);
	str = is_single_qoutes(0, s, q);
	if (str != NULL)
		return (str);
	if (*q == -1)
		return (NULL);
	return (NULL);
}

char	*identify_value_type(char *s, char *next, int need_input,
			int *num_of_pipe)
{
	char		*str;
	static int	f = 0;
	static int	q = 0;

	if ((!next || next[0] == '\0') && need_input == 1)
		return (NULL);
	str = handle_pipe(s, num_of_pipe);
	if (str)
		return (str);
	str = handle_builtin(s);
	if (str)
		return (str);
	str = handle_redirection(s, &f);
	if (str)
		return (str);
	str = handle_quotes(s, &q);
	if (str)
		return (str);
	if (s != NULL && f-- == 1)
	{
		return (ft_strdup("File_name"));
	}
	if (!str)
		return (ft_strdup("command"));
	return (str);
}
