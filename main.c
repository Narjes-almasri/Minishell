/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:18:22 by naalmasr          #+#    #+#             */
/*   Updated: 2025/09/01 15:32:22 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(char *input, char ***env, char **test,
		t_exit_status *exit_status)
{
	while (1)
	{
		g_sig = 0;
		signals();
		input = readline("🌻Minishell🌻 ");
		if (g_sig == SIGINT)
			exit_status->value = 130;
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		test = start_processing(input, *env, exit_status);
		if (test)
			*env = test;
		free(input);
		if (!test)
			break ;
	}
}

int	main(int ac, char **argv, char **envp)
{
	char			*input;
	char			**env;
	char			**test;
	t_exit_status	*exit_status;
	int				status;

	input = NULL;
	test = NULL;
	status = 0;
	(void)argv;
	if (ac != 1)
		return (0);
	env = create_env(envp);
	if (!env)
		return (1);
	exit_status = malloc(sizeof(t_exit_status));
	if (!exit_status)
		return (1);
	exit_status->value = 0;
	shell_loop(input, &env, test, exit_status);
	status = exit_status->value;
	free(exit_status);
	free_env(env);
	clear_history();
	return (status);
}
