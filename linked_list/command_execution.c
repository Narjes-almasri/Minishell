/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:12:06 by naalmasr          #+#    #+#             */
/*   Updated: 2025/09/01 14:28:01 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	****setup_commands(t_struct_token *tmp, t_fd *fd, char **arg,
		t_struct_token *token_list)
{
	char	****commands;

	commands = init_execute_commands(tmp);
	if (!commands)
	{
		free_fd_arg(fd, arg, token_list, NULL);
		return (NULL);
	}
	fill_the_3d_array(tmp, commands, tmp->n_pip, tmp->n_column);
	return (commands);
}

char	**execute_and_cleanup(t_fd *fd, char ****commands, char **envp,
		t_struct_token *token_list)
{
	char			**t;
	t_struct_token	*tmp;

	init_tokens(token_list);
	tmp = token_list;
	t = excuttttttttttttttttttttttttttttt(fd, tmp, commands, envp);
	safe_free_token_list(&token_list);
	if (t != NULL)
		return (t);
	return (envp);
}

int	check_initial_conditions(t_fd *fd, t_struct_token *token_list, char **arg)
{
	t_struct_token	*tmp;

	tmp = NULL;
	if (!token_list)
	{
		free_fd_arg(fd, arg, NULL, NULL);
		return (1);
	}
	if (handle_exit_shell(tmp, arg, token_list))
	{
		free(fd);
		return (1);
	}
	return (0);
}

int	run_command_checks(t_struct_token *token_list, t_fd *fd, char **envp,
		char *****commands)
{
	t_struct_token	*q;
	t_struct_token	*tmp;
	int				check;

	q = token_list;
	tmp = token_list;
	check = handle_check_command(&q, envp, fd, NULL);
	if (check == 1 || check == 2)
	{
		safe_free_token_list(&tmp);
		return (1);
	}
	if (handle_pipe_validation(token_list, fd, NULL))
		return (1);
	*commands = setup_commands(tmp, fd, NULL, token_list);
	if (!*commands)
		return (1);
	return (0);
}

char	**start_execution_cmd(t_fd *fd, t_struct_token *token_list, char **envp,
		char **arg)
{
	char	****commands;

	if (check_initial_conditions(fd, token_list, arg))
		return (NULL);
	free_env(arg);
	expand_token_variables(token_list, envp);
	if (run_command_checks(token_list, fd, envp, &commands))
		return (envp);
	return (execute_and_cleanup(fd, commands, envp, token_list));
}
