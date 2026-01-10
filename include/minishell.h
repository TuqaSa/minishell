/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealshari <ealshari@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:51:04 by ealshari          #+#    #+#             */
/*   Updated: 2025/08/23 20:23:51 by ealshari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

extern volatile sig_atomic_t	g_sig;

typedef struct s_ms
{
	int							last_status;
	char						**envp;
	int							argc;
	char						**argv;
	int							(*pipe_fds)[2];
	pid_t						*child_pids;
}								t_ms;

typedef struct s_wait_ctx
{
	size_t						cmd_count;
	pid_t						*child_pids;
	int							wait_status;
	int							current_pid;
}								t_wait_ctx;

typedef struct s_word_buf
{
	char						**buf;
	size_t						*len;
	size_t						*cap;
}								t_word_buf;

typedef enum e_redirtype
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}								t_redirtype;

typedef struct s_redir
{
	t_redirtype					type;
	char						*arg;
	int							hdoc_fd;
}								t_redir;

typedef struct s_cmd
{
	char						**argv;
	t_redir						*reds;
	size_t						nreds;
}								t_cmd;

typedef struct s_pipeline
{
	t_cmd						*cmds;
	size_t						n;
}								t_pipeline;

typedef enum e_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_DLESS,
	TOK_DGREAT
}								t_toktype;

typedef struct s_token
{
	t_toktype					type;
	char						*raw;
}								t_token;

typedef struct s_tokvec
{
	t_token						*v;
	size_t						n;
	size_t						cap;
}								t_tokvec;

typedef struct s_word_expand_ctx
{
	t_ms						*ms;
	const char					*raw;
	char						**output;
	size_t						*char_index;
	int							*in_single;
	int							*in_double;
}								t_word_expand_ctx;

typedef struct s_parse_ctx
{
	t_ms						*ms;
	const t_tokvec				*tv;
	char						***argv;
	size_t						*argc;
	t_cmd						*out;
}								t_parse_ctx;

typedef struct s_seg_ctx
{
	t_ms						*ms;
	const t_tokvec				*tv;
	t_pipeline					*out;
}								t_seg_ctx;

/* ========== BUILTINS MODULE ========== */
int								is_builtin(const char *cmd);
int								run_builtin(int argc, char **argv, t_ms *ms);
int								builtin_echo(char **argv, t_ms *ms);
int								builtin_pwd(t_ms *ms);
int								builtin_cd(int argc, char **argv, t_ms *ms);
char							*cd_expand_tilde(const char *target, t_ms *ms);
void							cd_update_env(t_ms *ms, char *oldpwd);
int								cd_handle_error(const char *target,
									char *oldpwd, char *expanded);
int								builtin_env(int argc, char **argv, t_ms *ms);
int								builtin_export(int argc, char **argv, t_ms *ms);
int								builtin_unset(int argc, char **argv, t_ms *ms);
int								builtin_exit(int argc, char **argv, t_ms *ms);
void							builtin_putstr(const char *s);
void							builtin_puterr3(const char *a, const char *b,
									const char *c);
int								builtin_count_args(char **argv);

/* ========== ENV MODULE ========== */
const char						*env_value_get(t_ms *ms, const char *name);
char							**env_context_init(char **envp_src);
void							env_context_free(char **envp);
int								env_variable_set(t_ms *ms, const char *name,
									const char *value);
int								env_variable_unset(t_ms *ms, const char *name);
char							*env_pair_create(const char *key,
									const char *value);
int								env_key_find_index(char **envp,
									const char *name);
int								env_name_validate(const char *s);

/* ========== EXEC MODULE ========== */
int								pipe_array_create(size_t cmd_count,
									int (**out_pipe_fds)[2]);
void							pipe_array_close_all(size_t cmd_count,
									int (*pipe_fds)[2]);
int								pid_array_allocate(size_t cmd_count,
									pid_t **out_pids);
int								ms_exec_builtin_check(t_ms *ms, t_cmd *command);
int								ms_exec_external_cmd(t_ms *ms, t_cmd *command,
									t_pipeline *pl);
int								ms_exec_cmd_with_pipeline(t_ms *ms, t_cmd *cmd,
									t_pipeline *pl);
void							ms_exec_pipeline_child(t_ms *ms, t_pipeline *pl,
									size_t cmd_index, int (*pipe_fds)[2]);
int								ms_heredoc_collect(t_ms *ms,
									const char *delimiter, int *output_fd);
int								ms_exec_pipeline(t_ms *ms, t_pipeline *pl);
int								ms_apply_redirs(const t_cmd *command);
int								exec_empty_cmd_redirs(t_cmd *cmd);
void							ms_exec_handle_signals(int process_status,
									t_ms *ms);
void							exec_external_command(t_ms *ms, t_cmd *cmd,
									t_pipeline *pl);
void							exec_wait_all_children(t_ms *ms,
									size_t cmd_count, pid_t *child_pids);

/* ========== EXPAND MODULE ========== */
int								char_append_to_output(const char *raw_input,
									size_t *pos, char **output);
int								quote_toggle_check(const char *raw_input,
									size_t *pos, int *in_single,
									int *in_double);
int								literal_dollar_append(char **output);
int								status_expansion_handle(t_ms *ms, size_t *pos,
									char **output);
void							expand_status_to_string(int status_value,
									char output_buffer[12]);
int								expand_variable_substitute(t_ms *ms,
									const char *raw_input, size_t *index,
									char **output);
char							*expand_word(t_ms *ms, const char *raw);

/* ========== LEXER MODULE ========== */
int								lexer_tokenize(const char *input_line,
									t_tokvec *output_tokens);
int								lexer_handle_operator(const char *input_line,
									size_t *char_index,
									t_tokvec *output_tokens);
int								lexer_sb_add(char **buffer_ptr,
									size_t *buffer_length,
									size_t *buffer_capacity, char character);
int								lexer_tokvec_push(t_tokvec *token_vector,
									t_toktype token_type, char *raw_string);
void							lexer_tokvec_free(t_tokvec *token_vector);
int								lexer_handle_word(const char *input_line,
									size_t *char_index,
									t_tokvec *output_tokens);
int								lexer_is_operator_char(int character);
int								lexer_handle_quotes(const char *input_line,
									size_t *char_index, int *in_single_quotes,
									int *in_double_quotes);
int								lexer_should_break_word(const char *input_line,
									size_t char_index, int in_single_quotes,
									int in_double_quotes);
int								lexer_add_char_to_word(t_word_buf *word_buffer,
									char character);
char							*lexer_sb_new(size_t initial_capacity);

/* ========== PARSER MODULE ========== */
int								push_word(char ***argv_ptr, size_t *argc_ptr,
									const char *word_string);
int								push_red(t_redir **redirections_ptr,
									size_t *redirection_count,
									t_redir new_redir);
int								push_cmd(t_pipeline *pipeline, t_cmd *command);
int								parser_cleanup_parse_error(char **argv_array,
									size_t argc_count, t_cmd *cmd_output);
void							ms_cmd_free(t_cmd *command);
int								parse_cmd(t_ms *ms,
									const t_tokvec *token_vector,
									t_cmd *output_cmd);
int								ms_run_line_simple(t_ms *ms,
									const char *input_line);
int								ms_parse_pipeline(t_ms *ms,
									const t_tokvec *token_vector,
									t_pipeline *output_pipeline);
int								parser_parse_segments(t_ms *ms,
									const t_tokvec *token_vector,
									t_pipeline *output_pipeline);
int								parser_set_redir_type(t_redir *redirect_info,
									int token_type);
int								parser_process_redir_arg(t_ms *ms,
									t_redir *redirect_info, char *arg_raw);
void							parser_cleanup_redir(t_redir *redirect_info);
int								parser_valid_r_s(const t_tokvec *token_vector,
									size_t token_index);
int								parser_setup_redir(t_ms *ms,
									t_redir *redirect_info,
									t_toktype redir_type, char *arg_raw);
int								check_pipe_syntax(const t_tokvec *token_vector);
void							ms_pipeline_free(t_pipeline *pipeline);
int								process_quotes(const char *raw_input,
									char **o_buffer, size_t *b_length,
									size_t *b_capacity);
int								parser_is_quoted_token(const char *raw_input);
int								parser_add_split_words(char ***argv_ptr,
									size_t *argc_ptr, char **split_words);
void							parser_free_split(char **split_words);
int								parser_handle_split_word(char *expanded_word,
									char ***argv_ptr, size_t *argc_ptr);
int								parser_handle_single_word(char *expanded_word,
									const char *raw_token, char ***argv_ptr,
									size_t *argc_ptr);
char							*unquote_literal(const char *raw_input);

/* ========== UTILS MODULE ========== */
char							*ms_path_build_candidate(const char *dir,
									const char *cmd);
int								ms_path_test_candidate(const char *candidate);
char							*ms_resolve_path(t_ms *ms, const char *cmd);
char							*ms_path_join3(const char *a, const char *b,
									const char *c);

void							ms_signals_ignore(void);
void							signals_sigint_handler(int signo);
void							signals_heredoc_sigint_handler(int signo);
void							ms_signals_interactive(void);
void							ms_signals_heredoc(void);
void							ms_signals_child(void);
void							ms_set_echoctl(bool enable);

#endif
