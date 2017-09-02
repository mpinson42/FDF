/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:07:57 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/02 18:18:31 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_strlen_s(char *str)
{
	char	**tab;
	int		i;

	tab = ft_strsplit(str, ' ');
	i = ft_strlen_tab(tab);
	ft_free_tab(tab);
	return (i);
}

void	bresenham(t_gen *g, int color)
{
	t_bresenham b;

	b.dx = ft_absolut(g->x1 - g->x0);
	b.dy = ft_absolut(g->y1 - g->y0);
	b.sx = g->x0 < g->x1 ? 1 : -1;
	b.sy = g->y0 < g->y1 ? 1 : -1;
	b.err = (b.dx > b.dy ? b.dx : -b.dy) / 2;
	while (42)
	{
		mlx_pixel_put(g->mlx, g->win, g->x0
			+ 2560 / 4 + g->x, g->y0 + 1440 / 4 + g->y, color);
		if ((g->x0 == g->x1 && g->y0 == g->y1))
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			g->x0 += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			g->y0 += b.sy;
		}
	}
}

void	bresenham_2(t_gen *g)
{
	t_bresenham b;

	b.dx = ft_absolut(g->x1 - g->x0);
	b.dy = ft_absolut(g->y1 - g->y0);
	b.sx = g->x0 < g->x1 ? 1 : -1;
	b.sy = g->y0 < g->y1 ? 1 : -1;
	b.err = (b.dx > b.dy ? b.dx : -b.dy) / 2;
	while (42)
	{
		mlx_pixel_put(g->mlx, g->win, g->x0
			+ 2560 / 4 + g->x, g->y0 + 1440 / 4 + g->y, 0);
		if (g->x0 == g->x1 && g->y0 == g->y1)
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.dx)
		{
			b.err -= b.dy;
			g->x0 += b.sx;
		}
		if (b.e2 < b.dy)
		{
			b.err += b.dx;
			g->y0 += b.sy;
		}
	}
}
