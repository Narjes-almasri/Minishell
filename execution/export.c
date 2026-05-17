/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:39:44 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:57:20 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**process_export_args(t_struct_token *token_list, char **env)
{
	char	**t;
	int		k;

	k = 0;
	while ((token_list != NULL) && ft_strcmp(token_list->value, "|") != 0)
	{
		if (ft_strcmp(token_list->value, "export") == 0 && k == 0)
		{
			token_list = token_list->next;
			k++;
		}
		if (token_list && token_list->value)
		{
			t = handle_export_command(token_list->value, env);
			if (t)
				env = t;
		}
		if (token_list)
			token_list = token_list->next;
	}
	return (env);
}

char	**export_fun(char ****commands, t_struct_token *token_list, char **env)
{
	int				k;
	t_struct_token	*temp;

	k = 0;
	temp = token_list;
	if (ft_strcmp(commands[temp->i][0][0], "export") == 0
		&& !commands[temp->i][0][1])
	{
		while (env[k] != NULL)
		{
			if (env[k][0] != '\0')
			{
				write(token_list->fd_write, "declare -x \"", 12);
				write(token_list->fd_write, env[k], ft_strlen(env[k]));
				write(token_list->fd_write, "\"\n", 2);
			}
			k++;
		}
		return (env);
	}
	return (process_export_args(token_list, env));
}
