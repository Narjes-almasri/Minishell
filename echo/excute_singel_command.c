/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_singel_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:15:35 by naalmasr          #+#    #+#             */
/*   Updated: 2025/09/01 14:14:45 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	if (s[0] == '-')
	{
		while (s[i] != '\0' && s[i] == 'n')
			i++;
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

int	check_n_e(char *s)
{
	int	i;

	i = 1;
	if (s[0] == '-')
	{
		while (s[i] != '\0' && (s[i] == 'n' || s[i] == 'e'))
			i++;
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

static int	is_pipe_or_redirection(char *type)
{
	if (ft_strcmp(type, "|") == 0 || ft_strcmp(type, ">") == 0
		|| ft_strcmp(type, ">>") == 0 || ft_strcmp(type, "<") == 0
		|| ft_strcmp(type, "<<") == 0)
		return (1);
	return (0);
}

void	excute_echo_command_2(t_struct_token *token_list,
			char **envp, int fd)
{
	int	print_spasce;

	print_spasce = 0;
	while (token_list != NULL && !is_pipe_or_redirection(token_list->type))
	{
		if (token_list->value[0] == '\'')
			print_whats_inside_qouts(token_list->value, 0, fd);
		else if (token_list->value[0] == '\"')
		{
			excute_echo_command_qoution(token_list, token_list->value,
				envp, fd);
		}
		else
		{
			excute_echo_command_without_q(token_list,
				token_list->value, envp, fd);
		}
		token_list = token_list->next;
		if (token_list != NULL && ft_strcmp(token_list->value, "|"))
			write(fd, " ", 1);
		print_spasce++;
	}
}

void	excute_echo_command(t_struct_token *token_list,
			char **envp, int fd)
{
	int	f_valid_n_echo;

	f_valid_n_echo = 0;
	if (ft_strcmp(token_list->type, "echo") == 0)
	{
		token_list = token_list->next;
		if (!token_list)
		{
			write(fd, "\n", 1);
			return ;
		}
		while (check_n(token_list->value))
		{
			token_list = token_list->next;
			if (!token_list)
				return ;
			f_valid_n_echo++;
		}
		excute_echo_command_2(token_list, envp, fd);
		if (f_valid_n_echo == 0)
			write (fd, "\n", 1);
	}
	token_list->exit_status->value = 0;
}
