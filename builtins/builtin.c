/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:26:25 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 14:29:06 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_and_extend_env(char **env, int *j)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	*j = 0;
	while (env[*j])
	{
		new_env[*j] = ft_strdup(env[*j]);
		(*j)++;
	}
	return (new_env);
}

char	**update_env(char **env, char *var, char *value)
{
	int		j;
	char	**new_env;

	new_env = copy_and_extend_env(env, &j);
	if (!new_env)
		return (NULL);
	new_env[j] = malloc(ft_strlen(var) + ft_strlen(value) + 2);
	ft_strcpy(new_env[j], var);
	if (!value)
		ft_strcat(new_env[j], NULL);
	else
		ft_strcat(new_env[j], value);
	j++;
	new_env[j] = NULL;
	free_env(env);
	return (new_env);
}

char	*check_first_char_value(char *value)
{
	if (value[0] == ' ')
		value = ft_strdup("\0");
	return (value);
}

int	extract_and_validate_var(char *saved_token, char **var, int *var_len)
{
	int	s;

	*var_len = 0;
	s = 0;
	while (saved_token[s] && saved_token[s] != '=')
	{
		(*var_len)++;
		s++;
	}
	*var = ft_substr(saved_token, 0, *var_len + 1);
	if (!*var)
		return (0);
	if (!ft_isalnum(*var))
	{
		printf("export : %s not valid identifier \n", *var);
		free(*var);
		return (0);
	}
	return (1);
}

char	*extract_value(char *saved_token, int var_len)
{
	char	*value;

	value = NULL;
	if (saved_token[var_len] == '=')
	{
		if (saved_token[var_len + 1] != '\0')
			value = ft_strdup(saved_token + var_len + 1);
		else if (saved_token[var_len + 1] == '\0'
			|| saved_token[var_len + 1] == ' ')
		{
			value = ft_strdup("\0");
		}
	}
	else
		value = ft_strdup("\0");
	return (value);
}
