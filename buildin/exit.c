/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:35:25 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/29 13:57:30 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_tokens(t_struct_token *token_list,
						t_exit_status *exit_status)
{
	t_struct_token	*tmp;

	tmp = token_list;
	while (tmp)
	{
		tmp->exit_status = exit_status;
		tmp = tmp->next;
	}
}

int	search_operates(t_struct_token *t)
{
	int	i;

	i = 0;
	while (t != NULL)
	{
		if (ft_strcmp(t->type, "|") == 0 || ft_strcmp(t->type, ">>") == 0
			|| ft_strcmp(t->type, ">") == 0 || ft_strcmp(t->type, "<<") == 0
			|| ft_strcmp(t->type, "<") == 0)
		{
			return (0);
		}
		i++;
		t = t->next;
	}
	return (1);
}

int	ft_exit_shell(t_struct_token *tmp, t_struct_token *line)
{
	int	i;

	i = 0;
	tmp = line;
	if (!line)
		return (1);
	if ((line->n_pip != 1 || !search_operates(tmp)))
		return (0);
	if (ft_strcmp(line->value, "exit") == 0 && !line->next)
	{
		printf("exit\n");
		return (1);
	}
	if ((ft_strcmp(line->value, "exit") == 0 || ft_strcmp(line->value,
				"'exit'") == 0) && ft_strcmp(line->value, "|") != 0)
	{
		line = line->next;
		i = ft_numeric(i, line);
		if (i < 1)
			return (0);
		ft_putendl_fd("exit", 1);
		return (i);
	}
	return (0);
}

int	parse_and_convert(const char *str, int sign, long long *res)
{
	unsigned long long	num;

	num = 0;
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		if ((sign == 1 && num > LLONG_MAX)
			|| (sign == -1 && num > (unsigned long long)LLONG_MAX + 1ULL))
			return (0);
		str++;
	}
	if (!ft_isdigit(*str) && *str != '\0')
		return (0);
	if (sign == 1)
		*res = (long long)num;
	else
		*res = -(long long)num;
	return (1);
}

int	ft_str_to_ll(const char *str, long long *res)
{
	int	sign;

	sign = 1;
	if (*str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (parse_and_convert(str, sign, res));
}
