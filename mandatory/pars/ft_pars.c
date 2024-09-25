/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:51:32 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/25 16:13:55 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_line_space(char *line, int i, t_cub *cub)
{
	int	j;

	j = -1;
	while (is_white_space(line[++j]))
		;
	if (line[j])
		return (0);
	if (i > 7)
		cub->endl = 1;
	return (1);
}

static char	*ft_strtrim_line(char *line, int i)
{
	if (i < 7)
		return (ft_strtrim(line));
	if (i >= 7)
		return (ft_back_strtrim(line));
	return (NULL);
}

static int	creat_cub_1(t_cub *cub)
{
	char	*line_map_file;
	int		i;

	i = 1;
	line_map_file = NULL;
	while (1)
	{
		free(line_map_file);
		line_map_file = get_next_line(cub->fd);
		if (!line_map_file)
			break ;
		if (is_line_space(line_map_file, i, cub))
			continue ;
		line_map_file = ft_strtrim_line(line_map_file, i);
		if (!line_map_file)
			return (ft_putendl_fd("error: malloc", 2), -1);
		if (i == 7)
			cub->ofset_front = ft_ofset_front(line_map_file);
		if (i > 7 && !is_line_space(line_map_file, i, cub) && cub->endl == 1)
			return (free_texture(cub), ft_putendl_fd("ERROR:\n\tmore lines", 2),
				free(line_map_file), -1);
		if (set_param(cub, line_map_file, i++) == -1)
			return (free_texture(cub), free(line_map_file), -1);
	}
	return (cub->height = i - 7, 0);
}

static int	creat_cub_0(t_cub *cub, char *name_file)
{
	cub->fd = open(name_file, O_RDONLY, 0400);
	if (cub->fd == -1)
		return (ft_putendl_fd("error: open", 2), -1);
	return (creat_cub_1(cub));
}

int	ft_pars(t_cub *cub, char *name_file)
{
	set_cub(cub);
	cub->direction.x = 0;
	cub->direction.y = 0;
	cub->cam_plane.x = 0;
	cub->cam_plane.y = 0;
	if (creat_cub_0(cub, name_file) == -1)
		return (free_line_map(&cub->line_map), -1);
	cub->width = cub->ofset_back - cub->ofset_front + 1;
	if (cub->height == 0)
		return (free_line_map(&cub->line_map),
			ft_putendl_fd("ERROR:\n\tmessing map", 2), -1);
	if (creat_map(cub) == -1)
		return (free_line_map(&cub->line_map), -1);
	free_line_map(&cub->line_map);
	if (pars_map(cub) == -1)
		return (free_cub(cub), -1);
	return (0);
}
