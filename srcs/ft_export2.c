/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:03:32 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/05 11:15:07 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(char **spli)
{
	int	i;

	i = 0;
	if (!spli[1])
		ft_export_noarg();
	else
	{	
		if (ft_parseexport(spli[1]) == 1)
		{
			return ;
		}
		else if (ft_verifenv(spli[1]) == 1)
		{
			return ;
		}
		ft_exportadd(i, spli[1]);
	}
}

void	ft_exptoenv(char *spli)
{
	char	**cpcpenv;
	int		i;

	i = 0;
	cpcpenv = ft_exptoenv2();
	while (cpcpenv[i])
	{
		g_stock.cpenv[i] = ft_mallocex(cpcpenv[i], g_stock.cpenv[i]);
		i++;
	}
	g_stock.cpenv[i] = ft_mallocex(spli, g_stock.cpenv[i]);
	g_stock.cpenv[i + 1] = NULL;
	return ;
}

int	ft_verifspli(char *spli)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (spli[i])
	{
		if (spli[i] == '=')
		{
			y = 1;
			while (spli[++i])
			{
				if (spli[i] != 22 && spli[i] != '\0')
					y = 1;
			}
		}
		i++;
	}
	return (y);
}

int	ft_verifdoublon(char *spli)
{
	int	i;

	i = 0;
	while (g_stock.cpexp[i])
	{
		if (strcmp(ft_preline(spli), ft_preline(g_stock.cpexp[i])) == 0)
		{
			if (ft_verifspli(spli) != 0)
				g_stock.cpexp[i] = ft_mallocex(spli, g_stock.cpexp[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_mallocex(char *str, char *str2)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (str);
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
