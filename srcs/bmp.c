/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 16:10:04 by mpinson           #+#    #+#             */
/*   Updated: 2017/10/07 16:10:09 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		size_img(void)
{
	int	pitch;
	int	padding;

	pitch = (IMG_WIDTH) * 3;
	if (pitch % 4 != 0)
		pitch += 4 - (pitch % 4);
	padding = pitch - ((IMG_WIDTH) * 3);
	return (3 * ((IMG_WIDTH) + padding) * (IMG_HEIGHT));
}

void	set_bmp_file(int fd)
{
	static char	bmp[54] = {0};

	bmp[0] = 'B';
	bmp[1] = 'M';
	*(int*)(bmp + 34) = ((IMG_WIDTH) * 3 % 4)
		? ((IMG_WIDTH) + 4 - ((IMG_WIDTH) * 3) % 4) * (IMG_HEIGHT)
		: (IMG_WIDTH) * 3 * (IMG_HEIGHT);
	bmp[2] = 54 + *(int*)(bmp + 34);
	bmp[10] = 54;
	bmp[14] = 40;
	*(int*)(bmp + 18) = IMG_WIDTH;
	*(int*)(bmp + 22) = IMG_HEIGHT;
	bmp[26] = 1;
	bmp[28] = 24;
	write(fd, bmp, 54);
}

void	bmp_write_in(t_gen *g, int fd, char *buf)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = IMG_HEIGHT;
	while (--y >= 0)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			buf[i++] = g->img_ptr[4 * (x + y * IMG_WIDTH)];
			buf[i++] = g->img_ptr[4 * (x + y * IMG_WIDTH) + 1];
			buf[i++] = g->img_ptr[4 * (x + y * IMG_WIDTH) + 2];
		}
	}
	write(fd, buf, size_img());
}

void	bmp_write(t_gen *g)
{
	int		fd;
	char	*buf;

	fd = open("bmp.bmp", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		return ;
	set_bmp_file(fd);
	if (!(buf = (char*)malloc(sizeof(char) * size_img())))
		return ;
	bmp_write_in(g, fd, buf);
	free(buf);
	buf = NULL;
	close(fd);
}
