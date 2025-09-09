CC      = cc
NAME    = minishell
CFLAGS  = -Wall -Wextra -Werror -I.

SRC = main.c \
      init_signal.c \
      simple_expand/expand_variables.c \
      simple_expand/expand_variables_2.c \
      buildin/env.c \
      buildin/env2.c \
      buildin/builtin.c \
      buildin/buildin2.c\
      buildin/exit2.c\
      buildin/exit.c\
      echo/excute_singel_command.c \
      echo/echo_quotes.c \
      echo/env_key_value.c \
      echo/quote_helpers.c \
      echo/echo_no_quotes.c \
      excute/excutttttttttttttttttttt.c \
      excute/excute.c \
      excute/helper_buildin.c\
      excute/cleanup_and_init_pip.c\
      excute/pipe_and_heredoc.c\
      excute/child.c \
      excute/export.c\
      excute/fd_read_write.c \
      excute/runs_builtin_commands.c\
      excute/runs_1_commands.c \
      heredoc/heredo.c\
      heredoc/herd2.c\
      heredoc/herd3.c\
      heredoc/hered4.c\
      heredoc/heredoc_excute.c\
      libft/ft_split.c \
      libft/ft_split_shell.c \
      libft/ft_split_shell_helper.c\
      libft/ft_split_shell_helper_2.c\
      libft/ft_split_shell_helper_3.c\
      libft/libft.c \
      libft/libft2.c \
      libft/libft3.c \
      libft/libft4.c \
      libft/libft5.c \
      libft/libft_utils.c \
      linked_list/check_command.c\
      linked_list/check_command2.c\
      linked_list/check_command3.c\
      linked_list/creat_3d_array.c \
      linked_list/command_execution.c\
      linked_list/Def_of_linked_list_variables_3.c \
      linked_list/Def_of_linked_list_variables_2.c \
      linked_list/Def_of_linked_list_variables.c \
      linked_list/init_pipex.c \
      linked_list/repalce_cmd.c \
       linked_list/repalce_cmd2.c \
      linked_list/repalce_cmd3.c \
      linked_list/command_execution2.c\
      linked_list/command_validation.c \
      linked_list/linked_list_fun.c \
      linked_list/linked_list_fun2.c \
      linked_list/readirection.c 

OBJDIR  = build
OBJ     = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
