/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_fun2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:46:38 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 19:23:00 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_struct_token	*creat_token(char *s, char *next, int *num_of_pipe)
{
	int				i;
	t_struct_token	*token;

	if (!s)
		return (NULL);
	token = malloc(sizeof(t_struct_token));
	if (!token)
		return (NULL);
	if (init_tokens_2(token, s) == -1)
		return (NULL);
	i = is_need_input(s, 2, next);
	if (i == -1)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	token->type = identify_value_type(s, next, i, num_of_pipe);
	if (!token->type)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	return (token);
}

int	handle_token_error(t_struct_token **head)
{
	printf(" ⚠️  syntax error in filling the tokens ⚠️ \n");
	safe_free_token_list(head);
	*head = NULL;
	return (-1);
}

int	add_token(t_struct_token **head, char *s, char *next, int f)
{
	static int		num_of_pipe = 0;
	int				re;
	t_struct_token	*tmp;
	t_struct_token	*new;

	re = 0;
	new = creat_token(s, next, &num_of_pipe);
	re = num_of_pipe;
	if (f == 0)
		num_of_pipe = 0;
	if (!new)
		return (handle_token_error(head));
	if (!*head)
	{
		*head = new;
		return (re);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (re);
}
