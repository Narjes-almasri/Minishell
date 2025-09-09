/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:22:46 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 13:24:56 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_unset_fun(char **env, char *var, int var_len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (env[i] != NULL)
		i++;
	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], var, var_len) == 0
				&& env[i][var_len] == '=') == 0)
		{
			j++;
		}
		else
		{
			free(env[i]);
			env[i] = ft_strdup("");
		}
		i++;
	}
	return (env);
}

void	freee(char **copy, int i)
{
	while (--i >= 0)
		free(copy[i]);
	free(copy);
}

char	**cpy_env(char **env)
{
	char	**copy;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!env)
		return (NULL);
	while (env[len])
		len++;
	copy = malloc(sizeof(char *) * (len + 1));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			freee(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[len] = NULL;
	return (copy);
}

char	**create_env(char **env)
{
	char	**en;

	if (!env)
	{
		printf("Error: env is NULL\n");
		return (NULL);
	}
	if (env != NULL && env[0])
	{
		en = cpy_env(env);
		if (!en)
		{
			printf("error in copping env\n");
			return (NULL);
		}
		return (en);
	}
	return (NULL);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free (env);
}
