/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hered4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:37:04 by lalmahth          #+#    #+#             */
/*   Updated: 2025/08/30 13:08:10 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_heredoc_pipe(int fd[2], struct sigaction *sa)
{
	if (pipe(fd) == -1)
	{
		perror("pipe creation failed");
		exit(1);
	}
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sa->sa_handler = SIG_IGN;
	sigaction(SIGINT, sa, NULL);
}

static void	start_heredoc_child(t_handle_heredoc_leak *heredoc_temp,
								t_struct_token *token_list,
								int fd[2])
{
	pid_t				child;
	struct sigaction	sa;

	child = fork();
	if (child == -1)
	{
		perror("fork failed");
		close(fd[0]);
		close(fd[1]);
		ft_exit(heredoc_temp->token, heredoc_temp->fd,
			heredoc_temp->temp_command);
		exit(1);
	}
	if (child == 0)
	{
		sa.sa_handler = handle_heredoc_sigint;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGINT, &sa, NULL);
		close(fd[0]);
		here2(heredoc_temp, token_list, fd[1]);
	}
	else
		ex_5checking(child, heredoc_temp->fd, fd);
}

void	process_heredocs(t_handle_heredoc_leak *heredoc_temp, int num_of_del)
{
	t_struct_token		*token_list;
	int					fd[2];
	struct sigaction	sa;

	token_list = heredoc_temp->token;
	while (token_list)
	{
		if (num_of_del <= 0)
		{
			cut_to_the_first_pip(&token_list, token_list->prev_read,
				token_list->i++, token_list->n_pip);
			num_of_del = find_target_in_heredoc(token_list);
			continue ;
		}
		prepare_heredoc_pipe(fd, &sa);
		start_heredoc_child(heredoc_temp, token_list, fd);
		cut_to_the_first_pip(&token_list, token_list->prev_read,
			token_list->i++, token_list->n_pip);
		num_of_del = find_target_in_heredoc(token_list);
	}
}

void	here2(t_handle_heredoc_leak *heredoc_temp, t_struct_token *token_list,
		int fd)
{
	if (!token_list)
	{
		close(fd);
		exit(0);
	}
	starting_child(heredoc_temp, token_list, fd);
	ft_free_heredoc(heredoc_temp, fd, 0);
}

void	ex_5checking(pid_t child, t_fd *fd_h, int fd[2])
{
	int	index;
	int	status;

	index = 0;
	if (child > 0)
	{
		fd_h->fd_here_doc[index] = fd[0];
		close(fd[1]);
		index++;
		wait(&status);
	}
}
