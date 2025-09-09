/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_helper_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:46:37 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:06:08 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	failed(char **s, char **tokens, int t)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	tokens[t] = NULL;
	return (-1);
}

int	handle_regular_chars(char *input, int *i, char *temp_token, int *token_len)
{
	if (input[*i] != '\0' && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '\''
		&& input[*i] != '\"')
	{
		*i = split_commands(input, *i, temp_token, token_len);
	}
	return (0);
}

int	handle_operator_token(char *input, int *i, char **tokens, int *t)
{
	int		token_len;
	char	*temp_token;

	token_len = 0;
	temp_token = malloc(1000);
	if (!temp_token)
	{
		tokens[*t] = NULL;
		return (-1);
	}
	*i = split_operators(input, *i, temp_token, &token_len);
	*t = store_token(temp_token, token_len, tokens, *t);
	free(temp_token);
	return (1);
}
