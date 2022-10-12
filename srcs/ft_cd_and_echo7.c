/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_and_echo7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcatrix <kcatrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:22:39 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/12 14:54:48 by kcatrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>
#include <errno.h>

char	*getpwd2(void)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PWD=", 4) == 0)
		{
			tmp = ft_mallocex((g_stock.cpenv[i] + 4), tmp);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

int	ft_verifdirexist(void)
{
	char	*testdir;
	char	*testdir2;
	DIR		*dir;

	testdir2 = getpwd2();
	testdir = ft_chk_last_path(testdir2);
	dir = opendir(testdir);
	free(testdir2);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	else
		return (1);
}

int	ft_modifdirdotdot(void)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PWD=", 4) == 0)
		{
			if (strcmp(g_stock.cpenv[i], "PWD=/Users") == 0)
				return (0);
		}
		i++;
	}
	printf("cd: error retrieving directory:cannot access parent directories\n");
	return (0);
}

void	cmd_cd_dot_dot_fct(void)
{
	int	i;

	i = 0;
	if (chdir("..") == -1)
		return ;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "OLDPWD=", 7) == 0 && g_stock.old == 0)
		{
			free(g_stock.cpenv[i]);
			g_stock.cpenv[i] = "OLDPWD=";
			g_stock.cpenv[i] = ft_strjoin(g_stock.cpenv[i], getpwd());
		}
		i++;
	}
	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PWD=", 4) == 0)
			g_stock.cpenv[i] = ft_chk_last_path(g_stock.cpenv[i]);
		i++;
	}
}
