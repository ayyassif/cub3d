/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:51:32 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/27 13:58:10 by hakaraou         ###   ########.fr       */
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
	if (i < 5 && set_texture(&cub->texture[i - 1], line) == -1)
		return (-1);
	if (i > 4 && i < 7 && set_floor_ceiling(cub, line) == -1)
		return (-1);
	return (0);
}

static int	creat_cub(t_cub *cub, char *name_file)
{
	char	*line_maps_file;
	int		fd;
	int		i;

	fd = -1;
	line_maps_file = NULL;
	fd = open(name_file, O_RDONLY, 0400);
	if (fd == -1)
		return (ft_putendl_fd("error: open", 2), -1);
	i = 0;
	while (++i)
	{
		free(line_maps_file);
		line_maps_file = get_next_line(fd);
		if (!line_maps_file)
			break ;
		if (is_line_space(line_maps_file))
			continue ;
		line_maps_file = ft_strtrim(line_maps_file);
		if (!line_maps_file)
			return (ft_putendl_fd("error: malloc", 2), -1);
		if (i < 7 && set_param(cub, line_maps_file, i) == -1)
			return (free(line_maps_file), -1);
	}
	return (0);
}

int	ft_pars(t_cub *cub, char *name_file)
{
	if (creat_cub(cub, name_file) == -1)
		return (-1);
	return (0);
}
