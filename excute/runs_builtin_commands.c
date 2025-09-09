/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:26:54 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 12:14:46 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**handle_export_unset(t_struct_token *token_list,
									char ****whole_command,
									char **env)
{
	if (token_list->value && ft_strncmp(token_list->value, "export", 6) == 0)
		env = export_fun(whole_command, token_list, env);
	else
		env = unset_fun(token_list, env);
	return (env);
}

static char	**handle_cd_command(t_struct_token *token_list, char **env)
{
	char	*v;

	if (cd_fun(token_list, env) != -1)
	{
		v = getcwd(NULL, 0);
		env = check_var_existens(env, "PWD=", v, 0);
		free(v);
		return (env);
	}
	return (env);
}

static char	**handle_simple_commands(t_struct_token *token_list, char **env)
{
	if (ft_strcmp(token_list->value, "pwd") == 0)
	{
		pwd_fun(token_list);
		return (env);
	}
	if (ft_strcmp(token_list->value, "echo") == 0)
	{
		excute_echo_command(token_list, env, token_list->fd_write);
		return (env);
	}
	if (ft_strcmp(token_list->value, "env") == 0)
	{
		print_env(env, token_list->fd_write);
		return (env);
	}
	return (env);
}

char	**build_in_fun(t_struct_token *tmp, t_struct_token *token_list,
		char ****whole_command, char **env)
{
	if (!token_list || !token_list->value)
		return (env);
	if (ft_strncmp(token_list->value, "export", 6) == 0
		|| (ft_strncmp(token_list->value, "unset", 5) == 0
			&& token_list->next != NULL))
	{
		return (handle_export_unset(token_list, whole_command, env));
	}
	if (ft_strcmp(token_list->value, "cd") == 0)
	{
		return (handle_cd_command(token_list, env));
	}
	if (ft_strcmp(token_list->value, "exit") == 0)
		ft_exit_shell(tmp, token_list);
	return (handle_simple_commands(token_list, env));
}
