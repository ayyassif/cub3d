/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:01:01 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/16 18:31:51 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static t_type	set_type_map_1(char c, t_cub *cub)
{
	if (c == ' ')
		return (M_VOID);
	else if (c == '0')
		return (M_FLOOR);
	else if (c == '1')
		return (M_WALL);
	else if (c == 'D')
		return (M_DOOR_CLOSED);
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
			cub->map[j][k] = set_type_map_0(tmp->line_map[i++], cub);
			pos_player(cub, cub->map[j][k], k, j);
			if (cub->map[j][k] == M_ERROR)
				return (-1);
		}
		while (++k < cub->width)
			cub->map[j][k] = set_type_map_1(' ', cub);
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
		return (ft_putendl_fd("error: malloc", 2), -1);
	while (i < cub->height)
	{
		cub->map[i] = malloc(sizeof(t_map) * cub->width);
		if (!cub->map[i])
			return (ft_putendl_fd("error: malloc", 2), -1);
		i++;
	}
	if (put_map(cub) == -1)
		return (ft_putendl_fd("ERROR:\n\tmap error", 2), -1);
	return (0);
}
