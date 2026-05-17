/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:54:35 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 13:01:56 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_fun(t_struct_token *token_list)
{
	char	*get_pwd;

	get_pwd = getcwd(NULL, 0);
	if (get_pwd)
	{
		write(token_list->fd_write, get_pwd, ft_strlen(get_pwd));
		write(token_list->fd_write, "\n", 1);
		free(get_pwd);
	}
	else
		printf("pwd error");
}

int	cd_chdir(t_struct_token *token_list)
{
	printf("minishell: cd: %s: No such file or directory\n",
		token_list->value);
	token_list->exit_status->value = 1;
	return (-1);
}

char	*cd_get_path(char *path, char **env)
{
	path = get_env(env, "HOME");
	if (!path)
	{
		printf("error in cd_get_path\n");
		return (NULL);
	}
	return (path);
}

int	cd_fun(t_struct_token *token_list, char **env)
{
	char	*path;

	path = NULL;
	if (token_list->next == NULL)
	{
		path = cd_get_path(path, env);
		if (!path)
			return (-1);
	}
	else if (token_list->next != NULL)
	{
		token_list = token_list->next;
		path = token_list->value;
		if (token_list->next != NULL && ft_strcmp(token_list->next->type,
				">") != 0 && ft_strcmp(token_list->next->type, "|") != 0)
		{
			write(2, "minishell: cd: too many arguments\n", 35);
			token_list->exit_status->value = 1;
			return (-1);
		}
	}
	if (chdir(path) != 0)
		cd_chdir(token_list);
	return (0);
}
