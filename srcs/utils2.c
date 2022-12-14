/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:57:47 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/13 15:58:14 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	chevinq(char *line)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	while (line[i])
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
			return (0);
		i++;
	}
	return (1);
}
