/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalmasr <naalmasr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:05:53 by naalmasr          #+#    #+#             */
/*   Updated: 2025/08/30 23:01:21 by naalmasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_exit_status
{
	int						value;
}							t_exit_status;

extern int					g_sig;

typedef struct s_struct_token
{
	char					*value;
	char					*type;
	char					*delimiter;
	char					**env;
	char					*input_afterhere;
	int						n_column;
	struct s_struct_token	*next;
	int						flag_heredoc;
	int						i;
	t_exit_status			*exit_status;
	int						heredoc;
	int						prev_read;
	int						n_pip;
	int						fd_read;
	int						fd_write;
	int						index;
	int						len;
	int						*num_of_del;
	int						heredoc_expand;
	int						heredoc_pipe[2];
}							t_struct_token;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_fd
{
	int						fd_in;
	int						fd_out;
	int						f;
	int						index_of_input;
	int						index_of_outfile;
	int						num_of_pipe;
	int						num_of_del_here;
	int						num_of_index;
	int						*fd_here_doc;
	int						fd_pipe[2];
}							t_fd;

typedef struct s_expand_vars
{
	char	*result;
	char	*temp;
	char	*expanded_var;
	char	*new_result;
	int		i;
	int		start;
}	t_expand_vars;

typedef struct s_signals
{
	struct sigaction		s_ctrl_c;
	struct sigaction		s_ctrl_d;
	struct sigaction		s_ctrl_back_slash;
}							t_signals;

typedef struct s_handle_heredoc_leak
{
	t_fd					*fd;
	t_struct_token			*token;
	int						i;
	char					****temp_command;
	char					**env_temp;
}							t_handle_heredoc_leak;

t_struct_token	*fill_token_list(t_struct_token *token_list, char **arg);
t_struct_token	*creat_token(char *s, char *next, int *num_of_pipe);
t_struct_token	*handle_token_errors(t_struct_token *token, int i);
long int		ft_atol(char *str);
long int		ft_return_nbr(char *str, int i, int sign);
int				check_digit_and_print_later(char *value, int fd, int *i);
int				search_for_heredoc(t_struct_token *token_list);
void			execute_child(t_struct_token *token_list, t_fd *fd,
					char ****commands,
					t_struct_token *tmp);
int				check_command_after_exit(t_struct_token *token_list);
void			execute_single_command(t_struct_token *token_list,
					char ****commands,
					char **env, t_struct_token *tmp);
//////////////////// child.c / command_execution.c ////////////////////
char			**handle_single_command(t_struct_token *token_list,
					t_handle_heredoc_leak *heredoc_temp);
int				handle_heredoc_collection(t_struct_token *token_list,
					char **env, t_fd *fd, char ****commands);
void			handle_process_cleanup(t_struct_token *token_list);
void			wait_for_processes(t_fd *fd, t_struct_token *token_list);
char			**excuttttttttttttttttttttttttttttt(t_fd *fd,
					t_struct_token *token_list, char ****commands, char **env);
//////////////////// pipe_and_heredoc.c ////////////////////
void			setup_heredoc_memory(t_fd *fd, int num_of_del);
void			process_heredoc_if_needed(t_handle_heredoc_leak *heredoc_temp,
					int num_of_del);
void			find_heredoc(t_handle_heredoc_leak *heredoc_temp);
int				setup_pipe_if_needed(t_fd *fd, int i,
					int num_of_pipe);
void			handle_pipe_cleanup(t_fd *fd,
					t_struct_token *token_list, int i,
					int num_of_pipe);
void			runs_commads(t_fd *fd, t_struct_token *token_list,
					char ****commands, char **env);
//////////////////// cleanup_and_init.c ////////////////////
void			close_token_read(t_struct_token *token_list);
void			close_fd_in_out(t_fd *fd);
void			close_fd_pipes(t_fd *fd);
void			clean_and_close(t_fd *fd,
					t_struct_token *token_list);
void			init_tokens(t_struct_token *token_list);
int				handle_exit_shell(t_struct_token *tmp, char **arg,
					t_struct_token *token_list);
int				handle_check_command(t_struct_token **q,
					char **envp, t_fd *fd, char **arg);
int				handle_pipe_validation(t_struct_token *token_list,
					t_fd *fd, char **arg);
void			ft_free_heredoc(t_handle_heredoc_leak *heredoc_temp,
					int fd, int s_exit);
void			exit_status_tokens(t_struct_token *token_list,
					t_exit_status *exit_status);
int				ft_exit_shell(t_struct_token *tmp, t_struct_token *line);
int				failed(char **s, char **tokens, int t);
int				init_temp_token(char **temp_token, int t,
					char **tokens);				
int				ft_numeric(int i, t_struct_token *line);
void			free_fd_arg(t_fd *fd, char **arg,
					t_struct_token *tokens, char ****cmd);
////////////exit.c////////////////////////
int				handle_operator_token(char *input, int *i,
					char **tokens, int *t);
void			handle_nonfinal_heredoc(t_struct_token **token_list,
					int *num_of_del,
					int fd,
					t_handle_heredoc_leak *heredoc_temp);
int				parse_and_convert(const char *str, int sign,
					long long *res);
int				ft_str_to_ll(const char *str, long long *res);
char			**update_env(char **env, char *var, char *value);
char			*return_var(char *saved_token, int var_len);
char			*return_value(char *value, char **envp);
char			**handle_export_command(char *saved_token,
					char **env);
char			**check_var_existens(char **env, char *var,
					char *value, int unsetf);
/////////////builtin.c/////////
char			*check_first_char_value(char *value);
int				extract_and_validate_var(char *saved_token,
					char **var, int *var_len);
char			*extract_value(char *saved_token, int var_len);
int				is_matching_var(char *env_entry, char *var,
					int var_len);
char			**copy_and_extend_env(char **env, int *j);
void			pwd_fun(t_struct_token *token_list);
int				cd_fun(t_struct_token *token_list, char **env);
char			**handle_unset_fun(char **env, char *var,
					int var_len);
void			freee(char **copy, int i);
char			**cpy_env(char **env);
char			**create_env(char **env);
void			free_env(char **env);
/////////////env.c//////////////
int				are_quotes_balanced(char *str);
char			*extract_var_name(char *str, int start_pos);
void			process_string(t_struct_token *tokens, char **envp,
					int fd, int expand_vars);
void			process_quoted_string(t_struct_token *tokens,
					char *str, char **envp, int fd);
void			process_unquoted_string(t_struct_token *token_list,
					char *str, char **envp, int fd);
int				check_n_flag(char *s);
int				validate_quotes_in_command(t_struct_token *token_list);
void			process_echo_arguments(t_struct_token *token_list,
					char **envp, int fd);
void			print_whats_inside_qouts(char *s,
					int f_idenify_qout, int fd);
char			*get_env(char **envp, const char *key);
char			*get_key(char *key, int size, int f, int i);
void			excute_echo_command_qoution(t_struct_token *tokns,
					char *value, char **envp, int fd);
void			excute_echo_command_without_q(t_struct_token *tokens,
					char *value, char **envp, int fd);
char			*excute_echo_command_doller(char *value,
					char **envp, int fd);
int				check_n(char *s);
int				check_n_e(char *s);
void			excute_echo_command(t_struct_token *token_list,
					char **envp, int fd);
void			excute_echo_command_2(t_struct_token *token_list,
					char **envp, int fd);
void			excute_echo_command_qoution(t_struct_token *tokens,
					char *value, char **envp, int fd);
//////////////excute_singel_command.c///////////////////
void			ft_exit(t_struct_token *token_list, t_fd *fd,
					char ****commands);
///////child.c/////
char			**excuttttttttttttttttttttttttttttt(t_fd *fd,
					t_struct_token *token_list, char ****commands,
					char **env);
void			find_here_doc(t_struct_token *token_list, t_fd *fd,
					char **env);
void			runs_commads(t_fd *fd, t_struct_token *token_list,
					char ****commands, char **env);
void			init_tokens(t_struct_token *token_list);
/////////////excute.c//////////////////
int				find_fully_num_del(t_struct_token *token_list);
int				search_index_of_pipex(t_struct_token *token_list,
					int n_pip);
void			cut_to_the_first_pip(t_struct_token **token_list,
					int prev, int p_i, int p_n_pipe);
int				set_len_for_all(t_struct_token *token_list);
int				find_target_in_heredoc(t_struct_token *token_list);
//////excuttttttttttttttttttt.c////
void			select_fd_read_and_write(t_struct_token *token_list,
					t_fd *fd, char **env);
void			the_last_command(t_struct_token *token_list,
					t_fd *fd);
void			read_from_heredo_and_write_in_pip(t_struct_token *token_list,
					t_fd *fd);
void			read_from_pip(t_struct_token *token_list, t_fd *fd);
void			the_first_commands(t_struct_token *token_list,
					t_fd *fd);
/////////////////////////////fd_read__write///////////////
char			**excute_1_command(t_struct_token *token_list,
					t_handle_heredoc_leak *heredoc_tmep);
void			the_finalll_function_for_1_command(t_struct_token *token_list,
					t_handle_heredoc_leak *heredoc_tmep);
void			runs_one_command(t_struct_token *token_list,
					char ****commands, char **env, t_fd *fd);
void			ft_excute_1_command(t_struct_token *token_list,
					char ****commands, char **env, t_fd *fd);
int				search_for_h(t_struct_token *token_list);
/////////////////////runs_1_//////
int				is_buildin(t_struct_token *token_list);
char			**build_in_fun(t_struct_token *tmp,
					t_struct_token *token_list,
					char ****whole_command, char **env);
char			**unset_fun(t_struct_token *token_list, char **env);
char			**export_fun(char ****commands,
					t_struct_token *token_list, char **env);
void			check_the_priority(t_struct_token *token_list,
					int *fd, int *h);
////////runs_builtin_commands.c/////////////////
char			**ft_split(char const *s, char c);
/////////ft_spilt.c//////////////
int				init_tokens_2(t_struct_token *token, char *s);
char			*identify_value_type(char *s, char *next,
					int need_input, int *num_of_pipe);
int				find_closing_quote(char *s, int start,
					char quote_char);
int				split_quote(char *input, int i, char *temp_token,
					int *token_len);
int				isappende_heredoc(char *input);
int				split_operators(char *input, int i,
					char *temp_token, int *token_len);
int				handle_operators(char *input, int *i,
					char *temp_token, int *token_len);
int				is_after_export(char **tokens, int current_index);
int				split_export_argument(char *input, int i,
					char *temp_token, int *token_len);
int				split_commands(char *input, int i, char *temp_token,
					int *token_len);
int				handle_regular_chars(char *input, int *i,
					char *temp_token, int *token_len);
int				store_token(char *temp_token, int token_len,
					char **tokens, int t);
int				split_shell_helper(char *input, char **tokens);
char			**ft_split_shell(char *input);
/////////ft_spilt_shell.c//////////////
int				ft_strcmp(char *s1, char *s2);
char			*ft_itoa(int n);
int				ft_strlen(const char *s);
char			*ft_strdup(char *s);
size_t			ft_strlcpy(char *dst, char *src, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strchr(char *s, char c);
char			*ft_substr(char const *s, unsigned int start,
					size_t len);
int				ft_isalnum(char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*ft_strcat(char *dest, char *src);
int				ft_isspace(int c);
int				ft_isdigit(int digit);
char			*ft_strcpy(char *dest, char *src);
int				ft_strncmp(const char *s1, const char *s2,
					size_t n);
int				ft_strnstr(const char *big, const char *little,
					size_t len);
////////////////////libft.c/////////////////
void			skip_special_command_tokens(t_struct_token **token_list);
void			process_without_quotes(t_struct_token **token_list,
					int i, char *copy);
void			process_without_single_quotes(t_struct_token **token_list,
					int i, char *copy);
int				handle_dollar_sign(t_struct_token **token_list,
					char **envp, int j);
int				check_command(t_struct_token **token_list,
					char **envp);
char			****init_execute_commands(t_struct_token *token_list);
char			***init_command_block(int n_column);
int				add_tokens_from_args(t_struct_token **token_list,
					char **arg);
int				is_operates(char *s);
int				count_non_quote_chars(char *value, int i);
void			copy_without_quotes(char *value, char *copy, int *i,
					int *len);
char			*without_q_s(char *value, int i, char *copy);
int				have_quotes(char *s);
void			free_tokens_split2(char **tokens);
void			init_fd(t_fd *fd);
///////////////check_command.c////////////////////
void			is_echo(t_struct_token *token_list);
int				find_number_of_command(t_struct_token *token_list);
void			free_whole_command(char ****commands,
					t_struct_token *token_list);
void			fill_the_3d_array(t_struct_token *token_list,
					char ****commands, int n_pip, int n_column);
int				count_pipe_segments(t_struct_token *token_list);
////////////////////////creat_3d_array.c//////////////
char			*is_pipe(int i, char *s);
char			*is_redirection_lessthan(int i, char *s);
char			*is_single_redirection(int i, char *s);
char			*is_redirection(int i, char *s);
char			*is_double_qoutes(int i, int *q, char *value);
char			*is_single_qoutes(int i, char *s, int *q);
int				search_valid_command(char *s);
//////////Def_of_linked_list_variables.c/////////////////////
char			*call_access(char *path, char *command);
char			*valid_command_path(char *command,
					char **find_path);
char			*find_command_path(char *command, char **envp,
					int f);
//////////////////init_pipex.c////////////////////////
int				search_valid_pipes(t_struct_token *t);
void			free_fd_arg(t_fd *fd, char **arg,
					t_struct_token *tokens, char ****cmd);
char			**start_execution_cmd(t_fd *fd,
					t_struct_token *token_list, char **envp,
					char **arg);
char			**start_processing(char *input, char **envp,
					t_exit_status *exit_status);
///////////////////////init_tokens.c//////////////////////////////
void			safe_free_token_list(t_struct_token **head);
int				is_need_input(char *s, int f, char *next);
int				add_token(t_struct_token **head, char *s,
					char *next, int f);
////////////////////////////linked_list_fun.c/////////////////////////
int				is_command_token(char *type);
int				check_expand_redirection(t_struct_token *token_list,
					t_fd *fd, char *filename);
int				check_out_redirection(t_struct_token *token_list,
					t_fd *fd, char *filename);
int				check_in_redirection_internal(t_struct_token *token_list,
					t_fd *fd, char *filename);
int				check_in_redirection(t_struct_token *token_list,
					t_fd *fd);
/////////////////////readirection.c///////////////////
char			*without_q(char *value, int i, char *copy);
char			*without_bin(char *s, int i);
int				check_dollar(char *s);
char			*replace_doller_2(char *value, int i, int len,
					char **envp);
char			*replace_doller(char *value, char **envp, int i);
////////////////////////////////repalce_cmd.c/////////////////////
void			print_3d_array_fixed(t_struct_token *token_list,
					char ****whole_command);
void			print_list(t_struct_token *head);
void			print_tokens(char **tokens);
void			print_env(char **env, int fd);
/////////////////// delete before evalllllll///////////////////////////////
void			init(t_struct_token *t, char **delimeter,
					char **input_afterhere,
					t_struct_token **token_list);
void			her2(t_struct_token *token_list, int num_of_del,
					t_fd *fd_h, char **envp);
void			heredocc_fun(t_struct_token *t, t_fd *fd_h,
					char **envp, int num_of_del);
int				starting_2(t_struct_token *token_list,
					char **delimeter, char **input_afterhere);
void			st3(t_struct_token *token_list);
void			here(t_struct_token **token_list, int fd,
					int *num_of_del,
					t_handle_heredoc_leak *heredoc_temp);
void			starting_child(t_handle_heredoc_leak *heredoc_temp,
					t_struct_token *token_list, int fd);
void			here2(t_handle_heredoc_leak *heredoc_temp,
					t_struct_token *token_list, int fd);
int				lastheredoc_and_input_isnt_the_del22(
					t_struct_token **token_list,
					int fd);
void			lasther_in_isnt_d(t_struct_token **token_list,
					int *num_of_del, int fd,
					t_handle_heredoc_leak *herdoc_temp);
void			ex_3(t_struct_token **token_list, int *num_of_del,
					int fd, t_handle_heredoc_leak *herdoc_temp);
void			ex_4(t_struct_token **token_list, int *num_of_del,
					int fd, t_handle_heredoc_leak *herdoc_temp);
void			ex_5checking(pid_t child, t_fd *fd_h, int fd[2]);
int				find_num_del(t_struct_token *token_list);
int				check_here_expand(t_struct_token *token,
					char *input, char **envp, int fd);
void			check_num_of_del(t_struct_token *token_list);
char			*finding_del(t_struct_token *token_list);
void			freeee(char **input_afterhere);
void			init_heredoc_token(t_struct_token *t,
					char **delimiter, char **input_afterhere,
					t_struct_token **token_list);
void			handle_heredoc_sigint(int sig);
void			process_heredocs(t_handle_heredoc_leak *heredoc_temp,
					int num_of_del);
void			start_heredoc_processing(t_handle_heredoc_leak *heredoc_temp,
					int num_of_del);
int				is_delimiter_or_eof(char *line, char *delimiter);
char			*expand_heredoc_line(char *line, int expand,
					char **envp, int write_fd);
void			write_line_to_pipe(char *line, int fd);
void			read_heredoc_input(char *delimiter, int write_fd,
					int expand, char **envp);
void			heredoc_child_process(t_struct_token *token_node,
					char **envp);
int				create_heredoc_pipe(t_struct_token *token_node);
int				fork_heredoc_process(pid_t *pid,
					t_struct_token *token_node);
void			wait_for_heredoc(t_struct_token *token_node,
					t_exit_status *exit_status);
void			handle_heredoc_token(t_struct_token *token_node,
					char **envp, t_exit_status *exit_status);
int				collect_all_heredocs(t_struct_token *token_list,
					char **envp, t_exit_status *exit_status);
void			run_heredoc_collection(t_struct_token *t,
					char **envp);
void			close_all_heredoc_pipes(t_struct_token *token_list);
//////////////////heredoc.c////////////////////////
char			*expand_variables_in_string(char *str, char **envp,
					t_exit_status *exit_status);
void			expand_token_variables(t_struct_token *token_list,
					char **envp);
//////////////////expand_variables.c////////////////////////
void			shell_loop(char *input, char ***env, char **test,
					t_exit_status *exit_status);
//////////////////// main.c///////////////////////////
void			define_fun(int num);
void			signal_function(struct sigaction *s_ctrl_back_slash,
					struct sigaction *s_ctrl_c,
					struct sigaction *s_ctrl_d);
void			signals(void);
char			*expand_single_variable(char *str, int *pos, char **envp,
					t_exit_status *exit_status);
int				find_dollar(char *value);
int				if_char_num(int c);
//////////////////////////////////////////////////////
#endif