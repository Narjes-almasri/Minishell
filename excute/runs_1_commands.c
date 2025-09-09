/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs_1_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:19:10 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 15:21:41 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**excute_1_command(t_struct_token *token_list,
		t_handle_heredoc_leak *heredoc_tmep)
{
	t_struct_token	*tmp;

	tmp = token_list;
	if (!check_in_redirection(token_list, heredoc_tmep->fd))
		return (NULL);
	the_finalll_function_for_1_command(token_list, heredoc_tmep);
	if (is_buildin(token_list))
	{
		heredoc_tmep->env_temp = build_in_fun(tmp, token_list,
				heredoc_tmep->temp_command, heredoc_tmep->env_temp);
		if (heredoc_tmep->fd->fd_out != -1)
			close(heredoc_tmep->fd->fd_out);
		if (heredoc_tmep->fd->fd_in != -1)
			close(heredoc_tmep->fd->fd_in);
		return (heredoc_tmep->env_temp);
	}
	return (NULL);
}

void	the_finalll_function_for_1_command(t_struct_token *token_list,
		t_handle_heredoc_leak *heredoc_tmep)
{
	token_list->fd_write = 0;
	token_list->fd_read = -1;
	if (search_for_heredoc(token_list) == 1)
		find_heredoc(heredoc_tmep);
	if (search_for_heredoc(token_list) && heredoc_tmep->fd->fd_in != -1)
	{
		check_the_priority(token_list, &heredoc_tmep->fd->fd_in,
			&token_list->heredoc);
		if (token_list->heredoc == 1)
			token_list->fd_read = token_list->heredoc_pipe[0];
		else
			token_list->fd_read = heredoc_tmep->fd->fd_in;
	}
	if (heredoc_tmep->fd->fd_out != -1)
		token_list->fd_write = heredoc_tmep->fd->fd_out;
	if (heredoc_tmep->fd->fd_in != -1)
		token_list->fd_read = heredoc_tmep->fd->fd_in;
	if (!is_buildin(token_list))
	{
		runs_one_command(token_list, heredoc_tmep->temp_command,
			heredoc_tmep->env_temp, heredoc_tmep->fd);
	}
	if (heredoc_tmep->fd->fd_here_doc != NULL)
		close(heredoc_tmep->fd->fd_here_doc[0]);
}

static void	handle_parent_process(t_struct_token *token_list, int state)
{
	if (token_list->fd_read != -1)
		close(token_list->fd_read);
	if (token_list->fd_write != 0)
		close(token_list->fd_write);
	signal(SIGINT, SIG_IGN);
	wait(&state);
	if (WIFEXITED(state))
		token_list->exit_status->value = WEXITSTATUS(state);
	else if (WIFSIGNALED(state))
		token_list->exit_status->value = 128 + WTERMSIG(state);
	else
		token_list->exit_status->value = 1;
}

void	runs_one_command(t_struct_token *token_list, char ****commands,
		char **env, t_fd *fd)
{
	pid_t			child;
	int				status;
	t_struct_token	*t;

	status = 0;
	t = token_list;
	if (commands[0][0][0] != NULL)
	{
		child = fork();
		if (child == 0)
		{
			ft_excute_1_command(t, commands, env, fd);
			exit(1);
		}
		else if (child > 0)
			handle_parent_process(token_list, status);
		else
		{
			perror("fork failed");
			exit(1);
		}
	}
}

void	ft_excute_1_command(t_struct_token *token_list, char ****commands,
		char **env, t_fd *fd)
{
	char	*find_path;

	if (token_list->value != NULL && (token_list->value[0] == '/'
			|| token_list->value[0] == '.'))
		find_path = token_list->value;
	else
		find_path = find_command_path(commands[0][0][0], env, 1);
	if (!find_path)
	{
		ft_exit(token_list, fd, commands);
		free_env(env);
		exit(127);
	}
	if (token_list->fd_read != -1)
		dup2(token_list->fd_read, STDIN_FILENO);
	if (token_list->fd_write != 0)
		dup2(token_list->fd_write, STDOUT_FILENO);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(find_path, commands[0][0], env);
	perror("execve failed");
	ft_exit(token_list, fd, commands);
	free_env(env);
	exit(1);
}
