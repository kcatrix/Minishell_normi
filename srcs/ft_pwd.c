/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcatrix <kcatrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:41:24 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/07 15:09:16 by kcatrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PWD=", 4) == 0)
		{
			printf("%s\n", g_stock.cpenv[i] + 4);
		}
		i++;
	}
}

int	ft_path_exist(void)
{
	int		i;
	int		x;
	char	**path;

	x = -1;
	i = 0;
	path = NULL;
	if (ft_path_exist_boucle(path, i, x) == 0)
		return (0);
	if (path)
		free_spli(path);
	return (1);
}

int	ft_path_exist_boucle(char **path, int i, int x)
{
	while (g_stock.cpenv[i])
	{
		if (ft_memcmp(g_stock.cpenv[i], "PATH=", 5) == 0)
		{
			path = ft_split(g_stock.cpenv[i] + 5, ':');
			i = 0;
			while (path[i])
			{
				path[i] = ft_strjoin(path[i], "/env");
				x = access(path[i], R_OK);
				if (x == 0)
				{
					free_spli(path);
					return (0);
				}
				i++;
			}
			free_spli(path);
			return (1);
		}
		i++;
	}
	return (1);
}

int	last_check(int i, char **path, char *line)
{
	if (i == -1 || !path)
	{
		printf("%s: Command not found\n", line);
		if (path)
			free_spli(path);
		g_stock.end = 127;
		return (-1);
	}
	return (0);
}
