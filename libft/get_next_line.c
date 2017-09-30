/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:48:28 by mpinson           #+#    #+#             */
/*   Updated: 2017/03/12 18:48:35 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check_static(t_env *e, char **line)
{
	int		i;
	char	*test;

	i = 0;
	if (ft_strchr(e->str, '\n') != NULL)
	{
		while (e->str[i] && e->str[i] != '\n')
			i++;
		line[0] ? free(line[0]) : 0;
		test = ft_strsub(e->str, 0, i);
		line[0] = ft_strjoin(line[0], test);
		free(test);
		e->str ? free(e->str) : 0;
		e->str = ft_strsub(e->str, i + 1, BUFF_SIZE);
		return (1);
	}
	else
	{
		line[0] ? free(line[0]) : 0;
		line[0] = ft_strjoin(line[0], e->str);
	}
	return (0);
}

static void		ft_suit2(t_env *e, char **line, char str[BUFF_SIZE + 1])
{
	int		i;
	char	*non;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line[0] ? free(line[0]) : 0;
	non = ft_strsub(str, 0, i);
	line[0] = ft_strjoin(line[0], non);
	free(non);
	e->str ? free(e->str) : 0;
	e->str = ft_strsub(str, i + 1, BUFF_SIZE);
}

static int		ft_suit(char **line, t_env *e, int fd)
{
	char	str[BUFF_SIZE + 1];
	int		test;

	ft_bzero(str, BUFF_SIZE + 1);
	while ((test = read(fd, str, BUFF_SIZE)) > 0)
	{
		if (ft_strchr(str, '\n') != NULL)
		{
			ft_suit2(e, line, str);
			return (1);
		}
		else
		{
			line[0] ? free(line[0]) : 0;
			line[0] = ft_strjoin(line[0], str);
		}
		ft_bzero(str, BUFF_SIZE + 1);
	}
	if (fd < 0 || test == -1)
		return (-1);
	return (0);
}

static int		ft_fin(t_env *e, char **line)
{
	if (line[0][0] != 0 && e->bol == 0)
	{
		e->bol = 1;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_env	*e = NULL;
	int				i;

	i = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	if (!e || e->fd != fd)
	{
		e ? free(e) : 0;
		if (!(e = (t_env *)malloc(sizeof(t_env))))
			return (-1);
		e->next = NULL;
		e->presed = NULL;
		e->str = NULL;
		e->fd = fd;
		e->bol = 0;
	}
	line[0] = ft_strdup("");
	if (e->str && ft_check_static(e, line) == 1)
		return (1);
	if ((i = ft_suit(line, e, fd)) != 0)
		return (i);
	return (ft_fin(e, line));
}
