/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repalce_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:42:54 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 22:50:09 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_special_var(char *value, char *key, int free_key)
{
	char	*result;

	if (ft_strcmp(key, "?") == 0 || ft_strcmp(key, "0") == 0)
	{
		if (free_key)
			free(key);
		result = ft_strdup(value);
		return (result);
	}
	return (NULL);
}

static char	*handle_env_var(char *value, char *key, char **envp, int pos)
{
	char	*output;
	char	*before;
	char	*result;

	output = get_env(envp, key);
	if (output)
	{
		before = ft_substr(value, 0, pos - 1);
		result = ft_strjoin(before, output);
		free(before);
	}
	else
		result = ft_strdup(value);
	free(key);
	return (result);
}

char	*replace_doller_2(char *value, int i, int len, char **envp)
{
	char	*key;
	char	*result;

	find_dollar(value);
	key = get_key(value, len - i + 1, 0, i);
	if (!key)
		return (NULL);
	result = handle_special_var(value, key, 1);
	if (result)
		return (result);
	return (handle_env_var(value, key, envp, i));
}

char	*replace_doller(char *value, char **envp, int i)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	var_name = extract_var_name(value + 1, i);
	if (!var_name)
		return (value);
	result = handle_special_var(value, var_name, 1);
	if (result)
		return (result);
	var_value = get_env(envp, var_name);
	if (var_value)
		result = ft_strdup(var_value);
	else
		result = value;
	free(var_name);
	return (result);
}
