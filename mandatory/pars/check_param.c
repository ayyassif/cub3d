/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:09:11 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/24 10:12:15 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_tex(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		cub->texture[i].texture_png = mlx_load_png(cub->texture[i].path);
}

int	check_texture(t_texture *texture)
{
	int		i;
	int		j;
	size_t	len;

	i = -1;
	while (++i < 3 && texture[i].path)
	{
		len = ft_strlen(texture[i].path);
		if (!(len >= 4 && !(ft_strcmp(texture[i].path + len - 4, ".png"))))
			return (ft_putendl_fd("ERROR: textures not png", 2), -1);
		j = i;
		while (++j < 4 && texture[j].path)
			if (texture[i].identifier == texture[j].identifier)
				return (ft_putendl_fd("ERROR2", 2), -1);
		if (j < 4 && !texture[j].path)
			return (ft_putendl_fd("ERROR: missing textures", 2), -1);
	}
	if (i < 4 && !texture[i].path)
		return (ft_putendl_fd("ERROR: missing textures", 2), -1);
	len = ft_strlen(texture[i].path);
	if (!(len >= 4 && !(ft_strcmp(texture[i].path + len - 4, ".png"))))
		return (ft_putendl_fd("ERROR: textures not png", 2), -1);
	return (0);
}

int	check_colors(t_color *floor, t_color *ceiling)
{
	if (floor->red < 0 || floor->red > 255)
		return (ft_putendl_fd("ERROR: floor color invalid", 2), -1);
	if (floor->green < 0 || floor->green > 255)
		return (ft_putendl_fd("ERROR: floor color invalid", 2), -1);
	if (floor->blue < 0 || floor->blue > 255)
		return (ft_putendl_fd("ERROR: floor color invalid", 2), -1);
	if (ceiling->red < 0 || ceiling->red > 255)
		return (ft_putendl_fd("ERROR: celling color invalid", 2), -1);
	if (ceiling->green < 0 || ceiling->green > 255)
		return (ft_putendl_fd("ERROR: celling color invalid", 2), -1);
	if (ceiling->blue < 0 || ceiling->blue > 255)
		return (ft_putendl_fd("ERROR: celling color invalid", 2), -1);
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
				return (ft_putendl_fd("ERROR: invalid wall", 2), -1);
			if (cub->map[ln][col].value == M_PLAYER)
			{
				p++;
				cub->map[ln][col].value = M_FLOOR;
			}
		}
	}
	if (p != 1)
		return (ft_putendl_fd("ERROR: number of player", 2), -1);
	return (0);
}
