/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_no_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:11:15 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 13:18:00 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar_symbol2(t_struct_token *tokens,
									char *key,
									int fd,
									int *i)
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
		(*i)++;
		return ;
	}
}

static int	handle_dollar_var2(char *key, char **envp, int fd, char *value)
{
	int		i;
	char	*output;

	i = 0;
	output = get_env(envp, key);
	if (output)
	{
		write(fd, output, ft_strlen(output));
		i += ft_strlen(key);
		free(key);
		return (i);
	}
	i += ft_strlen(key);
	free(key);
	if (*(value + i))
		i++;
	return (i);
}

int	check_digit_and_print_later(char *value, int fd, int *i)
{
	if (value[*i] > 48 && value[*i] <= 57)
	{
		(*i)++;
		while (value[*i] != '\0')
		{
			if (value[*i] != '$')
				break ;
			write(fd, &value[*i], 1);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

static void	print_until_dollar(char *value, int fd, int *i)
{
	while (value[*i] && value[*i] != '$')
	{
		write(fd, &value[*i], 1);
		(*i)++;
	}
}

void	excute_echo_command_without_q(t_struct_token *tokens,
									char *value,
									char **envp,
									int fd)
{
	int		i;
	char	*key;
	int		len;

	i = 0;
	len = ft_strlen(value);
	while (value[i])
	{
		print_until_dollar(value, fd, &i);
		if (value[i] == '$')
		{
			i++;
			if (check_digit_and_print_later(value, fd, &i))
				continue ;
			key = get_key(value, len - i + 1, i - 1, i);
			if (key[0] == '0' || key[0] == '?')
				handle_dollar_symbol2(tokens, key, fd, &i);
			else
				i += handle_dollar_var2(key, envp, fd, &value[i]);
			continue ;
		}
		if (value[i])
			i++;
	}
}
