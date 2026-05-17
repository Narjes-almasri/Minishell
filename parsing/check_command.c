/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:34:58 by naalmasr          #+#    #+#             */
/*   Updated: 2025/09/01 14:27:44 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_special_command_tokens(t_struct_token **token_list)
{
	while (*token_list != NULL && ft_strcmp((*token_list)->type, "|") != 0)
		*token_list = (*token_list)->next;
}

void	process_without_quotes(t_struct_token **token_list, int i,
		char *copy)
{
	if ((*token_list)->value != NULL && !check_dollar((*token_list)->value)
		&& have_quotes((*token_list)->value) == -1)
	{
		(*token_list)->value = without_q((*token_list)->value, i, copy);
	}
}

void	process_without_single_quotes(t_struct_token **token_list, int i,
		char *copy)
{
	if ((*token_list)->value != NULL && !check_dollar((*token_list)->value)
		&& have_quotes((*token_list)->value) == 1)
	{
		(*token_list)->value = without_q_s((*token_list)->value, i, copy);
	}
}

int	handle_dollar_sign(t_struct_token **token_list, char **envp, int j)
{
	char	*old;

	if (check_dollar((*token_list)->value) && (*token_list)->len == 1)
	{
		old = (*token_list)->value;
		(*token_list)->value = replace_doller(old, envp, j);
		old = find_command_path((*token_list)->value, envp, 0);
		if (!old)
		{
			printf("minishell: %s: Is a directory\n", (*token_list)->value);
			return (-1);
		}
		free(old);
	}
	return (1);
}

int	check_command(t_struct_token **token_list, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*token_list != NULL)
	{
		if (ft_strcmp((*token_list)->value, "export") == 0
			|| ft_strcmp((*token_list)->value, "cd") == 0
			|| ft_strcmp((*token_list)->value, "echo") == 0)
		{
			skip_special_command_tokens(token_list);
			continue ;
		}
		process_without_quotes(token_list, i, NULL);
		process_without_single_quotes(token_list, i, NULL);
		if (handle_dollar_sign(token_list, envp, j) == -1)
			return (-1);
		*token_list = (*token_list)->next;
	}
	return (1);
}
