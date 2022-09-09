/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:21:16 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/05 15:20:28 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_verifenv(char *spli)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (ft_strcmp(ft_preline(spli), ft_preline(g_stock.cpenv[i])) == 0)
		{
			free(g_stock.cpenv[i]);
			g_stock.cpenv[i] = ft_mallocex(spli, g_stock.cpenv[i]);
			i = 0;
			while (g_stock.cpexp[i])
			{
				if (ft_strcmp(ft_preline(spli),
						ft_preline(g_stock.cpexp[i])) == 0)
				{
					free(g_stock.cpexp[i]);
					g_stock.cpexp[i] = ft_mallocex(spli, g_stock.cpexp[i]);
				}
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_mallocunset(char **stockset)
{
	int		i;
	int		y;
	char	**cpcpenv;

	i = 0;
	y = 0;
	while (stockset[i])
		i++;
	cpcpenv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	cpcpenv = ft_mallocunset_boucle(cpcpenv, i, y, stockset);
	return (cpcpenv);
}

char	**ft_mallocunset_boucle(char **cpcpenv, int i, int y, char **stockset)
{
	while (stockset[i])
	{
		cpcpenv[i] = malloc(sizeof(char) * ft_strlen(stockset[i]) + 1);
		while (stockset[i][y])
		{
			cpcpenv[i][y] = stockset[i][y];
			y++;
		}
		cpcpenv[i][y] = '\0';
		y = 0;
		free(stockset[i]);
		i++;
	}
	cpcpenv[i] = NULL;
	free(g_stock.cpexp);
	g_stock.cpexp = malloc(sizeof(char *) * (i + 2));
	return (cpcpenv);
}

char	**ft_mallocexportadd(void)
{
	int		i;
	int		y;
	char	**cpcpenv;

	i = 0;
	y = 0;
	while (g_stock.cpexp[i])
		i++;
	cpcpenv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	cpcpenv = ft_mallocexportadd_boucle(cpcpenv, i, y);
	return (cpcpenv);
}

char	**ft_mallocexportadd_boucle(char **cpcpenv, int i, int y)
{
	while (g_stock.cpexp[i])
	{
		cpcpenv[i] = malloc(sizeof(char) * ft_strlen(g_stock.cpexp[i]) + 1);
		while (g_stock.cpexp[i][y])
		{
			cpcpenv[i][y] = g_stock.cpexp[i][y];
			y++;
		}
		cpcpenv[i][y] = '\0';
		y = 0;
		free(g_stock.cpexp[i]);
		i++;
	}
	cpcpenv[i] = NULL;
	free(g_stock.cpexp);
	g_stock.cpexp = malloc(sizeof(char *) * (i + 2));
	return (cpcpenv);
}
