/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcatrix <kcatrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:14:19 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/01 15:14:39 by kcatrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verifline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

/*void	ft_recup_export()
{
	recuperer le export
}*/

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_stock.cpenv[i])
	{
		if (verifline(g_stock.cpenv[i]) == 0)
			printf("%s\n", g_stock.cpenv[i]);
		i++;
	}
}
