/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:01:01 by hakaraou          #+#    #+#             */
/*   Updated: 2024/10/01 10:14:14 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_type	set_type_map_1(char c, t_cub *cub)
{
	if (c == ' ')
		return (M_VOID);
	else if (c == '0')
		return (M_FLOOR);
	else if (c == '1')
		return (M_WALL);
	else if (c == '2')
		return (M_DOOR);
	else if (c == '3')
		return (M_COIN);
	else if (c == 'W')
		return (cub->direction.x = -1, cub->cam_plane.y = -0.66, M_PLAYER);
	else if (c == 'S')
		return (cub->direction.y = 1, cub->cam_plane.x = -0.66, M_PLAYER);
	else if (c == 'E')
		return (cub->direction.x = 1, cub->cam_plane.y = 0.66, M_PLAYER);
	else if (c == 'N')
		return (cub->direction.y = -1, cub->cam_plane.x = 0.66, M_PLAYER);
	else
		return (M_ERROR);
}

static t_type	set_type_map_0(char c, t_cub *cub)
{
	if (c != '\n')
		return (set_type_map_1(c, cub));
	return (set_type_map_1(' ', cub));
}

static void	pos_player(t_cub *cub, t_type type, int x, int y)
{
	if (type == M_PLAYER)
	{
		cub->pos.x = (x + 0.5) * TILE_SIZE;
		cub->pos.y = (y + 0.5) * TILE_SIZE;
	}
}

static int	put_map(t_cub *cub)
{
	size_t		i;
	size_t		j;
	size_t		k;
	t_line_map	*tmp;

	tmp = cub->line_map;
	j = 0;
	while (tmp && j < cub->height)
	{
		i = cub->ofset_front;
		k = -1;
		while (tmp->line_map[i] && ++k < cub->width)
		{
			cub->map[j][k].value = set_type_map_0(tmp->line_map[i++], cub);
			pos_player(cub, cub->map[j][k].value, k, j);
			if (cub->map[j][k].value == M_ERROR)
				return (-1);
		}
		while (++k < cub->width)
			cub->map[j][k].value = set_type_map_1(' ', cub);
		j++;
		tmp = tmp->next;
	}
	return (0);
}

int	creat_map(t_cub *cub)
{
	size_t	i;

	i = 0;
	cub->map = malloc(sizeof(t_map *) * cub->height);
	if (!cub->map)
		return (free_texture(cub), ft_putendl_fd("error: malloc", 2), -1);
	while (i < cub->height)
	{
		cub->map[i] = malloc(sizeof(t_map) * cub->width);
		if (!cub->map[i])
			return (free_cub(cub), ft_putendl_fd("error: malloc", 2), -1);
		i++;
	}
	if (put_map(cub) == -1)
		return (free_cub(cub), ft_putendl_fd("ERROR:\n\tmap error", 2), -1);
	return (0);
}
