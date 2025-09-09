/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:12:36 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 19:05:50 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig;

void	define_fun(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = SIGINT;
	}
}

void	signal_function(struct sigaction *s_ctrl_back_slash,
						struct sigaction *s_ctrl_c,
						struct sigaction *s_ctrl_d)
{
	s_ctrl_c->sa_flags = 0;
	s_ctrl_back_slash->sa_flags = 0;
	s_ctrl_d->sa_flags = 0;
	sigemptyset(&s_ctrl_c->sa_mask);
	sigemptyset(&s_ctrl_d->sa_mask);
	sigemptyset(&s_ctrl_back_slash->sa_mask);
	s_ctrl_c->sa_handler = define_fun;
	s_ctrl_d->sa_handler = define_fun;
	s_ctrl_back_slash->sa_handler = SIG_IGN;
	sigaction(SIGINT, s_ctrl_c, NULL);
	sigaction(SIGTERM, s_ctrl_d, NULL);
	sigaction(SIGQUIT, s_ctrl_back_slash, NULL);
}

void	signals(void)
{
	struct sigaction	s_ctrl_c;
	struct sigaction	s_ctrl_d;
	struct sigaction	s_ctrl_back_slash;

	signal_function(&s_ctrl_back_slash, &s_ctrl_c, &s_ctrl_d);
}
