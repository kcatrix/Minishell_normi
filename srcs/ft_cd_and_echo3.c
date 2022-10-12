/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_and_echo3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcatrix <kcatrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:03:28 by kcatrix           #+#    #+#             */
/*   Updated: 2022/10/12 14:54:06 by kcatrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cd_dot_dot(void)
{
	if (ft_verifdirexist() == 1)
	{
		ft_modifdirdotdot();
		return ;
	}
	cmd_cd_dot_dot_fct();
}

char	*ft_chk_last_path(char *pwd)
{
	char	*newpwd;
	int		i;

	i = 0;
	while (pwd[i])
		i++;
	i--;
	while (pwd[i])
	{
		if (pwd[i] == '/')
		{
			pwd[i] = '\0';
			newpwd = pwd;
			return (newpwd);
		}
		i--;
	}
	return (pwd);
}

void	cmd_cd_absolute_redirect(char *spli)
{
	if (spli[0] == '/')
		cmd_cd_absolute(spli);
	else
		cmd_cd_relative(spli);
}

void	cmd_cd_absolute(char *spli)
{
	if (chdir(spli) == -1)
	{
		printf("cd: %s: No such file or directory\n", spli);
		return ;
	}
	cmd_cd_absolute_pwd(spli);
}

void	cmd_cd_relative(char *spli)
{
	if (chdir(spli) == -1)
	{
		printf("cd: %s: No such file or directory\n", spli);
		return ;
	}
	cmd_cd_relative_pwd (spli);
}
