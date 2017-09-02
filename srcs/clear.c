/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 19:11:14 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/02 19:11:15 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_clear_calcu(t_gen *g)
{
	int i;
	int y;

	i = -1;
	while (++i < 80)
	{
		y = -1;
		while (++y < 200)
			mlx_pixel_put(g->mlx, g->win, y, i, 0);
	}
	i = -1;
	while (++i < g->larg_x)
	{
		y = -1;
		while (++y < g->larg_y)
		{
			g->bd_x[i][y] = (g->ad_x[i][y] +
				(g->ad_z[i][y] * g->xrot) - g->ad_y[i][y]) * g->zoom;
			g->bd_y[i][y] = (g->ad_x[i][y] +
				(g->ad_z[i][y] * g->yrot) + g->ad_y[i][y]) * g->zoom;
		}
	}
}

void	ft_clear_algo(t_gen *g, int test, int i, int y)
{
	test = -1;
	while (++test < i)
	{
		g->x0 = g->bd_x[test][y];
		g->y0 = g->bd_y[test][y];
		g->x1 = g->bd_x[test + 1][y];
		g->y1 = g->bd_y[test + 1][y];
		bresenham_2(g);
	}
	test = -1;
	while (++test < y)
	{
		g->x0 = g->bd_x[i][test];
		g->y0 = g->bd_y[i][test];
		g->x1 = g->bd_x[i][test + 1];
		g->y1 = g->bd_y[i][test + 1];
		bresenham_2(g);
	}
}

void	ft_clear(t_gen *g)
{
	int i;
	int y;

	ft_clear_calcu(g);
	i = -1;
	while (++i < g->larg_x - 1)
	{
		y = -1;
		while (++y < g->larg_y - 1)
		{
			g->x0 = g->bd_x[i][y];
			g->y0 = g->bd_y[i][y];
			g->x1 = g->bd_x[i + 1][y];
			g->y1 = g->bd_y[i + 1][y];
			bresenham_2(g);
			g->x0 = g->bd_x[i][y];
			g->y0 = g->bd_y[i][y];
			g->x1 = g->bd_x[i][y + 1];
			g->y1 = g->bd_y[i][y + 1];
			bresenham_2(g);
		}
	}
	ft_clear_algo(g, 0, i, y);
}
