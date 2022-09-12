/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_and_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:13:17 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/12 05:58:42 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(char **spli)
{
	int	i;

	i = 1;
	if(g_stock.out != 0)
		dup2(g_stock.out, STDOUT_FILENO);
	if(g_stock.in != 1)
		dup2(g_stock.in, STDIN_FILENO);
	if (!spli[1])
	{
		printf("\n");
		fix_out_inr_redir();
		free_spli(spli);
		return ;
	}
	if (echo_option(spli[1]) == 0)
		i++;
	while (spli[i])
	{
		printf("%s", spli[i++]);
		if (spli[i] != NULL)
			printf(" ");
	}
	if (echo_option(spli[1]) == 1)
		printf("\n");
	fix_out_inr_redir();
	free_spli(spli);
}

int	echo_option(char *spli)
{
	int	i;

	i = 1;
	if (spli[0] == '-')
	{
		while (spli[i])
		{
			if (spli[i] == 'n')
			{
				i++;
			}
			else
				return (1);
		}
		if (i == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

void	cmd_cd(char **spli)
{
	char **unparun;
	int i;

	i = 0;
	if (spli[1])
		unparun = ft_split(spli[1], '/');
	if (!spli[1])
	{
		cmd_cd_noarg();		
		return;
	}
	while(unparun[i])
	{
		g_stock.old = i;
		if (strcmp(unparun[i], ".") == 0)
			cmd_cd_dot();
		else if (strcmp(unparun[i], "..") == 0)
			cmd_cd_dot_dot();
		else
			cmd_cd_absolute_redirect(unparun[i]);
		i++;
	}
	if (spli[1])
		free_spli(unparun);
	free_spli(spli);
}

char	**cmd_cd_dot(void)
{
	int	i;

	i = 0;
	printf("ici\n");
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "OLDPWD=", 7) == 0 && g_stock.old == 0)
		{
			g_stock.cpenv[i] = "OLDPWD=";
			g_stock.cpenv[i] = ft_strjoin(g_stock.cpenv[i], getpwd());
		}
		i++;
	}
	return (NULL);
}

char	*getpwd(void)
{
	int	i;
	int	j;

	i = 0;
	j = 4;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PWD=", 4) == 0)
			return (g_stock.cpenv[i] + 4);
		i++;
	}
	return (NULL);
}
