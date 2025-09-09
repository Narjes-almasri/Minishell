/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_excute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:06:05 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:16:19 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_delimiter_match_exit(t_struct_token **token_list,
										int *num_of_del,
										int fd,
										t_handle_heredoc_leak *heredoc_temp)
{
	char	*input;

	input = (*token_list)->input_afterhere;
	while (*token_list && ft_strcmp((*token_list)->value, "<<") != 0)
		*token_list = (*token_list)->next;
	if (!*token_list)
		ft_free_heredoc(heredoc_temp, fd, 0);
	if (ft_strcmp((*token_list)->value, "<<") == 0)
	{
		*token_list = (*token_list)->next;
		(*token_list)->delimiter = (*token_list)->value;
		(*token_list)->input_afterhere = input;
		(*num_of_del)--;
	}
	else if (ft_strcmp((*token_list)->type, "|") == 0)
		ft_free_heredoc(heredoc_temp, fd, 0);
}

static void	handle_quoted_delimiter_and_exit(t_struct_token **k,
	int *num_of_del,
	int fd,
	t_handle_heredoc_leak *t)
{
	char	*input;

	t->i = 0;
	input = (*k)->input_afterhere;
	while ((*k)->delimiter[t->i + 1] == (*k)->input_afterhere[t->i])
		t->i++;
	if (ft_strlen((*k)->delimiter) - 2 == t->i
		&& (*k)->input_afterhere[t->i] == '\0')
	{
		while (*k && ft_strcmp((*k)->value, "<<") != 0)
		{
			if (ft_strcmp((*k)->type, "|") == 0)
				ft_free_heredoc(t, fd, 0);
			*k = (*k)->next;
		}
		if (*k && ft_strcmp((*k)->value, "<<") == 0)
		{
			*k = (*k)->next;
			(*k)->delimiter = (*k)->value;
			(*k)->input_afterhere = input;
			(*num_of_del)--;
		}
		else
			ft_free_heredoc(t, fd, 0);
	}
}

void	ex_3(t_struct_token **token_list, int *num_of_del, int fd,
		t_handle_heredoc_leak *heredoc_temp)
{
	if ((*token_list)->delimiter[0] == '\''
		|| (*token_list)->delimiter[0] == '\"')
	{
		handle_quoted_delimiter_and_exit(token_list, num_of_del, fd,
			heredoc_temp);
	}
}

void	ex_4(t_struct_token **token_list, int *num_of_del, int fd,
		t_handle_heredoc_leak *heredoc_temp)
{
	if (ft_strcmp((*token_list)->delimiter,
			(*token_list)->input_afterhere) == 0)
	{
		handle_delimiter_match_exit(token_list, num_of_del, fd, heredoc_temp);
	}
}

void	handle_nonfinal_heredoc(t_struct_token **token_list,
									int *num_of_del,
									int fd,
									t_handle_heredoc_leak *heredoc_temp)
{
	ex_3(token_list, num_of_del, fd, heredoc_temp);
	if (ft_strcmp((*token_list)->input_afterhere, (*token_list)->delimiter) == 0
		&& ((*token_list)->delimiter[0] == '\''
			|| (*token_list)->delimiter[0] == '\"'))
	{
		write(fd, (*token_list)->input_afterhere,
			ft_strlen((*token_list)->input_afterhere));
		write(fd, "\n", 1);
		close(fd);
		return ;
	}
	ex_4(token_list, num_of_del, fd, heredoc_temp);
	if (!token_list || ft_strcmp((*token_list)->value, "|") == 0)
		ft_free_heredoc(heredoc_temp, fd, 0);
}
