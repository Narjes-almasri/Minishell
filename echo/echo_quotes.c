/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:12:04 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 12:12:24 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar_symbol(t_struct_token *tokens,
			char *key, int fd, int *i)
{
	char	*str;

	if (key[0] == '0')
	{
		write(fd, "Minishell", 9);
		(*i)++;
		free(key);
		return ;
	}
	if (key[0] == '?')
	{
		str = ft_itoa(tokens->exit_status->value);
		write(fd, str, ft_strlen(str));
		free(str);
		free(key);
		tokens->exit_status->value = 0;
		(*i)++;
		return ;
	}
}

static void	handle_dollar_var( char *key, char **envp, int fd, int *i)
{
	char	*output;

	output = get_env(envp, key);
	if (output)
	{
		write(fd, output, ft_strlen(output));
		*i += ft_strlen(key);
		free(key);
		return ;
	}
	*i += ft_strlen(key) - 1;
	free(key);
	(*i)++;
}

static void	print_non_dollar(char *value, int fd, int *i)
{
	if (value[*i] != '\"')
		write(fd, &value[*i], 1);
	(*i)++;
}

static void	echo_quotion_loop(t_struct_token *tokens,
			char *value, char **envp, int fd)
{
	int		i;
	int		len;
	char	*key;

	i = 1;
	len = ft_strlen(value);
	while (i < len)
	{
		while (value[i] && value[i] != '$')
			print_non_dollar(value, fd, &i);
		if (value[i] == '$')
		{
			i++;
			if (check_digit_and_print_later(value, fd, &i))
				continue ;
			key = get_key(value, len - i + 1, i - 1, i);
			if (key[0] == '0' || key[0] == '?')
				handle_dollar_symbol(tokens, key, fd, &i);
			else
				handle_dollar_var(key, envp, fd, &i);
			continue ;
		}
		i++;
	}
}

void	excute_echo_command_qoution(t_struct_token *tokens,
			char *value, char **envp, int fd)
{
	int		len;

	len = ft_strlen(value);
	if (len == 1)
	{
		write(2, "error the \" not matching", 25);
		return ;
	}
	echo_quotion_loop(tokens, value, envp, fd);
}
