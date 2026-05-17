/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:44:53 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 22:46:48 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_special_variables(char var_char, t_exit_status *exit_status)
{
	if (var_char == '?')
		return (ft_itoa(exit_status->value));
	else if (var_char == '0')
		return (ft_strdup("Minishell"));
	else if (var_char >= '1' && var_char <= '9')
		return (ft_strdup(""));
	return (NULL);
}

static char	*expand_special_or_positional_variable(char *str, int *pos,
		t_exit_status *exit_status)
{
	int		start;
	char	*result;

	start = *pos + 1;
	if (str[start] == '?' || str[start] == '0'
		|| (str[start] >= '1' && str[start] <= '9'))
	{
		result = expand_special_variables(str[start], exit_status);
		*pos = start + 1;
		return (result);
	}
	return (NULL);
}

static char	*expand_env_variable(char *str, int *pos, char **envp)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*result;

	start = *pos + 1;
	var_name = extract_var_name(str, start);
	if (!var_name)
	{
		(*pos)++;
		return (ft_strdup("$"));
	}
	var_value = get_env(envp, var_name);
	if (var_value)
		result = ft_strdup(var_value);
	else
		result = ft_strdup("");
	*pos = start + ft_strlen(var_name);
	free(var_name);
	return (result);
}

char	*expand_single_variable(char *str, int *pos, char **envp,
		t_exit_status *exit_status)
{
	char	*result;

	if (str[*pos] != '$')
		return (NULL);
	result = expand_special_or_positional_variable(str, pos, exit_status);
	if (result)
		return (result);
	return (expand_env_variable(str, pos, envp));
}
