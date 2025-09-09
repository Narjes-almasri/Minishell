/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:38:57 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 13:07:19 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here(t_struct_token **token_list, int fd, int *num_of_del,
		t_handle_heredoc_leak *heredoc_temp)
{
	char	*delimiter;
	char	*input;

	if (!*token_list || !(*token_list)->input_afterhere
		|| !(*token_list)->delimiter || fd == -1)
		ft_free_heredoc(heredoc_temp, fd, 0);
	delimiter = (*token_list)->delimiter;
	input = (*token_list)->input_afterhere;
	if (ft_strcmp(input, delimiter) != 0 && *num_of_del == 1)
	{
		lasther_in_isnt_d(token_list, num_of_del, fd, heredoc_temp);
		if (!check_here_expand((*token_list), input, heredoc_temp->env_temp,
				fd))
			write(fd, "\n", 1);
	}
	else if (ft_strcmp(input, delimiter) == 0 && *num_of_del == 1)
		ft_free_heredoc(heredoc_temp, fd, 0);
	else
		handle_nonfinal_heredoc(token_list, num_of_del, fd, heredoc_temp);
}

int	lastheredoc_and_input_isnt_the_del22(t_struct_token **token_list, int fd)
{
	while (*token_list && ft_strcmp((*token_list)->value, "<<") != 0)
	{
		if (ft_strcmp((*token_list)->type, "|") == 0)
		{
			close(fd);
			return (0);
		}
		*token_list = (*token_list)->next;
	}
	return (1);
}

int	check_here_expand(t_struct_token *token_list, char *input, char **envp,
		int fd)
{
	if (input[0] == '\'')
	{
		print_whats_inside_qouts(input, -1, fd);
		return (0);
	}
	else if (input[0] == '\"')
	{
		excute_echo_command_qoution(token_list, input, envp, fd);
		return (0);
	}
	else
	{
		excute_echo_command_without_q(token_list, input, envp, fd);
		return (0);
	}
	return (1);
}
