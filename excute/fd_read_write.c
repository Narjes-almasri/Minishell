/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_read_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:17:40 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 15:17:41 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_input_redirection(t_struct_token *token_list, t_fd *fd,
		t_struct_token *tmp)
{
	if (token_list->i == 0)
	{
		if (token_list->heredoc > 0)
		{
			if (fd->fd_here_doc[0] != -1)
			{
				dup2(fd->fd_here_doc[0], STDIN_FILENO);
				close(fd->fd_here_doc[0]);
			}
		}
	}
	else
	{
		if (tmp->prev_read != -1)
		{
			dup2(tmp->prev_read, STDIN_FILENO);
			close(tmp->prev_read);
		}
	}
}

static void	setup_output_redirection(t_struct_token *token_list, t_fd *fd)
{
	if (token_list->i == token_list->n_pip - 1)
	{
		token_list->fd_write = STDOUT_FILENO;
	}
	else
	{
		if (fd->fd_pipe[1] != -1)
		{
			dup2(fd->fd_pipe[1], STDOUT_FILENO);
			close(fd->fd_pipe[1]);
			token_list->fd_write = STDOUT_FILENO;
		}
	}
	if (fd->fd_pipe[0] != -1)
		close(fd->fd_pipe[0]);
}

static void	cleanup_and_exit_on_error(t_fd *fd, t_struct_token *tmp,
		char ****commands)
{
	free(fd);
	free_env(tmp->env);
	free(tmp->exit_status);
	free_whole_command(commands, tmp);
	safe_free_token_list(&tmp);
	exit(1);
}

static void	handle_file_redirections(t_struct_token *token_list, t_fd *fd)
{
	if (fd->fd_in != -1)
	{
		dup2(fd->fd_in, STDIN_FILENO);
		close(fd->fd_in);
	}
	if (fd->fd_out != -1)
	{
		dup2(fd->fd_out, STDOUT_FILENO);
		close(fd->fd_out);
		token_list->fd_write = STDOUT_FILENO;
	}
}

void	execute_child(t_struct_token *token_list, t_fd *fd, char ****commands,
		t_struct_token *tmp)
{
	setup_input_redirection(token_list, fd, tmp);
	setup_output_redirection(token_list, fd);
	if (!check_in_redirection(token_list, fd))
	{
		cleanup_and_exit_on_error(fd, tmp, commands);
	}
	handle_file_redirections(token_list, fd);
	free(fd);
	execute_single_command(token_list, commands, tmp->env, tmp);
}
