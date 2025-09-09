/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:28:19 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 14:30:07 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_export_command(char *saved_token, char **env)
{
	char	*var;
	char	*value;
	int		var_len;
	char	**t2;

	var = NULL;
	value = NULL;
	if (!extract_and_validate_var(saved_token, &var, &var_len))
		return (env);
	value = extract_value(saved_token, var_len);
	t2 = check_var_existens(env, var, value, var_len);
	if (!t2)
		env = update_env(env, var, value);
	else
		env = t2;
	free(var);
	free(value);
	return (env);
}

int	is_matching_var(char *env_entry, char *var, int var_len)
{
	return (
		(ft_strncmp(env_entry, var, var_len) == 0)
		|| ((ft_strlen(env_entry) > var_len)
			&& (ft_strncmp(env_entry, var, var_len - 1) == 0)
			&& (env_entry[var_len] != '\0')
			&& (env_entry[var_len] != '='))
		|| ((ft_strncmp(env_entry, var, var_len) == 0)
			&& (env_entry[var_len - 1] == '='))
	);
}

char	**check_var_existens(char **env, char *var, char *value, int var_len)
{
	int	i;

	i = 0;
	if (var[var_len - 1] != '\0' && var[var_len - 1] == '=')
		var_len--;
	while (env[i])
	{
		if (is_matching_var(env[i], var, var_len))
		{
			free(env[i]);
			env[i] = malloc(ft_strlen(var) + ft_strlen(value) + 2);
			if (!env[i])
				return (0);
			ft_strcpy(env[i], var);
			ft_strcat(env[i], value);
			return (env);
		}
		i++;
	}
	return (NULL);
}
