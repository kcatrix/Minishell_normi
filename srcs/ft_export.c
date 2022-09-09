/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:15:16 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/05 13:38:05 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_triexport(char *str)
{
	int		i;

	g_stock.save = NULL;
	g_stock.save2 = NULL;
	i = 0;
	while (g_stock.cpexp[i])
	{
		g_stock.save = ft_preline(str);
		g_stock.save2 = ft_preline(g_stock.cpexp[i]);
		if (ft_strcmp(g_stock.save, g_stock.save2) < 0)
		{
			str = ft_first_tri(str, i);
			return ;
		}
		free(g_stock.save);
		free(g_stock.save2);
		i++;
	}
	if (verif_ex_exist() == 1)
		return ;
	free(g_stock.cpexp[i]);
	g_stock.cpexp[i] = ft_mallocex(str, g_stock.cpexp[i]);
	g_stock.cpexp[i + 1] = NULL;
	return ;
}

char	**ft_exptoenv2(void)
{
	int		i;
	int		y;
	char	**cpcpenv;

	i = 0;
	y = 0;
	while (g_stock.cpenv[i])
		i++;
	cpcpenv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	cpcpenv = ft_exptoenv2_boucle(cpcpenv, i, y);
	return (cpcpenv);
}

void	ft_exportadd(int i, char *spli)
{
	char	**cpcpexp;
	int		y;
	int		z;

	y = 0;
	z = 0;
	if (ft_verifdoublon(spli) == 0)
		return ;
	cpcpexp = ft_mallocexportadd();
	ft_exptoenv(spli);
	ft_exportadd_boucle(cpcpexp, i, spli, y);
}

void	ft_exportadd_boucle(char **cpcpexp, int i, char *spli, int y)
{
	while (cpcpexp[i])
	{
		if (ft_strcmp(ft_preline(spli), ft_preline(cpcpexp[i])) < 0)
		{
			g_stock.cpexp[i] = ft_mallocex(spli, g_stock.cpexp[i]);
			y = i;
			i++;
			while (cpcpexp[y])
			{
				g_stock.cpexp[i] = ft_mallocex(cpcpexp[y], g_stock.cpexp[i]);
				free(cpcpexp[y]);
				y++;
				i++;
			}
			g_stock.cpexp[i] = NULL;
			free(cpcpexp);
			return ;
		}
		g_stock.cpexp[i] = ft_mallocex(cpcpexp[i], g_stock.cpexp[i]);
		free(cpcpexp[i]);
		i++;
	}
	cpcpexp = ft_exportadd_boucle_end(cpcpexp, i, spli);
}

char	**ft_exportadd_boucle_end(char **cpcpexp, int i, char *spli)
{
	g_stock.cpexp[i] = ft_mallocex(spli, g_stock.cpexp[i]);
	g_stock.cpexp[i + 1] = NULL;
	free(cpcpexp[i]);
	free(cpcpexp);
	return (cpcpexp);
}