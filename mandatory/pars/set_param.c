/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/30 10:36:00 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	dir_picker(char *line)
{
	int	j;

	j = 0;
	while (line[j] && !is_white_space(line[j]))
		j++;
	if (!ft_strncmp(line, "NO", j))
		return (E_NO);
	if (!ft_strncmp(line, "SO", j))
		return (E_SO);
	if (!ft_strncmp(line, "WE", j))
		return (E_WE);
	if (!ft_strncmp(line, "EA", j))
		return (E_EA);
	return (-1);
}

int	set_texture(t_texture *texture, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	texture->identifier = dir_picker(line);
	if (texture->identifier == (t_id)-1)
		return (ft_putendl_fd("ERROR", 2), -1);
	line += (i + 2);
	while (line[i] && is_white_space(line[i]))
		i++;
	if (!i)
		return (ft_putendl_fd("ERROR", 2), -1);
	while (line[i + j])
		j++;
	texture->path = ft_substr(line, i, j);
	if (!texture->path)
		return (ft_putendl_fd("error: malloc", 2), -1);
	return (0);
}

static int	set_colors(t_color *color, char *line)
{
	color->red = ft_atoi(line);
	if (color->red < 0 || color->red > 255)
		return (ft_putendl_fd("ERROR", 2), -1);
	while (*line && *line != ',')
		line++;
	if (!(*line))
		return (ft_putendl_fd("ERROR", 2), -1);
	color->green = ft_atoi(++line);
	if (color->green < 0 || color->green > 255)
		return (ft_putendl_fd("ERROR", 2), -1);
	while (*line && *line != ',')
		line++;
	if (!(*line))
		return (ft_putendl_fd("ERROR", 2), -1);
	color->blue = ft_atoi(++line);
	if (color->blue < 0 || color->blue > 255)
		return (ft_putendl_fd("ERROR", 2), -1);
	while (*line && *line >= '0' && *line <= '9')
		line++;
	if (*line)
		return (ft_putendl_fd("ERROR", 2), -1);
	return (0);
}

int	set_floor_ceiling(t_cub *cub, char *line)
{
	int	j;
	int	i;

	j = 0;
	while (line[j] && !is_white_space(line[j]))
		j++;
	i = j;
	while (line[i] && is_white_space(line[i]))
		i++;
	if (!ft_strncmp(line, "F", j))
	{
		if (set_colors(&cub->floor, line + i) == -1)
			return (-1);
	}
	else if (!ft_strncmp(line, "C", j))
	{
		if (set_colors(&cub->ceiling, line + i) == -1)
			return (-1);
	}
	else
		return (ft_putendl_fd("ERROR", 2), -1);
	return (0);
}
