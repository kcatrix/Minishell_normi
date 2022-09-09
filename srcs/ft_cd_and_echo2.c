/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_and_echo2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:57:58 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/09 13:03:34 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_cd_absolute_pwd(char *spli)
{
	int	i;

	i = 0;
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
			g_stock.cpenv[i] = ft_strjoin("PWD=", spli);
		i++;
	}
}

void	cmd_cd_relative_pwd(char *spli)
{
	int	i;

	i = 0;
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
		{
			g_stock.cpenv[i] = ft_strjoin(g_stock.cpenv[i], "/");
			if (verifpwd(spli) == 0)
				spli[ft_strlen(spli) - 1] = '\0';
			g_stock.cpenv[i] = ft_strjoin(g_stock.cpenv[i], spli);
		}
		i++;
	}
}

int	verifpwd(char *spli)
{
	int	i;

	i = 0;
	while (spli[i])
		i++;
	i--;
	if (spli[i] == '/')
		return (0);
	else
		return (1);
}

void	cmd_cd_noarg(void)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "HOME=", 5) == 0)
		{
			chdir(g_stock.cpenv[i] + 5);
			cmd_cd_pwd(g_stock.cpenv[i] + 5);
		}
		i++;
	}
}

void	cmd_cd_pwd(char *home)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "OLDPWD=", 7) == 0)
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
		{
			free(g_stock.cpenv[i]);
			g_stock.cpenv[i] = "PWD=";
			g_stock.cpenv[i] = ft_strjoin(g_stock.cpenv[i], home);
		}
		i++;
	}
}
