/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:58:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/10/01 11:08:27 by hakaraou         ###   ########.fr       */
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

static int	set_texture(t_texture *texture, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	texture->identifier = dir_picker(line);
	line += (i + 2);
	while (line[i] && is_white_space(line[i]))
		i++;
	if (!i)
		return (ft_putendl_fd("ERROR:\n\tmissing textures", 2), -1);
	while (line[i + j])
		j++;
	texture->path = ft_substr(line, i, j);
	if (!texture->path)
		return (ft_putendl_fd("error: malloc", 2), -1);
	return (0);
}

static int	set_colors(t_color *color, char *line)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		while (*line && is_white_space(*line))
			line++;
		if (i == 0)
			color->red = ft_atoi(line);
		else if (i == 1)
			color->green = ft_atoi(line);
		else if (i == 2)
			color->blue = ft_atoi(line);
		if (*line && (*line == '-' || *line == '+'))
			line++;
		if (*line && (*line < '0' || *line > '9'))
			return (-1);
		while (*line && *line >= '0' && *line <= '9')
			line++;
		while (*line && is_white_space(*line))
			line++;
		while (*line && *line == ',' && i != 2)
			line++;
	}
	return (*line * -1);
}

static int	set_texture_color(t_cub *cub, char *line)
{
	int		j;

	j = 0;
	while (line[j] && !is_white_space(line[j]))
		j++;
	if (!ft_strncmp(line, "NO", j) || !ft_strncmp(line, "SO", j)
		|| !ft_strncmp(line, "WE", j) || !ft_strncmp(line, "EA", j))
	{
		if (cub->tex_id == 4)
			return (ft_putendl_fd("ERROR:\n\tduplicates textures", 2), -1);
		if (set_texture(&cub->texture[cub->tex_id++], line) == -1)
			return (-1);
	}
	else if (!ft_strncmp(line, "F", j))
	{
		if (set_colors(&cub->floor, line + j) < 0)
			return (ft_putendl_fd("ERROR:\n\tfloor color invalid", 2), -1);
	}
	else if (!ft_strncmp(line, "C", j))
	{
		if (set_colors(&cub->ceiling, line + j) < 0)
			return (ft_putendl_fd("ERROR:\n\tcelling color invalid", 2), -1);
	}
	return (0);
}

int	set_door_coin(t_cub *cub)
{
	cub->texture[4].tex_png = mlx_load_png("mandatory/textures/door2.png");
	if (!cub->texture[4].tex_png)
		return (-1);
	cub->texture[4].identifier = E_DR;
	cub->texture[4].path = NULL;
	cub->texture[5].tex_png = mlx_load_png("mandatory/textures/door1.png");
	if (!cub->texture[5].tex_png)
		return (-1);
	cub->texture[5].identifier = E_CN;
	cub->texture[5].path = NULL;
	return (0);	
}

int	set_param(t_cub *cub, char *line, int i)
{
	size_t	len;

	if (set_texture_color(cub, line) == -1)
		return (-1);
	if (i == 6 && (check_colors(&cub->floor, &cub->ceiling) == -1
			|| check_texture(cub->texture) == -1))
		return (-1);
	if (i > 6)
	{
		len = ft_ofset_front(line);
		if (cub->ofset_front > len)
			cub->ofset_front = len;
		len = ft_strlen(line) - 1;
		if (cub->ofset_back < len)
			cub->ofset_back = len;
		if (set_line_map(&cub->line_map, line) == -1)
			return (-1);
	}
	if (set_door_coin(cub) == -1)
		return (-1);
	return (0);
}
