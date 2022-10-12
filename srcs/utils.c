/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:40:20 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/12 10:50:05 by tnicoue          ###   ########.fr       */
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
