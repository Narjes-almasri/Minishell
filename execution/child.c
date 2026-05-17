/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalmahth <lalmahth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:12:22 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/29 15:38:21 by lalmahth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_builtin_command(t_struct_token *token_list,
		char ****commands, char **env, t_struct_token *tmp)
{
	int	status;

	status = 0;
	build_in_fun(tmp, token_list, commands, env);
	if (tmp->exit_status->value != 0
		&& check_command_after_exit(token_list) == 1)
		status = tmp->exit_status->value;
	free_env(env);
	free(token_list->exit_status);
	free_whole_command(commands, tmp);
	safe_free_token_list(&tmp);
	exit(status);
}

static char	*get_command_path(t_struct_token *token_list, char ****commands,
		char **env)
{
	char	*find_path;

	find_path = NULL;
	if (token_list->value != NULL && (token_list->value[0] == '/'
			|| token_list->value[0] == '.'))
		find_path = token_list->value;
	else
		find_path = find_command_path(commands[token_list->i][0][0], env, 1);
	return (find_path);
}

static void	handle_command_not_found(t_struct_token *token_list, char **env,
		char ****commands, t_struct_token *tmp)
{
	if (token_list->next != NULL && ft_strcmp(token_list->next->value,
			"|") == 0)
	{
		free_env(env);
		free_whole_command(commands, tmp);
		free(token_list->exit_status);
		safe_free_token_list(&tmp);
		exit(0);
	}
	free_env(env);
	free_whole_command(commands, tmp);
	free(token_list->exit_status);
	safe_free_token_list(&tmp);
	exit(127);
}

static void	signals_and_execute(char *find_path, t_struct_token *token_list,
		char ****commands, t_struct_token *tmp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (execve(find_path, commands[token_list->i][0], tmp->env) == -1)
	{
		perror("execve failed");
		free_env(tmp->env);
		free(token_list->exit_status);
		free_whole_command(commands, token_list);
		safe_free_token_list(&tmp);
		exit(1);
	}
}

void	execute_single_command(t_struct_token *token_list, char ****commands,
		char **env, t_struct_token *tmp)
{
	char	*find_path;

	if (is_buildin(token_list))
	{
		handle_builtin_command(token_list, commands, env, tmp);
	}
	find_path = get_command_path(token_list, commands, env);
	if (!find_path || ft_strcmp(find_path, "/usr/local/sbin/") == 0)
	{
		handle_command_not_found(token_list, env, commands, tmp);
	}
	tmp->env = env;
	signals_and_execute(find_path, token_list, commands, tmp);
}
