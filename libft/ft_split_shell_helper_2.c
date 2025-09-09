/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_helper_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:05:31 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 13:27:02 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isappende_heredoc(char *input)
{
	int	i;

	i = 0;
	if (input[i + 1] != '\0' && input[i + 1] == '>')
		return (1);
	else if (input[i + 1] != '\0' && input[i + 1] == '<')
		return (1);
	return (0);
}

int	is_after_export(char **tokens, int current_index)
{
	if (current_index > 0 && tokens[current_index - 1] != NULL)
	{
		return (ft_strcmp(tokens[current_index - 1], "export") == 0);
	}
	return (0);
}

int	split_quote(char *input, int i, char *temp_token, int *token_len)
{
	char	quote_char;
	int		closing_quote_idx;

	quote_char = input[i];
	closing_quote_idx = find_closing_quote(input, i, quote_char);
	if (closing_quote_idx == -1)
	{
		printf("Error: No matching quote found\n");
		return (-1);
	}
	while (i <= closing_quote_idx)
	{
		temp_token[(*token_len)++] = input[i];
		i++;
	}
	return (i);
}

int	split_operators(char *input, int i, char *temp_token, int *token_len)
{
	while (isappende_heredoc(input + i))
	{
		temp_token[(*token_len)++] = input[i];
		i++;
	}
	if (input[i] != '\0')
		temp_token[(*token_len)++] = input[i];
	i++;
	return (i);
}

int	split_export_argument(char *input, int i, char *temp_token, int *token_len)
{
	int	quote_result;

	while (input[i] != '\0' && input[i] != ' ' && input[i] != '|'
		&& input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote_result = split_quote(input, i, temp_token, token_len);
			if (quote_result == -1)
				return (-1);
			i = quote_result;
		}
		else
		{
			temp_token[(*token_len)++] = input[i];
			i++;
		}
	}
	return (i);
}
