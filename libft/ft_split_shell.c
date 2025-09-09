/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:03:08 by lalmahth          #+#    #+#             */
/*   Updated: 2025/09/01 14:27:06 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quote_token(char *input, int *i, char **tokens, int *t)
{
	int		token_len;
	char	*temp_token;
	int		quote_result;

	token_len = 0;
	temp_token = malloc(1000);
	if (!temp_token)
	{
		tokens[*t] = NULL;
		return (-1);
	}
	quote_result = split_quote(input, *i, temp_token, &token_len);
	if (quote_result == -1)
		return (failed(&temp_token, tokens, *t));
	*i = quote_result;
	*t = store_token(temp_token, token_len, tokens, *t);
	free(temp_token);
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
	return (1);
}

static int	process_regular_chars(char *input, int *i, char *temp_token,
		int *token_len)
{
	int		quote_result;
	char	c;

	while (input[*i] != '\0' && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote_result = split_quote(input, *i, temp_token, token_len);
			if (quote_result == -1)
				return (-1);
			*i = quote_result;
		}
		else
		{
			c = input[*i];
			temp_token[*token_len] = c;
			(*token_len)++;
			(*i)++;
		}
	}
	return (0);
}

static int	process_single_token(char *input, int *i, char **tokens, int *t)
{
	int		token_len;
	char	*temp_token;
	int		result;

	token_len = 0;
	temp_token = NULL;
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		return (handle_operator_token(input, i, tokens, t));
	if (init_temp_token(&temp_token, *t, tokens) == -1)
		return (-1);
	if (input[*i] == '\'' || input[*i] == '"')
	{
		result = handle_quote_token(input, i, tokens, t);
		free(temp_token);
		return (result);
	}
	if (process_regular_chars(input, i, temp_token, &token_len) == -1)
		return (failed(&temp_token, tokens, *t));
	*t = store_token(temp_token, token_len, tokens, *t);
	free(temp_token);
	return (0);
}

int	split_shell_helper(char *input, char **tokens)
{
	int	i;
	int	t;
	int	result;

	i = 0;
	t = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		result = process_single_token(input, &i, tokens, &t);
		if (result == -1)
			return (-1);
		if (result == 1)
			continue ;
	}
	return (t);
}

char	**ft_split_shell(char *input)
{
	int		t;
	char	**tokens;

	tokens = malloc(256 * sizeof(char *));
	if (!tokens)
		return (NULL);
	t = split_shell_helper(input, tokens);
	if (t == -1)
	{
		free_env(tokens);
		return (NULL);
	}
	tokens[t] = NULL;
	return (tokens);
}
