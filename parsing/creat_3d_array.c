/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_3d_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:09:31 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 12:24:41 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_number_of_command(t_struct_token *token_list)
{
	int	num;
	int	max;

	num = 0;
	max = 0;
	while (token_list != NULL)
	{
		if (ft_strcmp(token_list->type, "command") == 0
			|| ft_strcmp(token_list->type, "\"") == 0
			|| ft_strcmp(token_list->type, "\'") == 0)
		{
			num++;
		}
		if (ft_strcmp(token_list->type, "|") == 0)
		{
			if (num > max)
				max = num;
			num = 0;
		}
		token_list = token_list->next;
	}
	if (num > max)
		max = num;
	return (max);
}

void	free_whole_command(char ****commands, t_struct_token *token_list)
{
	token_list->i = 0;
	if (token_list->n_column == 0)
		token_list->n_column = 1;
	if (!commands)
		return ;
	while (token_list->i < token_list->n_pip)
	{
		if (commands[token_list->i])
		{
			if (commands[token_list->i][0])
			{
				token_list->index = 0;
				while (token_list->index < token_list->n_column)
				{
					if (commands[token_list->i][0][token_list->index])
						free(commands[token_list->i][0][token_list->index]);
					token_list->index++;
				}
				free(commands[token_list->i][0]);
			}
			free(commands[token_list->i]);
		}
		token_list->i++;
	}
	free(commands);
}

int	is_command_token(char *type)
{
	return (ft_strcmp(type, "command") == 0
		|| ft_strcmp(type, "echo") == 0
		|| ft_strcmp(type, "\"") == 0
		|| ft_strcmp(type, "\'") == 0);
}

void	is_echo(t_struct_token *token_list)
{
	if (ft_strcmp(token_list->type, "echo") == 0
		&& token_list->next != NULL)
		token_list = token_list->next;
}

void	fill_the_3d_array(t_struct_token *token_list, char ****commands,
	int n_pip, int n_column)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token_list != NULL && i <= n_pip)
	{
		if (ft_strcmp(token_list->type, "|") == 0)
		{
			commands[i][0][j] = NULL;
			i++;
			j = 0;
		}
		else if (is_command_token(token_list->type))
		{
			is_echo(token_list);
			if (j < n_column)
			{
				commands[i][0][j] = ft_strdup(token_list->value);
				j++;
			}
		}
		token_list = token_list->next;
	}
	commands[i][0][j] = NULL;
}
