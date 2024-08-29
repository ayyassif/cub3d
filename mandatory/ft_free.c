/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:24:48 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/28 16:20:08 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4 && cub->texture[i].path)
	{
		if (cub->texture[i].path)
			free(cub->texture[i].path);
	}
}

void	free_line_map(t_line_map **line_map)
{
	t_line_map	*tmp;

	while (line_map && *line_map)
	{
		tmp = (*line_map)->next;
		if ((*line_map)->line_map)
		{
			free((*line_map)->line_map);
			(*line_map)->line_map = NULL;
		}
		free(*line_map);
		*line_map = NULL;
		(*line_map) = tmp;
	}
}

void	free_map(t_map **map, t_cub *cub)
{
	size_t	i = 0;
	i = cub->height;
	while (i-- > 0)
		free(map[i]);
	free(map);
}

void	free_cub(t_cub *cub)
{
	free_texture(cub);
	free_map(cub->map, cub);
}
