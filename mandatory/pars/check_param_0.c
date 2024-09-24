/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 20:09:11 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/24 19:31:56 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_open_tex(t_texture *texture)
{
	int	i;
	int	len;

	i = -1;
	while (++i < 4)
	{
		len = ft_strlen(texture[i].path);
		if (!(len >= 4 && !(ft_strcmp(texture[i].path + len - 4, ".png"))))
			return (ft_putendl_fd("ERROR: textures not png", 2), -1);
		if (open(texture[i].path, O_RDONLY) == -1)
			return (ft_putendl_fd("ERROR: textures not found", 2), -1);
		texture[i].tex_png = mlx_load_png(texture[i].path);
	}
	return (0);
}

int	check_texture(t_texture *texture)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3 && texture[i].path)
	{
		j = i;
		while (++j < 4 && texture[j].path)
			if (texture[i].identifier == texture[j].identifier)
				return (ft_putendl_fd("ERROR2", 2), -1);
		if (j < 4 && !texture[j].path)
			return (ft_putendl_fd("ERROR: missing textures", 2), -1);
	}
	if (i < 4 && !texture[i].path)
		return (ft_putendl_fd("ERROR: missing textures", 2), -1);
	return (check_open_tex(texture));
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
