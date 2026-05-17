CC      = cc
NAME    = minishell
CFLAGS  = -Wall -Wextra -Werror -I./include -I/opt/homebrew/opt/readline/include -I/usr/local/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib -L/usr/local/opt/readline/lib -lreadline

SRC = main.c \
      signals/init_signal.c \
      expansion/expand_variables.c \
      expansion/expand_variables_2.c \
      builtins/env.c \
      builtins/env2.c \
      builtins/builtin.c \
      builtins/buildin2.c\
      builtins/exit2.c\
      builtins/exit.c\
      builtins/echo/excute_singel_command.c \
      builtins/echo/echo_quotes.c \
      builtins/echo/env_key_value.c \
      builtins/echo/quote_helpers.c \
      builtins/echo/echo_no_quotes.c \
      execution/excutttttttttttttttttttt.c \
      execution/excute.c \
      execution/helper_buildin.c\
      execution/cleanup_and_init_pip.c\
      execution/pipe_and_heredoc.c\
      execution/child.c \
      execution/export.c\
      execution/fd_read_write.c \
      execution/runs_builtin_commands.c\
      execution/runs_1_commands.c \
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
      parsing/check_command.c\
      parsing/check_command2.c\
      parsing/check_command3.c\
      parsing/creat_3d_array.c \
      parsing/command_execution.c\
      parsing/Def_of_linked_list_variables_3.c \
      parsing/Def_of_linked_list_variables_2.c \
      parsing/Def_of_linked_list_variables.c \
      parsing/init_pipex.c \
      parsing/repalce_cmd.c \
      parsing/repalce_cmd2.c \
      parsing/repalce_cmd3.c \
      parsing/command_execution2.c\
      parsing/command_validation.c \
      parsing/linked_list_fun.c \
      parsing/linked_list_fun2.c \
      parsing/readirection.c 

OBJDIR  = build
OBJ     = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


all: $(NAME)
$(NAME): $(OBJ)
	@echo "$(YELLOW)🔧 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)✅ Build complete: $(NAME)$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)🧩 Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(YELLOW)🗑️ Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re