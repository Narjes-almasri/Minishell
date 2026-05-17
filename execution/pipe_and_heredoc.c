/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:18:13 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 15:18:14 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipe(t_fd *fd, t_struct_token *token_list, int i)
{
	token_list->heredoc = find_target_in_heredoc(token_list);
	token_list->i = i;
	token_list->prev_read = -1;
	if (i < fd->num_of_pipe - 1)
	{
		if (pipe(fd->fd_pipe) == -1)
		{
			perror("pipe failed");
			return ;
		}
	}
}

static int	handle_fork_and_execute(t_struct_token *token_list, t_fd *fd,
		char ****commands, t_struct_token *tmp)
{
	pid_t	pids;

	pids = fork();
	if (pids == 0)
	{
		tmp->env = tmp->env;
		execute_child(token_list, fd, commands, tmp);
		exit(127);
	}
	else if (pids < 0)
	{
		perror("fork failed");
		if (fd->fd_pipe[0] != -1)
			close(fd->fd_pipe[0]);
		if (fd->fd_pipe[1] != -1)
			close(fd->fd_pipe[1]);
		return (-1);
	}
	return (0);
}

static void	close_pipes(t_fd *fd, int *pre_pip)
{
	if (fd->fd_pipe[1] != -1)
		close(fd->fd_pipe[1]);
	if (fd->fd_here_doc)
	{
		if (fd->fd_here_doc[0] != 0)
			close(fd->fd_here_doc[0]);
	}
	if (*pre_pip != -1)
		close(*pre_pip);
}

void	runs_commads(t_fd *fd, t_struct_token *token_list, char ****commands,
		char **env)
{
	int				i;
	int				pre_pip;
	t_struct_token	*tmp;

	i = 0;
	pre_pip = -1;
	tmp = token_list;
	fd->fd_pipe[0] = -1;
	fd->fd_pipe[1] = -1;
	while (i < fd->num_of_pipe && token_list != NULL)
	{
		init_pipe(fd, token_list, i);
		tmp->env = env;
		if (handle_fork_and_execute(token_list, fd, commands, tmp) == -1)
			return ;
		close_pipes(fd, &pre_pip);
		tmp->prev_read = fd->fd_pipe[0];
		pre_pip = fd->fd_pipe[0];
		cut_to_the_first_pip(&token_list, pre_pip, i++, fd->num_of_pipe);
	}
	if (fd->fd_here_doc)
		free(fd->fd_here_doc);
	if (pre_pip != -1)
		close(pre_pip);
}
