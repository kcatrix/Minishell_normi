/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:56:15 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/05 11:02:10 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**path_fct(char **env)
{
	int		i;
	int		y;
	char	*str;
	char	**spli;

	i = 0;
	y = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	while (env[i][y] != '=')
		y++;
	str = env[i] + y + 1;
	spli = ft_split(str, ':');
	return (path_finish(spli));
}

char	**path_finish(char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(env[i], "/");
		free(env[i]);
		env[i] = tmp;
	}
	return (env);
}

int	verif_exist(char **path, char *argv)
{
	int		i;
	int		x;

	i = -1;
	x = 1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], argv);
		x = access(path[i], R_OK);
		if (x == 0)
			return (i);
	}
	return (-1);
}

int	ft_strlendouble(char **strdouble)
{
	int	i;

	i = 0;
	while (strdouble[i])
		i++;
	return (i);
}

int	ft_verifexistunset(char **env, char **spli)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_preline(env[i]), ft_preline(spli[1])) == 0)
			return (0);
		i++;
	}
	return (1);
}
