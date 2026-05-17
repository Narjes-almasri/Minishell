/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:05:26 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 19:23:17 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_free_token_list(t_struct_token **head)
{
	t_struct_token	*tmp;

	if (!head || !*head)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		if ((*head)->value)
		{
			free((*head)->value);
			(*head)->value = NULL;
		}
		if ((*head)->type)
		{
			free((*head)->type);
			(*head)->type = NULL;
		}
		free(*head);
		*head = tmp;
	}
}

int	handle_double_greater(char *s, int i)
{
	if (s[i + 2] != '\0')
		return (-1);
	return (2);
}

int	is_need_input(char *s, int f, char *next)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '<' && s[i] != '>')
		i++;
	if (s[i] == '\0')
		return (0);
	if (s[i + 1] != '\0' && s[i] == '>' && s[i + 1] == '>')
		handle_double_greater(s, i);
	if (s[i + 1] != '\0' && s[i] == '<' && s[i + 1] == '<')
	{
		if (s[i + 2] != '\0' || !next)
			return (-1);
		return (2);
	}
	if (s[i + 1] == '\0' && s[i] == '>')
		return (2);
	if (s[i + 1] == '\0' && s[i] == '<')
		return (2);
	if (s[i] == '|' && f != 0)
		return (2);
	return (0);
}

int	init_tokens_2(t_struct_token *token, char *s)
{
	token->type = NULL;
	token->value = NULL;
	token->next = NULL;
	token->index = 0;
	if (s)
		token->value = ft_strdup(s);
	if (!token->value)
	{
		free(token);
		return (-1);
	}
	return (0);
}
