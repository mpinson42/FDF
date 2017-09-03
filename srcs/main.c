/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:08:04 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/03 15:29:26 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_menu(t_gen *g)
{
	mlx_string_put(g->mlx, g->win, 0, 0, 0x00FFFFFF, "+/- zoom");
	mlx_string_put(g->mlx, g->win, 0, 15, 0x00FFFFFF, "fleche depalcement");
	mlx_string_put(g->mlx, g->win, 0, 30, 0x00FFFFFF, "w/a/s/d depalcer z");
	mlx_string_put(g->mlx, g->win, 0, 45, 0x00FFFFFF, "delete reset");
	mlx_string_put(g->mlx, g->win, 0, 60, 0x00FFFFFF, "page up change color");
	mlx_string_put(g->mlx, g->win, 0, 75, 0x00FFFFFF, "echap quitte");
}

void	ft_start_algo(t_gen *g, int *i, int *y, int color)
{
	while (++*i < g->larg_x - 1)
	{
		*y = -1;
		while (++*y < g->larg_y - 1)
		{
			if (g->ad_z[*i][*y] > g->ad_z[*i + 1][*y])
				color = g->ad_z[*i][*y];
			else
				color = g->ad_z[*i + 1][*y];
			g->x0 = g->bd_x[*i][*y];
			g->y0 = g->bd_y[*i][*y];
			g->x1 = g->bd_x[*i + 1][*y];
			g->y1 = g->bd_y[*i + 1][*y];
			bresenham(g, color + g->color);
			if (g->ad_z[*i][*y] > g->ad_z[*i][*y + 1])
				color = g->ad_z[*i][*y];
			else
				color = g->ad_z[*i][*y + 1];
			g->x0 = g->bd_x[*i][*y];
			g->y0 = g->bd_y[*i][*y];
			g->x1 = g->bd_x[*i][*y + 1];
			g->y1 = g->bd_y[*i][*y + 1];
			bresenham(g, color + g->color);
		}
	}
}

void	ft_last_line(t_gen *g, int i, int y, int color)
{
	while (++g->test < i)
	{
		if (g->ad_z[g->test][y] > g->ad_z[g->test + 1][y])
			color = g->ad_z[g->test][y];
		else
			color = g->ad_z[g->test + 1][y];
		g->x0 = g->bd_x[g->test][y];
		g->y0 = g->bd_y[g->test][y];
		g->x1 = g->bd_x[g->test + 1][y];
		g->y1 = g->bd_y[g->test + 1][y];
		bresenham(g, color + g->color);
	}
	g->test = -1;
	while (++g->test < y)
	{
		if (g->ad_z[i][g->test] > g->ad_z[i][g->test + 1])
			color = g->ad_z[i][g->test];
		else
			color = g->ad_z[i][g->test + 1];
		g->x0 = g->bd_x[i][g->test];
		g->y0 = g->bd_y[i][g->test];
		g->x1 = g->bd_x[i][g->test + 1];
		g->y1 = g->bd_y[i][g->test + 1];
		bresenham(g, color + g->color);
	}
}

void	ft_test(t_gen *g)
{
	int	i;
	int	y;

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
	i = -1;
	ft_start_algo(g, &i, &y, 0);
	g->test = -1;
	ft_last_line(g, i, y, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	ft_menu(g);
}

int		main(int argc, char **argv)
{
	t_gen g;

	ft_bzero(&g, sizeof(g));
	if (argc != 2 || argv[1][ft_strlen(argv[1]) - 1] != 'f'
			|| argv[1][ft_strlen(argv[1]) - 2] != 'd'
			|| argv[1][ft_strlen(argv[1]) - 3] != 'f'
			|| argv[1][ft_strlen(argv[1]) - 4] != '.')
	{
		ft_putstr("need file .fdf");
		return (0);
	}
	if (ft_pars(&g, argv[1]) == -1)
	{
		ft_putstr("error");
		return (0);
	}
	if (init(&g) == -1)
		return (0);
	ft_test(&g);
	mlx_hook(g.win, 2, 1L << 0, &key_pressed, &g);
	mlx_hook(g.win, 17, (1L << 17), &red_cross, &g);
	mlx_loop(g.mlx);
}
