/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:08:13 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/02 18:27:32 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_check(char *str)
{
	char	**tab;
	int		i;
	int		y;

	i = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[i])
	{
		y = 0;
		while (str[y] && str[y] != ',')
		{
			if ((str[y] != '-' && str[y] != 32 && 1 != ft_isdigit(str[y]))
				|| ft_strlen(tab[i]) > 11 ||
				(ft_atol(tab[i]) > 2147483647 ||
					ft_atol(tab[i]) < -2147483648))
			{
				return (-1);
			}
			y++;
		}
		i++;
	}
	ft_free_tab(tab);
	return (0);
}

int	go_malloc1(char **tab, int y, t_gen *g)
{
	int i;

	i = 0;
	g->color = 42;
	if (!(g->ad_x[y] = malloc(sizeof(int) * ft_strlen_tab(tab))))
		return (-1);
	if (!(g->ad_y[y] = malloc(sizeof(int) * ft_strlen_tab(tab))))
		return (-1);
	if (!(g->ad_z[y] = malloc(sizeof(int) * ft_strlen_tab(tab))))
		return (-1);
	if (!(g->bd_x[y] = malloc(sizeof(int) * ft_strlen_tab(tab))))
		return (-1);
	if (!(g->bd_y[y] = malloc(sizeof(int) * ft_strlen_tab(tab))))
		return (-1);
	i = 0;
	while (i < ft_strlen_tab(tab))
	{
		g->ad_z[y][i] = ft_atoi(tab[i]);
		g->ad_y[y][i] = y * 10;
		g->ad_x[y][i] = i * 10;
		free(tab[i]);
		i++;
	}
	return (0);
}

int	ft_init(t_gen *g, char *pass)
{
	int		fd;
	char	*test;
	char	**tab;
	int		y;

	y = 0;
	g->zoom = 2;
	g->yrot = -1;
	g->xrot = 0;
	if ((fd = open(pass, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &test) > 0)
	{
		tab = ft_strsplit(test, ' ');
		g->larg_y = ft_strlen_tab(tab);
		if (-1 == (go_malloc1(tab, y, g)))
			return (-1);
		free(test);
		free(tab);
		y++;
	}
	close(fd);
	free(test);
	return (0);
}

int	go_malloc2(t_gen *g, int lang)
{
	if (lang == -1)
		return (-1);
	if (!(g->ad_x = malloc(sizeof(int *) * g->larg_x)))
		return (-1);
	if (!(g->ad_y = malloc(sizeof(int *) * g->larg_x)))
		return (-1);
	if (!(g->ad_z = malloc(sizeof(int *) * g->larg_x)))
		return (-1);
	if (!(g->bd_x = malloc(sizeof(int *) * g->larg_x)))
		return (-1);
	if (!(g->bd_y = malloc(sizeof(int *) * g->larg_x)))
		return (-1);
	return (0);
}

int	ft_pars(t_gen *g, char *pass)
{
	int		fd;
	char	*test;
	int		lang;

	lang = -1;
	g->red = 48;
	g->green = 113;
	g->blue = 51;
	if ((fd = open(pass, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &test) > 0)
	{
		if ((lang != -1 && lang != ft_strlen_s(test)) || ft_check(test) == -1)
			return (-1);
		g->larg_x++;
		lang = ft_strlen_s(test);
		free(test);
	}
	if (g->larg_x <= 1 || go_malloc2(g, lang) == -1)
		return (-1);
	close(fd);
	ft_init(g, pass);
	free(test);
	return (0);
}
