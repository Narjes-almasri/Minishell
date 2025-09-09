/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 19:45:00 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 22:48:30 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_plain_text(char *str, t_expand_vars *ctx)
{
	if (ctx->i > ctx->start)
	{
		ctx->temp = ft_substr(str, ctx->start, ctx->i - ctx->start);
		if (!ctx->temp)
			return (0);
		ctx->new_result = ft_strjoin(ctx->result, ctx->temp);
		free(ctx->result);
		free(ctx->temp);
		ctx->result = ctx->new_result;
		if (!ctx->result)
			return (0);
	}
	return (1);
}

static int	append_variable(char *str, char **envp,
		t_exit_status *exit_status, t_expand_vars *ctx)
{
	if (str[ctx->i] == '$')
	{
		ctx->expanded_var = expand_single_variable(str, &ctx->i,
				envp, exit_status);
		if (ctx->expanded_var)
		{
			ctx->temp = ft_strjoin(ctx->result, ctx->expanded_var);
			free(ctx->result);
			free(ctx->expanded_var);
			ctx->result = ctx->temp;
			if (!ctx->result)
				return (0);
		}
	}
	return (1);
}

char	*expand_variables_in_string(char *str, char **envp,
		t_exit_status *exit_status)
{
	t_expand_vars	ctx;

	if (!str)
		return (NULL);
	ctx.result = ft_strdup("");
	if (!ctx.result)
		return (NULL);
	ctx.i = 0;
	while (str[ctx.i])
	{
		ctx.start = ctx.i;
		while (str[ctx.i] && str[ctx.i] != '$')
			ctx.i++;
		if (!append_plain_text(str, &ctx))
			return (NULL);
		if (!append_variable(str, envp, exit_status, &ctx))
			return (NULL);
	}
	return (ctx.result);
}

void	expand_token_variables(t_struct_token *token_list, char **envp)
{
	t_struct_token	*current;
	char			*expanded;

	current = token_list;
	while (current)
	{
		if (current->value && ft_strchr(current->value, '\''))
		{
			current = current->next;
			continue ;
		}
		else if (current->value && ft_strchr(current->value, '$'))
		{
			expanded = expand_variables_in_string(current->value, envp,
					current->exit_status);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}
