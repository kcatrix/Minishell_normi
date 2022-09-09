/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:48:32 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/09 04:36:51 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redirect_2(char **spli)
{
	if (ft_strcmp(spli[0], "PWD") == 0 || ft_strcmp(spli[0], "pwd") == 0)
	{
		ft_pwd();
		free_spli(spli);
		return (0);
	}
	else if ((ft_strcmp(spli[0], "env") == 0
			|| ft_strcmp(spli[0], "ENV") == 0) && ft_path_exist() == 0)
	{
		ft_env();
		free_spli(spli);
		return (0);
	}
	else if (ft_strcmp(spli[0], "export") == 0)
	{
		ft_export(spli);
		free_spli(spli);
		return (0);
	}
	else if (ft_strcmp(spli[0], "exit") == 0)
	{
		f_exit(spli);
		return (0);
	}
	return (1);
}

char	**cmd_unset2(char **spli, char **tmp, char **env, int i)
{
	while (tmp[i])
	{
		if (ft_memcmp(env[i], spli[1], ft_strlen(spli[1])) == 0
			&& ((env[i][ft_strlen(spli[1])] == '=')
			|| (env[i][ft_strlen(spli[1])] == '\0')))
		{
			while (tmp[i + 1])
			{
				free(env[i]);
				env[i] = ft_mallocex(tmp[i + 1], env[i]);
				free(tmp[i + 1]);
				i++;
			}
			env[i] = NULL;
			return (env);
		}
		env[i] = ft_mallocex(tmp[i], env[i]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (env);
}

void	ft_exec(char **spli, char **path, char **env, int i)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		dup2(g_stock.out, STDOUT_FILENO);
		dup2(g_stock.in, STDIN_FILENO);
		execve(path[i], spli, env);
	}
	else
	{
		waitpid(id, 0, 0);
		free_spli(path);
		free_spli(spli);
	}
	if (g_stock.out > 1)
		close(g_stock.out);
	if (g_stock.in > 0)
		close(g_stock.in);
}

void	init_var_cmd(void)
{
	g_stock.chkcrash = 0;
	g_stock.in = 0;
	g_stock.out = 1;
}

int	ft_parse_cmd(char **spli, char **path)
{
	dup2(g_stock.out, STDOUT_FILENO);
	dup2(g_stock.in, STDIN_FILENO);
	if (g_stock.chkcrash < 0)
	{
		g_stock.out = 1;
		g_stock.in = 0;
		if (path)
			free_spli(path);
		return (0);
	}
	if (ft_redirect(spli) == 0)
	{
		if (path)
			free_spli(path);
		return (0);
	}
	if (path == NULL)
	{
		printf("%s: No such file or directory\n", spli[0]);
		return (0);
	}
	return (1);
}
