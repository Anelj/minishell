/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:31:14 by                   #+#    #+#             */
/*   Updated: 2022/03/03 17:17:16 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include "./libft/libft.h"
# include <string.h>

# define BUFFER_SIZE 8000

extern int	g_exit_code;

typedef struct s_env_list
{
	char				*key;
	char				*val;
	size_t				key_len;
	size_t				val_len;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_env
{
	struct s_env_list	*env_lst;
	char				**env_ar;
	int					avail_nb_env_ar;
	int					nb_keys;
}	t_env;

typedef struct s_redir
{
	char	*redir;
	int		isin;
	int		isdouble;
}	t_redir;
// Command Data Structure
// Describes a simple command and arguments
typedef struct s_simple_command
{
	int		nb_ofavail_args;
	int		nb_ofargs;
	char	**args;
	t_redir	*redir;
	t_redir	*out;
	t_redir	*in;
}	t_simple_command;
// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
typedef struct s_command
{
	int						nb_ofavail_scmds;
	int						nb_ofscmds;
	struct s_simple_command	**scmds;
	struct s_simple_command	**cur_scmds;
	t_env					*env_s;
	char					*out;
	char					*in;
	char					*er;
}	t_command;

//   --- ft_split_helper_bonus  ---   //
char				**ft_split_freestrs(char **strs, char **ss);
int					ft_quotes(const char **str, int *lw);

//   --- ft_splitpath_bonus  ---   //
char				**ft_splitpath(char const *s, char c);

//   --- ft_heredoc ---   //
int					ft_getbuffer(int out, char **buffer);

int					ft_fullbuffer(size_t nbytes, int out, char *buffer, \
					char *limiter);
//   --- ft_heredoc ---   //
int					ft_return_after_processing_heredoc(int flag, char *buffer, \
					int out);
int					ft_getcbytes(char *buf, size_t nbytes, \
					char *buffer, int out);
int					ft_proccess_heredoc(int out, char *limiter);

//   --- ft_is_sep_or_spec_sign ---   //
int					ft_is_specn(char *s);
int					ft_is_spec(char *s);
int					ft_issep_cmdn(char *s);
int					ft_issep_cmd(char *s);

//   --- ft_pipe_helper ---   //
int					ft_getexitcode(int stat, int exit);
int					ft_pipe1(int *fds, int in, int out);
pid_t				ft_fork1(int in, int out);
int					ft_open(char *file, int toread, int toappend, int toclose);

//   --- ft_insert_var1 ---   //
int					ft_emptyvar_insert(char **string, char **s, char **ret);
int					ft_join_with_remain_str(char *tmp, char **s, \
					char **string);
int					ft_insert_var_witin_quotes(char **s, char **string, \
					t_env *env_s);
int					ft_var_within_quotes(char **str, char **string, \
					t_env *env_s);

//   --- ft_insert_var ---   //
int					ft_freestr_reter(char *string);
int					ft_insert_var(char **string, t_env *env_s);
int					ft_process_found_var_char(char **s, char **string, \
					t_env *env_s);
int					ft_insert_splitedvar_withquotes(char **spl_var, \
					size_t *l, char **tmp);

//   --- ft_free ---   //
char				**ft_freescmd_exit_code_ret_null(t_simple_command *scmd);
void				ft_freescmd(t_simple_command *scmd);
void				ft_freecmd(t_command **cmd);
void				ft_execve_exit(t_command *cmd, int ex_code);
int					ft_check_and_exit(int fd, t_command *cmd, \
					int is_from_child);

//   --- ft_env_utils ---   //
void				int_handler1(void);
void				int_handler(void);
void				ft_initial_sig_override(t_env *env_s);
void				ft_sigint_for_parent_process(char *s, t_env *env_s);
void				ft_sig_return_def_behavior(t_command *cmd);
//   --- ft_env_utils ---   //
int					ft_is_val_present(char *env, size_t l);
int					ft_validate_key(char *env, char *cmdname);
size_t				ft_get_key_len(char *env);
int					ft_find_el_or_place_toinsert(t_env *env_s, char *env, \
					t_env_list **env_lst, t_env_list **env_lst_prev);
//  --- ft_free_del_env ---   //
void				ft_del_env_lst_el(t_env_list *env_lst, \
					t_env_list *env_lst_prev);
void				ft_free_env(t_env *env);
void				ft_free_lst(t_env_list **lst);
void				ft_free_ar(char ***ar);
void				ft_del_env_ar_el(char **env_ar, char *env, size_t key_len);

//   --- ft_insert_var_helper ---   //
int					ft_split_var(char ***spl_var, char *var, char *string);
int					ft_get_len_and_strdup_str_before_var_char( \
					size_t *l, char **string, char **tmp, char **spl_var);
int					ft_env_is_digit_or_exit_code(char **s, char **var);
int					ft_env_value(t_env_list *env_lst, char **var);
int					ft_find_envvar(char **s, t_env *env_s, char **var);
//   --- ft_utils ---   //
void				ft_exit_program(t_env *env_s);
void				ft_dup2_close(int fd1, int fd2);
int					ft_strjoin_inserting_var(char **s, char *s1, \
					char **spl_var, int i);
int					ft_strdup_helper(char **string, char **tmp);
int					ft_set_exit_code_and_display_er(int code);

//   --- ft_pipex2 ---   //
void				ft_proccess_child(int tmpin, int tmpout, int fdin, \
					t_command *cmd);
void				ft_exit_ers(int ret, t_command *cmd);

//   --- ft_pipex ---   //
int					ft_parent_wait_exec(int tmpin, int tmpout, pid_t child, \
					t_command *cmd);
int					ft_execute_buildin(int (*f)(t_command *), t_command *cmd, \
					int is_from_child);
int					ft_execute_inseparate_process(t_command *cmd, \
					int is_from_child);
int					ft_create_child_and_execute(t_command *cmd);

//   --- parser_utils ---   //
int					ft_args_count(char **s);
int					ft_in_count(char **s);
int					ft_out_count(char **s);
int					ft_scmd_count(char **s);
t_simple_command	*ft_get_scmd(char ***s1);

//   --- parser ---   //
t_simple_command	*ft_create_scmd(char **s);
t_simple_command	*ft_set_redir_heredoc(\
					t_simple_command *scmd, int *j, char **s);
t_simple_command	*ft_set_redir(t_simple_command *scmd, int *j, char **s);
char				**ft_fill_scmd(char **s, t_simple_command *scmd);
t_command			*ft_parse(char **s1);
//   --- ft_cmd_bonus_utils ---   //
int					ft_is_path(char *cmdname);
void				ft_freestrs(char **s);

//   --- ft_cmd_bonus ---   //
char				**ft_get_cmd(char **cmd, t_env *env_s);
char				*ft_path(char *cmdname, t_env *env_s);
int					ft_execute_cmd(t_command *cmd, int is_from_child);
char				*ft_find_cmdpath_inpath(char *envPATH, char *cmdname);
char				*ft_is_cmd_executable(char *cmdname);

//   --- ft_dup ---   //
int					ft_dup_redir_fdout(t_redir *redir);
int					ft_dup_redir(t_redir *redir, t_command *cmd, \
					int is_from_child);
int					ft_dup_pipes(int *fdin, int is_last_scmd, int tmpout, \
					int tmpin);
void				ft_set_tmp_in_and_out(int *tmpin, int *tmpout, int *fdin);
void				ft_set_from_tmp_in_out(int tmpin, int tmpout);

//   --- ft_env ---   //
t_env_list			*ft_create_env_lst_el(char *env, size_t key_len);
t_env				*ft_init_env(char **env);
int					ft_check_env_lst_el(char *env, size_t key_len, \
					t_env_list	*env_el);
int					ft_insert_env_lst_el(t_env *env_s, \
					t_env_list *env_lst, char *env, size_t key_len);
int					ft_replace_env_ar_el(char **env_ar, char *env, \
					size_t key_len);

//   --- ft_env2 ---   //
int					ft_replace_env_lst_el_val(t_env_list *env_lst, \
					char *env, size_t key_len);
void				ft_fill_env_ar_el(t_env *env_s, char *env_cpy, char	**tmp);
int					ft_insert_env_ar_el(t_env *env_s, char *env);
int					ft_insert_env_helper(t_env *env_s, char *env, \
					t_env_list *env_lst, size_t key_len);
int					ft_insert_env(t_env *env_s, char *env);

//   --- ft_split_bonus_utils ---   //
void				ft_fill_str_with_char_and_move_to_nextch(char **strs, \
					char **s);
void				ft_quotesfill(char *s, char **strs1, int len);
int					ft_token_qoutes_fill(char **strs, \
					char const **s_tosplit, char const	*s, int l);
int					ft_tokenfill(char *s, char **strs);
void				ft_count_chars_within_qoutes(int *lw, \
					char const **s, int *lwq);
//   --- ft_split_bonus_strs ---   //
int					ft_str_len_after_spec_met( \
					int lw, int lwq, char const **s_tosplit, char const *s);
int					ft_str_len_after_ws_met( \
					char const **s_tosplit, char const *s, int lw);
int					ft_str_len_in_s_tosplit( \
					char const **s_tosplit, char c);
void				ft_countstrs_after_spec_met( \
					int *lw, int *lwq, int *l, char const **str);

//   --- ft_split_bonus ---   //
char				**ft_advance_split(char const *s, char c);

//   --- ft_buildin ---   //
int					ft_set_env_vals(t_env *env_s, int ret);
int					ft_setter(t_command *cmd, char *prev, \
					char cwd[1024], char *pwd);
int					ft_set_pwd_oldpwd(t_command *cmd, char *prev);
int					ft_isdigits(char *s);

//   --- ft_buildin2 ---   //
int					ft_pwd(t_command *cmd);
int					ft_exit(t_command *cmd);
int					ft_unset(t_command *cmd);
int					ft_echo(t_command *cmd);
int					ft_env(t_command *cmd);

//   --- ft_buildin3 ---   //
void				ft_export_print(t_env_list	*env);
int					ft_export(t_command *cmd);
void				ft_write_cd(char **args);
int					ft_cd(t_command *cmd);

//   --- ft_validate_spec_funcs ---   //
int					ft_check_newline_token(char *spliteds, char *spliteds2);
int					ft_check_bracket1_token(char *spliteds, char *spliteds2);
int					ft_check_bracket2_token(char *spliteds, char *spliteds2);
int					ft_check_bracket3_token(char *spliteds, char *spliteds2);
int					ft_check_bracket4_token(char *spliteds, char *spliteds2);

//   --- ft_validate_spec_orders ---   //
int					ft_validate_spec_order(char **spliteds);
int					ft_check_pipe_token(char *spliteds, char *spliteds2, int i);
#endif
