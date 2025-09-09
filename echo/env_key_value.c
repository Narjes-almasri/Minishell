/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_key_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:12:54 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 23:01:49 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_special_var_name(char *str, int pos)
{
	char	*var_name;

	if (str[pos] == '?' || str[pos] == '0'
		|| (str[pos] >= '1' && str[pos] <= '9'))
	{
		var_name = malloc(2);
		if (!var_name)
			return (NULL);
		var_name[0] = str[pos];
		var_name[1] = '\0';
		return (var_name);
	}
	return (NULL);
}

static char	*extract_normal_var_name(char *str, int start_pos)
{
	int		i;
	int		len;
	char	*var_name;
	int		j;

	i = start_pos;
	len = 0;
	while (str[i] && (if_char_num(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	if (len == 0)
		return (NULL);
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	j = 0;
	i = start_pos;
	while (str[i] && (if_char_num(str[i]) || str[i] == '_'))
		var_name[j++] = str[i++];
	var_name[j] = '\0';
	return (var_name);
}

char	*extract_var_name(char *str, int start_pos)
{
	char	*var_name;

	var_name = extract_special_var_name(str, start_pos);
	if (var_name)
		return (var_name);
	return (extract_normal_var_name(str, start_pos));
}

char	*get_env(char **envp, const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			if (envp[i][key_len + 1] != '\0')
				return (envp[i] + key_len + 1);
		}
		i++;
	}
	return (NULL);
}

char	*get_key(char *key, int size, int f, int i)
{
	int		j;
	char	*value;

	(void)f;
	j = 0;
	value = malloc(1 * size);
	if (!value)
		return (NULL);
	if (key[i] == '?' || key[i] == '0' || (key[i] >= '1' && key[i] <= '9'))
	{
		value[j++] = key[i];
		value[j] = '\0';
		return (value);
	}
	while (key[i] != '\0' && key[i] != '\"' && key[i] != ' ' && key[i] != '$'
		&& key[i] != '+' && key[i] != '\'' && (if_char_num(key[i])
			|| key[i] == '_'))
	{
		value[j] = key[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}
