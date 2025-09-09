/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:05:10 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:10:03 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_commands(char *input, int i, char *temp_token, int *token_len)
{
	while (input[i] != '\0' && input[i] != ' ' && input[i] != '|'
		&& input[i] != '<' && input[i] != '>' && input[i] != '\''
		&& input[i] != '\"')
	{
		temp_token[(*token_len)++] = input[i];
		i++;
	}
	return (i);
}

int	store_token(char *temp_token, int token_len, char **tokens, int t)
{
	char	*token;

	temp_token[token_len] = '\0';
	token = ft_strdup(temp_token);
	if (token && ft_strlen(token) > 0)
	{
		tokens[t++] = token;
	}
	return (t);
}

int	handle_operators(char *input, int *i, char *temp_token, int *token_len)
{
	*i = split_operators(input, *i, temp_token, token_len);
	return (0);
}
