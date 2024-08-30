/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:51:32 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/30 11:41:11 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_line_space(char *line)
{
	int	i;

	i = -1;
	while (is_white_space(line[++i]))
		;
	if (line[i])
		return (0);
	return (1);
}

static int	set_param(t_cub *cub, char *line, int i)
{
	size_t	len;

	if (i < 5 && set_texture(&cub->texture[i - 1], line) == -1)
		return (-1);
	if (i == 5 && check_texture(cub->texture) == -1)
		return (free_texture(cub), -1);
	if (i > 4 && i < 7 && set_floor_ceiling(cub, line) == -1)
		return (-1);
	if (i == 6 && check_colors(&cub->floor, &cub->ceiling) == -1)
		return (free_texture(cub), ft_putendl_fd("ERROR", 2), -1);
	if (i > 6)
	{
		len = ft_ofset_front(line);
		if (cub->ofset_front > len)
			cub->ofset_front = len;
		len = ft_strlen(line) - 1;
		if (cub->ofset_back < len)
			cub->ofset_back = len;
		if (set_line_map(&cub->line_map, line) == -1)
			return (free_texture(cub), -1);
	}
	return (0);
}

static char	*ft_strtrim_line(char *line, int i)
{
	if (i < 7)
		return (ft_strtrim(line));
	if (i >= 7)
		return (ft_back_strtrim(line));
	return (NULL);
}

static int	creat_cub(t_cub *cub, char *name_file)
{
	char	*line_map_file;
	int		i;

	line_map_file = NULL;
	cub->fd = open(name_file, O_RDONLY, 0400);
	if (cub->fd == -1)
		return (ft_putendl_fd("error: open", 2), -1);
	i = 1;
	while (1)
	{
		free(line_map_file);
		line_map_file = get_next_line(cub->fd);
		if (!line_map_file)
			break ;
		if (is_line_space(line_map_file))
		{
			if (i > 7)
				cub->endl = 1;
			continue ;
		}
		line_map_file = ft_strtrim_line(line_map_file, i);
		if (!line_map_file)
			return (ft_putendl_fd("error: malloc", 2), -1);
		if (i == 7)
			cub->ofset_front = ft_ofset_front(line_map_file);
		if (i > 7 && !is_line_space(line_map_file) && cub->endl == 1)
			return (ft_putendl_fd("ERROR", 2), free(line_map_file), -1);
		if (set_param(cub, line_map_file, i++) == -1)
			return (free(line_map_file), -1);
	}
	return (cub->height = i - 7, 0);
}

int	ft_pars(t_cub *cub, char *name_file)
{
	cub->height = 0;
	cub->width = 0;
	cub->ofset_front = 0;
	cub->ofset_back = 0;
	cub->line_map = NULL;
	cub->floor.red = -1;
	cub->floor.blue = -1;
	cub->floor.green = -1;
	cub->ceiling.red = -1;
	cub->ceiling.blue = -1;
	cub->ceiling.green = -1;
	cub->map = NULL;
	cub->endl = 0;
	if (creat_cub(cub, name_file) == -1)
		return (free_line_map(&cub->line_map), -1);
	cub->width = cub->ofset_back - cub->ofset_front + 1;
	if (creat_map(cub) == -1)
		return (free_line_map(&cub->line_map), -1);
	free_line_map(&cub->line_map);
	if (pars_map(cub) == -1)
		return (free_cub(cub), -1);
	return (0);
}
