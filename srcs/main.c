/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:38:50 by tnicoue           #+#    #+#             */
/*   Updated: 2022/09/13 15:39:09 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	supp_env(char **env)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH", 4) == 0)
			x = 1;
		i++;
	}
	if (x == 0)
		return (1);
	else
		return (0);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		id;
	int		i;

	ac = 0;
	i = 0;
	av = NULL;
	id = 0;
	g_stock.cpenv = ft_cp_env(env);
	verif_export_exist(i);
	set_signal(0);
	g_stock.nbpip = 0;
	g_stock.nbpassage = 0;
	while (1)
	{
		if ((g_stock.nbpassage == 0) && (g_stock.nbpip == 0))
		{
			line = readline("minishell >");
			add_history(line);
		}
		ft_cmd(line, env);
		if ((g_stock.nbpassage) == g_stock.nbpip + 1)
		{
			g_stock.nbpassage = 0;
			g_stock.nbpip = 0;
		}
	}
	free(line);
}

void	verif_export_exist(int i)
{
	if (!g_stock.cpexp)
	{
		while (g_stock.cpenv[i])
			i++;
		g_stock.cpexp = malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (g_stock.cpenv[i])
		{
			ft_triexport(g_stock.cpenv[i]);
			i++;
		}
		signal(SIGINT, interrupt_signal);
		signal(SIGQUIT, quit_signal);
		signal(11, quit_signal);
	}
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

void	f_exit(char **spli)
{
	int	exit_status;

	exit_status = 0;
	if (spli[1])
	{
		if (is_num(spli[1]) == 1)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				spli[1]);
			return ;
		}
		if (spli[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		exit_status = ft_atoi(spli[1]);
	}
	printf("exit\n");
	g_stock.end = exit_status;
	exit(exit_status);
}

/* CPexp = Export (env trie) Cpenv = environnement 
exportadd : on va free le export actuel apres avoir cree une copie de ce dernier 
dans cpcpenv, on remalloc le cpexp a sa longueur + 1 (parce qu on va rajouter une
variable d environnement)

Puis a l aide de strcmp et ft_preline, il va comparer les valeurs ascii des noms
de variable d environnement avant les '=',
 si ce resultat (nouvelle valeur - valeur pointee de exp)
 est inferieur a 0, la nouvelle valeur se situe a l emplacement actuel
 
*/