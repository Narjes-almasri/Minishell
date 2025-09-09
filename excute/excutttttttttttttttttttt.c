/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutttttttttttttttttttt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:17:17 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 15:17:31 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_fully_num_del(t_struct_token *token_list)
{
	int	count;

	count = 0;
	while (token_list != NULL)
	{
		if (ft_strcmp(token_list->type, "<<") == 0)
			count++;
		token_list = token_list->next;
	}
	return (count);
}

void	cut_to_the_first_pip(t_struct_token **token_list, int prev, int p_i,
		int p_n_pipe)
{
	int	tmp_fd;
	int	p_here_doc;

	if (!*token_list || !token_list)
		return ;
	tmp_fd = (*token_list)->fd_write;
	p_here_doc = (*token_list)->heredoc;
	while ((*token_list) && ft_strcmp((*token_list)->type, "|") != 0)
		(*token_list) = (*token_list)->next;
	if ((*token_list) && ft_strcmp((*token_list)->type, "|") == 0)
		(*token_list) = (*token_list)->next;
	if (*token_list)
	{
		(*token_list)->fd_write = tmp_fd;
		(*token_list)->prev_read = prev;
		(*token_list)->i = p_i;
		(*token_list)->n_pip = p_n_pipe;
		(*token_list)->heredoc = p_here_doc;
		(*token_list)->n_column = rl_num_chars_to_read;
	}
}

int	check_command_after_exit(t_struct_token *token_list)
{
	t_struct_token	*temp;

	temp = token_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->value, "|") == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	find_target_in_heredoc(t_struct_token *token_list)
{
	int				count;
	t_struct_token	*t;

	count = 0;
	t = token_list;
	while (t)
	{
		if (ft_strcmp(t->type, "<<") == 0)
		{
			count++;
		}
		if (ft_strcmp(t->type, "|") == 0)
		{
			break ;
		}
		t = t->next;
	}
	return (count);
}

void	handle_pipe_cleanup(t_fd *fd, t_struct_token *token_list, int i,
		int num_of_pipe)
{
	if (token_list->heredoc > 0)
		fd->num_of_index++;
	if (i != num_of_pipe - 1)
	{
		close(fd->fd_pipe[1]);
		token_list->prev_read = fd->fd_pipe[0];
	}
}
