/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:56:58 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 13:27:57 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	failed_fd(char *filename, t_fd *fd, t_struct_token *token_list)
{
	free(filename);
	if (fd->fd_in != -1)
		close(fd->fd_in);
	if (fd->fd_out != -1)
		close(fd->fd_out);
	token_list->exit_status->value = 1;
	fd->fd_in = -1;
	fd->fd_out = -1;
	write(2, "Permission denied\n", 19);
	return (0);
}

int	check_expand_redirection(t_struct_token *token_list, t_fd *fd,
		char *filename)
{
	int	fd_;

	if (!token_list->next)
	{
		printf("minishell: syntax error no infile\n");
		return (0);
	}
	token_list = token_list->next;
	if (fd->fd_out > 2)
		close(fd->fd_out);
	filename = ft_strdup(token_list->value);
	if (!filename)
		return (0);
	fd_ = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_ < 0)
	{
		printf("minishell: %s : Can not create a file or directory\n",
			filename);
		free(filename);
		return (0);
	}
	free(filename);
	fd->fd_out = fd_;
	return (1);
}

int	check_out_redirection(t_struct_token *token_list, t_fd *fd, char *filename)
{
	if (fd->fd_out > 2)
		close(fd->fd_out);
	if (ft_strcmp(token_list->value, ">") == 0 && token_list->next != NULL)
	{
		token_list = token_list->next;
		filename = ft_strdup(token_list->value);
		if (!filename)
		{
			fd->fd_out = -1;
			return (0);
		}
		fd->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd->fd_out < 0)
			return (failed_fd(filename, fd, token_list));
	}
	else
	{
		printf("minishell: syntax error no outfile\n");
		fd->fd_out = -1;
		return (0);
	}
	free(filename);
	return (1);
}

int	check_in_redirection_internal(t_struct_token *token_list, t_fd *fd,
		char *filename)
{
	token_list = token_list->next;
	if (!token_list)
	{
		printf("minishell: syntax error no outfile\n");
		return (0);
	}
	filename = ft_strdup(token_list->value);
	if (!filename)
	{
		fd->fd_in = -1;
		return (0);
	}
	if (fd->fd_in > 2)
	{
		close(fd->fd_in);
		if (fd->fd_out != -1)
			close(fd->fd_out);
	}
	fd->fd_in = open(filename, O_RDONLY);
	if (fd->fd_in < 0)
		return (failed_fd(filename, fd, token_list));
	free(filename);
	return (1);
}

int	check_in_redirection(t_struct_token *token_list, t_fd *fd)
{
	char	*filename;

	fd->fd_in = -1;
	fd->fd_out = -1;
	filename = NULL;
	while (token_list != NULL && ft_strcmp(token_list->type, "|") != 0)
	{
		if (ft_strcmp(token_list->type, "<") == 0)
		{
			if (!check_in_redirection_internal(token_list, fd, filename))
				return (0);
		}
		if (ft_strcmp(token_list->type, ">") == 0
			&& !check_out_redirection(token_list, fd, filename))
		{
			return (0);
		}
		if (ft_strcmp(token_list->type, ">>") == 0
			&& !check_expand_redirection(token_list, fd, filename))
		{
			return (0);
		}
		token_list = token_list->next;
	}
	return (1);
}
