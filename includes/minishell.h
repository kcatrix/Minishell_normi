/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:57:59 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/09 04:56:55 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <termios.h>

int		ft_cmd(char *line, char **env);
char	**path_fct(char **env);
void	interrupt_signal(int signal);
char	**path_finish(char **env);
void	quit_signal(int signum);
int		verif_exist(char **path, char *argv);
char	**verif_option(char **spli);
void	ft_exit(int x);
void	cmd_echo(char **spli);
char	*getpwd(void);
void	cmd_cd(char **spli);
int		echo_option(char *spli);
char	**ft_cp_env(char **env);
char	**cmd_cd_dot(void);
int		ft_chevron_redirect(char **spli, int i);
int		ft_chevron_droite(char **spli, int i);
char	*ft_chk_last_path(char *pwd);
void	cmd_cd_dot_dot(void);
void	cmd_cd_relative_pwd(char *spli);
int		verifpwd(char *spli);
void	cmd_cd_absolute_pwd(char *spli);
void	cmd_cd_relative(char *spli);
void	cmd_cd_absolute(char *spli);
void	cmd_cd_absolute_redirect(char *spli);
void	cmd_cd_pwd(char *home);
void	cmd_cd_noarg(void);
char	**parse(char **spli);
char	**cmd_dollar(char **spli, int i);
void	ft_export(char **spli);
void	ft_pwd(void);
char	**ft_sup_dollar(char **spli, int y);
void	ft_env(void);
void	free_spli(char **spli);
void	f_exit(char **spli);
int		ft_verif_chevron(char **spli);
int		ft_redirect(char **spli);
char	*ft_preline(char *line);
int		ft_chevron_redirect(char **spli, int i);
char	*ft_mallocex(char *str, char *str2);
char	**ft_mallocunset(char **stockset);
int		verif_space(char *line);
int		ft_strlendouble(char **strdouble);
int		ft_checkdollar(char **spli);
void	ft_triexport(char *str);
char	**del_i(char **spli, int i);
void	rl_replace_line(const char *text, int clear_undo);
int		ft_path_exist(void);
void	del_quote(char *cmd);
void	rm_char(char *str, size_t index);
void	remove_backslash(char *str);
void	skip(char *str, size_t *i);
int		double_chevron_droite(char **spli, int i);
int		ft_chevron_exist(char **spli);
int		ft_chevron_gauche(char **spli, int i, int y);
int		ft_verif_chevronin(char **spli);
int		heredoc(char **spli, int i);
int		ft_chevron_redirect2(char **spli, int i);
int		ft_prepchevgauche(char **spli, int i);
int		ft_verifexistunset(char **env, char **spli);
int		ft_verifdoublon(char *spli);
void	ft_exptoenv(char *spli);
char	**ft_exptoenv2(void);
void	ft_export_noarg(void);
int		ft_parseexport(char *spli);
void	ft_triexport(char *str);
int		ft_verifenv(char *spli);
void	ft_exportadd(int i, char *spli);
char	**ft_mallocexportadd(void);
int		ft_redirect_2(char **spli);
char	**cmd_unset2(char **spli, char **tmp, char **env, int i);
void	ft_exec(char **spli, char **path, char **env, int i);
void	init_var_cmd(void);
int		ft_parse_cmd(char **spli, char **path);
int		last_check(int i, char **path, char *line);
char	*ft_first_tri(char *str, int i);
int		verif_ex_exist(void);
char	**ft_exptoenv2_boucle(char **cpcpenv, int i, int y);
void	ft_exportadd_boucle(char **cpcpexp, int i, char *spli, int y);
char	**ft_exportadd_boucle_end(char **cpcpexp, int i, char *spli);
int		ft_chevron_redirect2_boucle(char **spli, int i, int y);
char	**ft_mallocunset_boucle(char **cpcpenv, int i, int y, char **stockset);
char	**ft_mallocexportadd_boucle(char **cpcpenv, int i, int y);
int		ft_chevron_redirect_boucle(char **spli, int i, int y);
void	verif_export_exist(int i);
char	**ft_sup_dollar_boucle(char **spli, char **spli2, int y, int i);
int		ft_path_exist_boucle(char **path, int i, int x);
char 	**cmd_dollar_int(char **spli, int i);
void	fix_out_inr_redir(void);
typedef struct s_stock
{
	char	**cpenv;
	char	**cpexp;
	char	**derive;
	char	*save;
	char	*save2;
	int		out;
	int		in;
	int		chkcrash;
	int		old;
	int		end;
}	t_stock;

t_stock	g_stock;

#endif
