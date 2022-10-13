/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_and_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:13:17 by kcatrix           #+#    #+#             */
/*   Updated: 2022/10/13 14:59:02 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(char **spli)
{
	int		i;
	int		id;
	int		in;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin_spli(spli);
	del_quote(tmp);
	spli = ft_split(tmp, ' ');
	free_protect(tmp);
	i = 1;
	pipe(g_stock.pip);
	in = g_stock.pip[0];
	id = fork();
	if (id == 0)
		fixechopip(in, spli, i);
	else
		fixwait(id);
	free_spli_protect(spli);
}

void	free_spli_protect(char **spli)
{
	int	i;

	i = 0;
	if (!spli)
		return ;
	while (spli[i])
	{
		free_protect(spli[i]);
		i++;
	}
	free(spli);
}

char	*ft_strjoin_spli(char **spli)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp2 = NULL;
	tmp = NULL;
	i = 0;
	tmp = ft_mallocex(spli[i], tmp);
	i++;
	while (spli[i])
	{
		tmp2 = ft_mallocex(tmp, tmp2);
		free_protect(tmp);
		tmp = ft_strjoin_spe(tmp2, spli[i]);
		free_protect(tmp2);
		i++;
	}
	return (tmp);
}

char	*ft_strjoin_spe(char *s1, char *s2)
{
	char	*c;
	size_t	lena;
	size_t	lenb;

	if (!s1 || !s2)
		return (NULL);
	lena = strlen(s1);
	lenb = strlen(s2);
	c = (char *)malloc(sizeof(char) * (lena + (lenb + 2)));
	if (!c)
		return (NULL);
	return (ft_strjoin_spe2(s1, s2, c, lenb));
}

int	echo_option(char *spli)
{
	int	i;

	i = 1;
	if (spli[0] == '-')
	{
		while (spli[i])
		{
			if (spli[i] == 'n')
			{
				i++;
			}
			else
				return (1);
		}
		if (i == 1)
			return (1);
	}
	else
		return (1);
	return (0);
}
