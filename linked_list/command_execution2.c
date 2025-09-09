/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:53:21 by naalmasr          #+#    #+#             */
/*   Updated: 2025/09/01 14:28:24 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*prepare_arg_and_fd(char *input, char ***arg)
{
	t_fd	*fd;

	*arg = ft_split_shell(input);
	if (!*arg || !**arg)
	{
		free_env(*arg);
		return (NULL);
	}
	fd = malloc(sizeof(t_fd));
	if (!fd)
		return (NULL);
	init_fd(fd);
	return (fd);
}

t_struct_token	*prepare_token_list(t_fd *fd,
	char **arg)
{
	t_struct_token	*token_list;

	token_list = NULL;
	token_list = fill_token_list(token_list, arg);
	if (!token_list)
	{
		free(fd);
		return (NULL);
	}
	return (token_list);
}

char	**start_processing(char *input, char **envp, t_exit_status *exit_status)
{
	t_struct_token	*token_list;
	char			**arg;
	t_fd			*fd;
	char			**t;

	fd = prepare_arg_and_fd(input, &arg);
	if (!fd)
		return (envp);
	token_list = prepare_token_list(fd, arg);
	if (!token_list)
		return (envp);
	exit_status_tokens(token_list, exit_status);
	t = start_execution_cmd(fd, token_list, envp, arg);
	if (t != NULL)
		return (t);
	return (NULL);
}
