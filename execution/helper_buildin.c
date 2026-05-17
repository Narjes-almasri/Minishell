/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_buildin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:23:17 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 15:26:45 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_for_heredoc(t_struct_token *token_list)
{
	while (token_list != NULL && token_list->next != NULL)
	{
		if (ft_strcmp(token_list->type, "<<") == 0)
			return (1);
		token_list = token_list->next;
	}
	return (0);
}

void	check_the_priority(t_struct_token *token_list, int *fd, int *h)
{
	int	herdoc;

	herdoc = 0;
	while (token_list != NULL)
	{
		if (ft_strcmp(token_list->type, "<<") == 0)
		{
			herdoc = 1;
		}
		else if (ft_strcmp(token_list->type, "<") == 0)
		{
			herdoc = 0;
		}
		token_list = token_list->next;
	}
	if (herdoc == 1)
		*fd = -1;
	else
		*h = 0;
}

int	is_buildin(t_struct_token *token_list)
{
	if (!token_list || !token_list->value)
		return (0);
	if (ft_strcmp(token_list->value, "export") == 0
		|| ft_strcmp(token_list->value, "unset") == 0)
		return (1);
	if (ft_strcmp(token_list->value, "pwd") == 0 || ft_strcmp(token_list->value,
			"cd") == 0 || ft_strcmp(token_list->value, "exit") == 0)
		return (1);
	if (ft_strcmp(token_list->value, "echo") == 0)
		return (1);
	if (ft_strcmp(token_list->value, "env") == 0)
		return (1);
	return (0);
}

char	**unset_fun(t_struct_token *token_list, char **env)
{
	while ((token_list != NULL) && ft_strcmp(token_list->value, "|") != 0)
	{
		if (ft_strcmp(token_list->value, "unset") == 0)
		{
			token_list = token_list->next;
			continue ;
		}
		else
		{
			env = handle_unset_fun(env, token_list->value,
					ft_strlen(token_list->value));
		}
		token_list = token_list->next;
	}
	return (env);
}
