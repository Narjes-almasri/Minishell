/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:59:13 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 20:39:17 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*call_access(char *path, char *command)
{
	char	*tmp;
	char	*valid_path;

	tmp = NULL;
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	valid_path = ft_strjoin(tmp, command);
	free(tmp);
	if (!valid_path)
		return (NULL);
	if (access(valid_path, X_OK) == 0)
		return (valid_path);
	free(valid_path);
	valid_path = NULL;
	return (NULL);
}

char	*valid_command_path(char *command, char **find_path)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (find_path[i] != NULL)
	{
		tmp = call_access(find_path[i], command);
		if (tmp != NULL)
		{
			return (tmp);
		}
		i++;
	}
	if (tmp)
		free(tmp);
	return (NULL);
}

static char	*get_paths_from_env(char *command, char **envp)
{
	char	*path;
	char	**find_path;

	path = get_env(envp, "PATH");
	if (!path)
	{
		write(2, "Minishell:", 11);
		write(2, command, ft_strlen(command));
		write(2, " No such file or directory\n", 28);
		return (NULL);
	}
	find_path = ft_split(path, ':');
	if (!find_path)
		return (NULL);
	return ((char *)find_path);
}

char	*find_command_path(char *command, char **envp, int f)
{
	char	**find_path;
	char	*valid_path;

	find_path = (char **)get_paths_from_env(command, envp);
	if (!find_path)
		return (NULL);
	if (command[0] == '\0')
	{
		free_env(find_path);
		return (NULL);
	}
	valid_path = valid_command_path(command, find_path);
	if (!valid_path)
	{
		free_env(find_path);
		if (f == 1)
		{
			write(2, command, ft_strlen(command));
			write(2, "  : command not found\n", 23);
		}
		return (NULL);
	}
	free_env(find_path);
	return (valid_path);
}

int	count_pipe_segments(t_struct_token *token_list)
{
	int	pipe_count;

	pipe_count = 0;
	while (token_list != NULL)
	{
		if (ft_strcmp(token_list->type, "|") == 0)
			pipe_count++;
		token_list = token_list->next;
	}
	return (pipe_count + 1);
}
