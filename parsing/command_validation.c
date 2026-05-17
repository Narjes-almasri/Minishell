/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:08:45 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 19:21:56 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_split2(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	search_valid_pipes(t_struct_token *t)
{
	int	i;

	i = 0;
	while (t != NULL)
	{
		if (ft_strcmp(t->type, "\"") == 0 || ft_strcmp(t->type, "\'") == 0)
		{
			t = t->next;
			i++;
			continue ;
		}
		if (ft_strcmp(t->type, "|") == 0)
		{
			if (i == 0)
				return (0);
			t = t->next;
			if (!t || ft_strcmp(t->value, "|") == 0)
				return (0);
		}
		i++;
		t = t->next;
	}
	return (1);
}

int	handle_exit_shell(t_struct_token *tmp, char **arg,
		t_struct_token *token_list)
{
	if (ft_exit_shell(tmp, token_list))
	{
		free_fd_arg(NULL, arg, NULL, NULL);
		safe_free_token_list(&token_list);
		return (1);
	}
	return (0);
}

int	handle_check_command(t_struct_token **q, char **envp, t_fd *fd, char **arg)
{
	int	check;

	check = check_command(q, envp);
	if (check == 0)
	{
		printf("minishell:syntax Error\n");
		free_fd_arg(fd, arg, *q, NULL);
		return (1);
	}
	if (check == -1)
	{
		free_fd_arg(fd, arg, NULL, NULL);
		return (2);
	}
	return (0);
}

int	handle_pipe_validation(t_struct_token *token_list, t_fd *fd, char **arg)
{
	if (search_valid_pipes(token_list) == 0)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		free_fd_arg(fd, arg, NULL, NULL);
		safe_free_token_list(&token_list);
		return (1);
	}
	return (0);
}
