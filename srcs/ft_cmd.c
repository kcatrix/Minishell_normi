/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:38:47 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/09 04:53:57 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*

pipe gerer les quotes correctement, gerer les pipes chelous

env affiche pas les variables vides et export oui
 
EXPORT ; La commande export marque une variable d'environnement à exporter 
avec tout processus enfant nouvellement créé et permet ainsi à un processus 
enfant d'hériter de toutes les variables marquées.
*/
/*char	**ft_verifparam(char *env, t_stock *env2)
{
	int	i;

	i = 0;
	while(env[i])
	{
		
	}
}*/
/*char	*ft_suppr(char *tmp, char *spli)
{
	int	i;

	i = 0;
	while (tmp[i] == spli[i])
	{
		i++;
	}
	tmp[i] = '\0';
	printf("tmp == %s\n", tmp);
	return (tmp);
}*/

void	free_spli(char **spli)
{
	int	i;

	i = 0;
	while (spli[i])
	{
		free(spli[i]);
		i++;
	}
	free(spli);
}

char	**ft_cp_env(char **env)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		tmp[i] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		j = 0;
		while (env[i][j])
		{
			tmp[i][j] = env[i][j];
			j++;
		}
		tmp[i][j] = '\0';
		i++;
	}
	return (tmp);
}

// securitee a rajouter pour verifier l existence du parametre au sein de l env
// stocker les differents parametre dans un tableau

char	**cmd_unset(char **spli, char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	if (ft_verifexistunset(env, spli) == 1)
		return (env);
	tmp = ft_cp_env(env);
	cmd_unset2(spli, tmp, env, i);
	fix_out_inr_redir();
	return (env);
}

int	ft_redirect(char **spli)
{
	if (ft_strcmp(spli[0], "unset") == 0)
	{
		if (!spli[1])
			return (0);
		g_stock.cpenv = cmd_unset(spli, g_stock.cpenv);
		g_stock.cpexp = cmd_unset(spli, g_stock.cpexp);
		free_spli(spli);
		return (0);
	}
	else if (ft_strcmp(spli[0], "echo") == 0)
	{
		cmd_echo(spli);
		return (0);
	}
	else if (ft_strcmp(spli[0], "cd") == 0)
	{
		cmd_cd(spli);
		return (0);
	}
	if (ft_redirect_2(spli) == 0)
	{
		g_stock.end = 0;
		return (0);
	}
	return (1);
}

int	ft_cmd(char *line, char **env)
{
	char	**path;
	char	**spli;
	int		i;

	i = 0;
	init_var_cmd();
	if (verif_space(line) == 0 || line[0] == 0)
		return (0);
	del_quote(line);
	path = path_fct(g_stock.cpenv);
	spli = ft_split(line, ' ');
	spli = parse(spli);
	if (spli[0] == NULL)
		return (0);
	ft_verif_chevron(spli);
	if (ft_parse_cmd(spli, path) == 0) 
		return (0);
	i = verif_exist(path, spli[0]);
	if (last_check(i, path, spli[0]) == -1)
		return (-1);
	ft_exec(spli, path, env, i);
	g_stock.end = 0;
	return (0);
}
 