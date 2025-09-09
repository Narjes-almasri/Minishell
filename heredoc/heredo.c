/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:36:07 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:53:19 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	close(0);
	write(1, "\n", 1);
}

void	ft_free_heredoc(t_handle_heredoc_leak *heredoc_temp, int fd, int s_exit)
{
	if (fd != -1)
		close(fd);
	free_env(heredoc_temp->env_temp);
	ft_exit(heredoc_temp->token, heredoc_temp->fd, heredoc_temp->temp_command);
	exit(s_exit);
}

void	st3(t_struct_token *token_list)
{
	if (token_list != NULL)
	{
		token_list->delimiter = NULL;
		token_list->input_afterhere = NULL;
	}
}

void	start_heredoc_processing(t_handle_heredoc_leak *heredoc_temp,
								int num_of_del)
{
	t_struct_token	*token_list;
	char			*delimiter;
	char			*input_afterhere;

	token_list = heredoc_temp->token;
	init_heredoc_token(heredoc_temp->token, &delimiter, &input_afterhere,
		&token_list);
	process_heredocs(heredoc_temp, num_of_del);
}

void	init_heredoc_token(t_struct_token *t, char **delimiter,
		char **input_afterhere, t_struct_token **token_list)
{
	*delimiter = NULL;
	*input_afterhere = NULL;
	*token_list = t;
	if (t)
	{
		t->heredoc_expand = 1;
		t->heredoc_pipe[0] = -1;
		t->heredoc_pipe[1] = -1;
	}
}
