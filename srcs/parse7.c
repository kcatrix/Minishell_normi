/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:36:31 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/12 10:38:42 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_backslash(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			skip(str, &i);
		if (str[i] == '\'')
			skip(str, &i);
		if (str[i] == '\\')
			rm_char(str, i--);
		i++;
	}
}

int	pos_dollard(char **spli)
{
	int	i;

	i = 0;
	while (spli[i])
	{
		if (spli[i][0] == '$')
			return (i);
		i++;
	}
	return (i);
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

char	**cmd_cd_dot(void)
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
	return (NULL);
}

void	cmd_cd(char **spli)
{
	char	**unparun;

	if (g_stock.nbpip > 0)
	{
		fixcd();
		return ;
	}
	if (spli[1])
		unparun = ft_split(spli[1], '/');
	if (!spli[1])
	{
		cmd_cd_noarg();
		return ;
	}
	if (spli[1][0] == '/')
		cmd_cd_absolute(spli[1]);
	else
	{
		cmd_cd_boucle(unparun);
	}
	if (spli[1])
		free_spli(unparun);
}
