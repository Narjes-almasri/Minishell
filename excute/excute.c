/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:04:51 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:46:32 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_single_command(t_struct_token *token_list,
								t_handle_heredoc_leak *heredoc_temp)
{
	char			**test;
	t_struct_token	*tm;

	tm = token_list;
	test = excute_1_command(token_list, heredoc_temp);
	if (heredoc_temp->fd->fd_here_doc != NULL)
		free(heredoc_temp->fd->fd_here_doc);
	free_fd_arg(heredoc_temp->fd, NULL, tm, heredoc_temp->temp_command);
	if (test != NULL)
		return (test);
	return (heredoc_temp->env_temp);
}

void	handle_process_cleanup(t_struct_token *token_list)
{
	if (token_list && token_list->prev_read != -1)
	{
		close(token_list->prev_read);
		token_list->prev_read = -1;
	}
}

void	wait_for_processes(t_fd *fd, t_struct_token *token_list)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < fd->num_of_pipe)
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		if (WIFEXITED(status))
			token_list->exit_status->value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			token_list->exit_status->value = 128 + WTERMSIG(status);
		i++;
	}
}

char	**excuttttttttttttttttttttttttttttt(t_fd *fd,
											t_struct_token *token_list,
											char ****commands,
											char **env)
{
	t_struct_token			*tm;
	t_handle_heredoc_leak	heredoc_temp;

	if (!fd || !token_list || !commands || !env)
		return (env);
	tm = token_list;
	tm->env = env;
	fd->num_of_pipe = token_list->n_pip;
	if (search_for_heredoc(token_list) == 1 || fd->num_of_pipe == 1)
	{
		heredoc_temp.fd = fd;
		heredoc_temp.temp_command = commands;
		heredoc_temp.token = tm;
		heredoc_temp.env_temp = env;
	}
	if (fd->num_of_pipe == 1)
		return (handle_single_command(token_list, &heredoc_temp));
	if (search_for_heredoc(token_list) == 1)
		find_heredoc(&heredoc_temp);
	runs_commads(fd, token_list, commands, env);
	handle_process_cleanup(tm);
	wait_for_processes(fd, tm);
	free_fd_arg(fd, NULL, tm, commands);
	return (env);
}
