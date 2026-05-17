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

void clear_screen(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void print_line_with_delay(const char *line, const char *color, int delay_ms)
{
    printf("%s%s%s%s\n", BOLD, color, line, RESET);
    fflush(stdout);
    usleep(delay_ms * 1000);
}

void print_animated_banner(void)
{
    clear_screen();
    const char *colors[] = {
        BRIGHT_CYAN,
        BRIGHT_CYAN,
        BRIGHT_MAGENTA,
        BRIGHT_MAGENTA,
        BRIGHT_YELLOW,
        BRIGHT_YELLOW,
        BRIGHT_CYAN
    };
    
    const char *banner[] = {
        "",
        "  ███╗   ███╗██╗███╗   ██╗██╗███╗   ██╗███████╗██╗  ██╗███████╗██╗     ██╗     ",
        "  ████╗ ████║██║████╗  ██║██║████╗  ██║██╔════╝██║  ██║██╔════╝██║     ██║     ",
        "  ██╔████╔██║██║██╔██╗ ██║██║██╔██╗ ██║███████╗███████║█████╗  ██║     ██║     ",
        "  ██║╚██╔╝██║██║██║╚██╗██║██║██║╚██╗██║╚════██║██╔══██║██╔══╝  ██║     ██║     ",
        "  ██║ ╚═╝ ██║██║██║ ╚████║██║██║ ╚████║███████║██║  ██║███████╗███████╗███████╗",
        "  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝",
        ""
    };
    
   int banner_lines = sizeof(banner) / sizeof(banner[0]);
int color_lines  = sizeof(colors) / sizeof(colors[0]);
    
 for (int i = 0; i < banner_lines; i++)
{
    const char *col = (i < color_lines) ? colors[i] : BRIGHT_WHITE;
    print_line_with_delay(banner[i], col, 100);
}
    
    usleep(300000);
    printf("                            %s%s    🌻%s\n", BRIGHT_YELLOW, BOLD, RESET);
    usleep(200000);
    
    printf("%s%s                  A beautiful shell experience%s\n\n", 
           DIM, BRIGHT_WHITE, RESET);
    
    usleep(400000);
    
    printf("%s                      Type %sexit%s to quit%s\n\n\n", 
           DIM, BRIGHT_YELLOW, DIM, RESET);
}


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
	print_animated_banner();
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
