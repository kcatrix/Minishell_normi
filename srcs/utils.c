/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:40:20 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/13 15:49:50 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_spe2(char *s1, char *s2, char *c, size_t lenb)
{
	size_t	y;
	size_t	i;
	size_t	j;
	size_t	lena;

	lena = strlen(s1);
	i = 0;
	j = 0 - lena;
	y = 0;
	while (i < lena + (lenb + 1))
	{
		if (i == lena)
		{
			c[i] = 32;
			i++;
		}
		c[i] = s1[y];
		if (i >= lena)
			c[i] = s2[j];
		y++;
		j++;
		i++;
	}
	c[i] = '\0';
	return (c);
}

void	ft_getchevquo(char **spli)
{
	int	i;
	int	y;
	int	j;

	j = 0;
	y = 0;
	i = 0;
	while (spli[i])
	{
		while (spli[i][y])
		{
			if ((spli[i][y] == '"' || spli[i][y] == '\'') && j == 0)
			{
				j = 1;
				g_stock.debquot = i;
			}
			else if ((spli[i][y] == '"' || spli[i][y] == '\'') && j == 1)
			{
				g_stock.finquot = i;
			}
			y++;
		}
		y = 0;
		i++;
	}
}

int	verif_pipe2(char *line)
{
	int	i;

	i = 0;
	while (((line[i] == 32) || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == '|' && i > 0)
		return (0);
	return (1);
}

void	quotestate(void)
{
	g_stock.test = ft_split(g_stock.line2[g_stock.nbpassage], ' ');
	ft_getchevquo(g_stock.test);
}

void	fixfin(void)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	g_stock.test = malloc(sizeof(char *) * 100);
	while (g_stock.test[i])
	{
		g_stock.test[i] = ft_strdup("");
		free(g_stock.test[i]);
		i++;
	}
}

int	chevinq(char *line)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while(line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && w == 0)
		{
			w++;
			i++;
		}
		if ((line[i] == '"' || line[i] == '\'') && w == 1)
		{
			w--;
			i++;
		}
		if ((line[i] == '>' || line[i] == '<') && w == 1)
			return(0);
		i++;
	}
	return (1);
}