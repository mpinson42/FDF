/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 19:11:51 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/02 19:11:52 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

typedef	struct		s_gen
{
	int				**ad_x;
	int				**ad_y;
	int				**ad_z;
	int				**bd_x;
	int				**bd_y;
	int				larg_x;
	int				larg_y;
	void			*win;
	void			*mlx;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	float			zoom;
	int				x;
	int				y;
	float			xrot;
	float			yrot;
	int				test;
}					t_gen;

typedef	struct		s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_bresenham;

void				ft_clear(t_gen *g);
int					ft_strlen_s(char *str);
int					ft_strlen_tab(char **tab);
int					ft_check(char *str);
int					ft_pars(t_gen *g, char *pass);
void				bresenham(t_gen *g, int color);
int					key_pressed(int kc, t_gen *g);
int					red_cross(t_gen *g);
void				ft_test(t_gen *g);
void				bresenham_2(t_gen *g);
void				ft_free_tab(char **tab);
long				ft_atol(const char *str);

#endif
