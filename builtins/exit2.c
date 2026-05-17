/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:48:41 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 13:53:29 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_num_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_numeric(int i, t_struct_token *line)
{
	long long	num;

	(void)i;
	if (!ft_str_to_ll(line->value, &num))
	{
		line->exit_status->value = 2;
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(line->value, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (1);
	}
	line->exit_status->value = (int)(num % 256);
	line = line->next;
	if (line != NULL && ft_strcmp(line->value, "|") != 0
		&& ft_strcmp(line->value, ">") != 0 && ft_strcmp(line->value,
			">> ") != 0)
	{
		line->exit_status->value = 1;
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
		return (0);
	}
	return (1);
}

void	free_fd_arg(t_fd *fd, char **arg, t_struct_token *tokens, char ****cmd)
{
	if (fd != NULL)
		free(fd);
	if (arg != NULL)
		free_tokens_split2(arg);
	if (cmd != NULL)
		free_whole_command(cmd, tokens);
}
