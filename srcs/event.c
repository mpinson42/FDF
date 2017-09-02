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
}

int		key_pressed(int kc, t_gen *g)
{
	ft_clear(g);
	if (kc == 53)
		exit(0);
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
	if (kc == 117)
	{
		g->zoom = 2;
		g->x = 0;
		g->y = 0;
		g->yrot = -1;
		g->xrot = 0;
	}
	ft_test(g);
	return (0);
}

int		red_cross(t_gen *g)
{
	(void)g;
	exit(0);
	return (0);
}
