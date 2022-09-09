/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:17:04 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/05 11:19:31 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_preline(char *line)
{
	char	*line2;
	int		i;

	i = 0;
	line2 = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		line2[i] = line[i];
		i++;
	}
	line2[i] = '\0';
	i = 0;
	while (line2[i])
	{
		if (line2[i] == '=')
		{
			line2[i] = '\0';
		}
		i++;
	}
	return (line2);
}

int	veriflen(char **spli, int i)
{
	if (ft_strlen(spli[1]) > ft_strlen(ft_preline(g_stock.cpenv[i])))
		return (ft_strlen(spli[1]));
	else
		return (ft_strlen(ft_preline(g_stock.cpenv[i])));
}

int	ft_parseexport(char *spli)
{
	int		i;
	char	*line;

	line = ft_preline(spli);
	i = 0;
	while (line[i])
		i++;
	i--;
	while ((i >= 0 && ft_isdigit(line[i]) == 1) || (i >= 0 && line[i] == '_'))
		i--;
	if (i == -1)
		return (1);
	while ((i >= 0 && ft_isalpha(line[i]) == 1) || (i >= 0 && line[i] == '_'))
		i--;
	if (i == -1)
		return (0);
	return (1);
}

char	**ft_exportaff(char *line, char **newline)
{
	int	i;

	i = 0;
	while (line[i])
	{
		newline[0][i] = line[i];
		if (line[i] == '=')
		{
			i++;
			newline[0][i] = '"';
			i++;
			while (line[i])
			{
				newline[0][i] = line[i - 1];
				i++;
			}
			newline[0][i] = line[i - 1];
			newline[0][++i] = '"';
			newline[0][++i] = '\0';
			return (newline);
		}
		i++;
	}
	newline[0][i] = '\0';
	return (newline);
}

void	ft_export_noarg(void)
{
	int		i;
	char	*line;

	i = 0;
	while (g_stock.cpexp[i])
	{
		line = malloc(sizeof(char) * ft_strlen(g_stock.cpexp[i]) + 3);
		line = *ft_exportaff(g_stock.cpexp[i], &line);
		printf("declare -x %s\n", line);
		free(line);
		i++;
	}
}
