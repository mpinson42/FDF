/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:07:50 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/02 18:08:22 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key(int kc, t_gen *g)
{
	if (kc == 78)
		g->zoom -= 1;
	if (kc == 126)
		g->y -= 10;
	if (kc == 125)
		g->y += 10;
	if (kc == 123)
		g->x -= 10;
	if (kc == 124)
		g->x += 10;
	if (kc == 116)
		g->color += 1;
}

void	key_color(int kc, t_gen *g)
{
	if (kc == 89)
		g->red += 10;
	if (kc == 86)
		g->red -= 10;
	if (kc == 91)
		g->green += 10;
	if (kc == 87)
		g->green -= 10;
	if (kc == 92)
		g->blue += 10;
	if (kc == 88)
		g->blue -= 10;
	if (kc == 117)
	{
		g->zoom = 2;
		g->x = 0;
		g->y = 0;
		g->yrot = -1;
		g->xrot = 0;
		g->color = 42;
		g->red = 48;
		g->green = 113;
		g->blue = 51;
	}
}

int		key_pressed(int kc, t_gen *g)
{
	if (kc == 19)
		bmp_write(g);
	ft_clear(g);
	if (kc == 53)
	{
		system("killall afplay");
		exit(0);
	}
	ft_key(kc, g);
	if (kc == 69)
		g->zoom += 0.1;
	if (kc == 13)
		g->yrot -= 1;
	if (kc == 1)
		g->yrot += 1;
	if (kc == 0)
		g->xrot -= 1;
	if (kc == 2)
		g->xrot += 1;
	key_color(kc, g);
	ft_test(g);
	return (0);
}

int		red_cross(t_gen *g)
{
	(void)g;
	system("killall afplay");
	exit(0);
	return (0);
}

void	ft_putpixel_in_img(int x, int y, t_gen *g, int color)
{
	if ((unsigned long long int)((x * 4) + (y * 2560 * 4)) >
			(unsigned long long int)(2560 * 1440 * 4) ||
			(unsigned long long int)((x * 4) + (y * 2560 * 4))
			<= 0 || x > 2560 || x < 0 || y < 0 || y > 1440)
		return ;
	if (color != 0)
	{
		if (color == 1 || color == 2)
			color = 0x00FFFFFF;
		color = ft_absolut(color);
		g->img_ptr[(x * 4) + (y * 2560 * 4)] = color % 256 + g->red;
		g->img_ptr[(x * 4) + (y * 2560 * 4) + 1] = color % 256 + g->green;
		g->img_ptr[(x * 4) + (y * 2560 * 4) + 2] = color % 256 + g->blue;
		g->img_ptr[(x * 4) + (y * 2560 * 4) + 3] = 0;
	}
	else
	{
		g->img_ptr[(x * 4) + (y * 2560 * 4)] = 0;
		g->img_ptr[(x * 4) + (y * 2560 * 4) + 1] = 0;
		g->img_ptr[(x * 4) + (y * 2560 * 4) + 2] = 0;
		g->img_ptr[(x * 4) + (y * 2560 * 4) + 3] = 0;
	}
}
