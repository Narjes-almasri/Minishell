/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herd3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:37:45 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:16:06 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*finding_del(t_struct_token *token_list)
{
	while (token_list != NULL)
	{
		if (ft_strcmp(token_list->value, "<<") == 0)
		{
			if (token_list->next != NULL)
			{
				token_list = token_list->next;
				return (token_list->value);
			}
		}
		if (ft_strcmp(token_list->value, "|") == 0)
			return (NULL);
		token_list = token_list->next;
	}
	return (NULL);
}

int	starting_2(t_struct_token *token_list, char **delimiter,
		char **input_afterhere)
{
	token_list->delimiter = finding_del(token_list);
	*delimiter = token_list->delimiter;
	*input_afterhere = readline("> ");
	if (!*input_afterhere)
	{
		return (0);
	}
	return (1);
}

void	starting_child(t_handle_heredoc_leak *heredoc_temp,
					t_struct_token *token_list,
					int fd)
{
	int	num_of_del;

	st3(token_list);
	num_of_del = find_target_in_heredoc(token_list);
	while (1)
	{
		if (!starting_2(token_list, &token_list->delimiter,
				&token_list->input_afterhere))
		{
			close(fd);
			break ;
		}
		here(&token_list, fd, &num_of_del, heredoc_temp);
	}
}

static void	check_and_handle_matching_delimiter(t_struct_token **token_list,
	int *num_of_del,
	int fd,
	t_handle_heredoc_leak *heredoc_temp)
{
	int		i;
	char	*input;

	i = 0;
	input = (*token_list)->input_afterhere;
	while ((*token_list)->delimiter[i + 1] == (*token_list)->input_afterhere[i])
		i++;
	if (ft_strlen((*token_list)->delimiter) - 2 == i
		&& (*token_list)->input_afterhere[i] == '\0')
	{
		if (!lastheredoc_and_input_isnt_the_del22(token_list, fd))
			ft_free_heredoc(heredoc_temp, fd, 0);
		if (*token_list && ft_strcmp((*token_list)->value, "<<") == 0)
		{
			*token_list = (*token_list)->next;
			(*token_list)->delimiter = (*token_list)->value;
			(*token_list)->input_afterhere = input;
			(*num_of_del)--;
			ft_free_heredoc(heredoc_temp, fd, 0);
		}
		else
			ft_free_heredoc(heredoc_temp, fd, 0);
	}
}

void	lasther_in_isnt_d(t_struct_token **token_list,
						int *num_of_del,
						int fd,
						t_handle_heredoc_leak *heredoc_temp)
{
	if ((*token_list)->delimiter[0] == '\''
		|| (*token_list)->delimiter[0] == '\"')
		check_and_handle_matching_delimiter(token_list, num_of_del, fd,
			heredoc_temp);
}
