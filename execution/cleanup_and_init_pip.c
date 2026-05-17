/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_init_pip.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:16:05 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 18:21:31 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_struct_token *token_list, t_fd *fd, char ****commands)
{
	if (token_list && commands)
		free_whole_command(commands, token_list);
	if (token_list->exit_status != NULL)
		free(token_list->exit_status);
	safe_free_token_list(&token_list);
	if (fd->fd_here_doc != NULL)
		free(fd->fd_here_doc);
	free(fd);
}

void	init_tokens(t_struct_token *token_list)
{
	token_list->fd_write = 1;
	token_list->prev_read = -1;
	token_list->heredoc = 0;
	token_list->i = 0;
}

void	setup_heredoc_memory(t_fd *fd, int num_of_del)
{
	fd->fd_here_doc = malloc(sizeof(int) * num_of_del);
	fd->num_of_del_here = num_of_del;
	if (!fd->fd_here_doc)
		return ;
	if (num_of_del == 0)
	{
		free(fd->fd_here_doc);
		fd->fd_here_doc = NULL;
	}
}

void	process_heredoc_if_needed(t_handle_heredoc_leak *heredoc_temp,
								int num_of_del)
{
	int	i;

	i = 1;
	if (i <= num_of_del)
	{
		start_heredoc_processing(heredoc_temp, num_of_del);
		heredoc_temp->token->heredoc = 1;
		heredoc_temp->token->fd_read = heredoc_temp->fd->fd_here_doc[0];
	}
}

void	find_heredoc(t_handle_heredoc_leak *heredoc_temp)
{
	int	num_of_del;

	if (!heredoc_temp->token)
	{
		write(2, "Minishell: syntax error near unexpected token\n", 35);
		return ;
	}
	num_of_del = find_fully_num_del(heredoc_temp->token);
	find_target_in_heredoc(heredoc_temp->token);
	setup_heredoc_memory(heredoc_temp->fd, num_of_del);
	process_heredoc_if_needed(heredoc_temp, num_of_del);
}
