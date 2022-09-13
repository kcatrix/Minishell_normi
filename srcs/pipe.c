/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:18:41 by kevyn             #+#    #+#             */
/*   Updated: 2022/09/13 15:08:50 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	strlen_pipe(char *line)
{
	int i;
	int y;
	
	i = 0;
	y = 0;
	while(line[i])
	{
		if(line[i] == '|')
			y++;
		i++;	
	}
	return(y);
}

void	spli_pipe(char *line)
{
	char **line2;

	line2 = NULL;
	if (strlen_pipe(line) > 0)
		line2 = ft_split(line, '|');
	g_stock.line2 = line2;
}

/*void	ft_pipe(char **line2)
{
	
}*/