/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:01:38 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 16:09:13 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(t_fd *fd)
{
	fd->index_of_input = 0;
	fd->index_of_outfile = 0;
	fd->num_of_index = 0;
	fd->f = 0;
	fd->fd_here_doc = NULL;
}

int	add_tokens_from_args(t_struct_token **token_list, char **arg)
{
	int	i;
	int	re;

	i = 0;
	re = 0;
	while (arg[i] != NULL)
	{
		if (!arg[i + 1])
			re = add_token(token_list, arg[i], NULL, 0);
		else
			re = add_token(token_list, arg[i], arg[i + 1], 1);
		if (re == -1)
		{
			safe_free_token_list(token_list);
			free_env(arg);
			return (-1);
		}
		i++;
	}
	return (re);
}

t_struct_token	*fill_token_list(t_struct_token *token_list, char **arg)
{
	t_struct_token	*tmp;
	int				re;
	int				i;

	re = add_tokens_from_args(&token_list, arg);
	if (re == -1)
		return (NULL);
	i = 0;
	tmp = token_list;
	while (arg[i])
		i++;
	while (tmp)
	{
		tmp->len = i;
		tmp->env = NULL;
		tmp->n_pip = re + 1;
		tmp->index = 0;
		tmp->n_column = find_number_of_command(token_list);
		tmp = tmp->next;
	}
	return (token_list);
}

char	***init_command_block(int n_column)
{
	char	***command_block;
	int		j;

	command_block = malloc(sizeof(char **) * 2);
	if (!command_block)
		return (NULL);
	command_block[0] = malloc(sizeof(char *) * (n_column + 1));
	if (!command_block[0])
		return (NULL);
	j = 0;
	while (j < n_column + 1)
	{
		command_block[0][j] = NULL;
		j++;
	}
	command_block[1] = NULL;
	return (command_block);
}

char	****init_execute_commands(t_struct_token *token_list)
{
	char	****whole_command;
	int		i;

	whole_command = malloc(sizeof(char ***) * (token_list->n_pip + 1));
	if (!whole_command)
		return (NULL);
	i = 0;
	while (i < token_list->n_pip)
	{
		whole_command[i] = init_command_block(token_list->n_column);
		if (!whole_command[i])
			return (NULL);
		i++;
	}
	whole_command[i] = NULL;
	return (whole_command);
}
