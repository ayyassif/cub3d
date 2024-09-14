/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:09:11 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/14 15:09:03 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_texture(t_texture *texture)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (i < 3)
	{
		j = i + 1;
		while (j < 4)
		{
			if (texture[i].identifier == texture[j].identifier)
				return (ft_putendl_fd("ERROR", 2), -1);
			len = ft_strlen(texture[i].path);
			if (len < ft_strlen(texture[j].path))
				len = ft_strlen(texture[j].path);
			if (!ft_strncmp(texture[i].path, texture[j].path, len))
				return (ft_putendl_fd("ERROR", 2), -1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_colors(t_color *floor, t_color *ceiling)
{
	if (floor->red == -1 || floor->blue == -1 || floor->green == -1)
		return (-1);
	if (ceiling->red == -1 || ceiling->blue == -1 || ceiling->green == -1)
		return (-1);
	return (0);
}

int	check_file_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	return (!(len >= 4 && !ft_strcmp(file + len - 4, ".cub")));
}

static int	check_empty(t_cub *cub, size_t ln, size_t col)
{
	if (ln == 0 || ln == cub->height - 1 || col == 0 || col == cub->width - 1)
		return (-1);
	if (cub->map[ln - 1][col].value == M_VOID)
		return (-1);
	if (cub->map[ln + 1][col].value == M_VOID)
		return (-1);
	if (cub->map[ln][col - 1].value == M_VOID)
		return (-1);
	if (cub->map[ln][col + 1].value == M_VOID)
		return (-1);
	return (0);
}

int	pars_map(t_cub *cub)
{
	size_t	ln;
	size_t	col;
	int		p;

	p = 0;
	ln = -1;
	while (++ln < cub->height)
	{
		col = -1;
		while (++col < cub->width)
		{
			if ((cub->map[ln][col].value == M_FLOOR
				|| cub->map[ln][col].value == M_PLAYER)
				&& check_empty(cub, ln, col) == -1)
				return (ft_putendl_fd("ERROR", 2), -1);
			if (cub->map[ln][col].value == M_PLAYER)
			{
				p++;
				cub->map[ln][col].value = M_FLOOR;
			}
		}
	}
	if (p != 1)
		return (ft_putendl_fd("ERROR", 2), -1);
	return (0);
}
