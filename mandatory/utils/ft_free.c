/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:24:48 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/17 11:01:13 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_texture(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4 && cub->texture[i].path)
	{
		if (cub->texture[i].path)
			free(cub->texture[i].path);
		if (cub->texture[i].tex_png)
			mlx_delete_texture(cub->texture[i].tex_png);
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

static void	free_map(t_cub *cub)
{
	size_t	i;

	i = 0;
	if (!cub->map)
		return ;
	while (i < cub->height && cub->map[i])
		i++;
	while (i-- > 0)
	{
		if (cub->map[i])
			free(cub->map[i]);
	}
	free(cub->map);
}

void	free_cub(t_cub *cub)
{
	int	i;

	free_texture(cub);
	free_map(cub);
	close(cub->fd);
	i = 2;
	while (++i < OPEN_MAX)
		close (i);
}
