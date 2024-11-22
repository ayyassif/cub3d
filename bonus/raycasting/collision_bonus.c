/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:10:19 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/22 11:29:20 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	steps_and_door(t_cub *cub, t_vec *m_crds, t_vec step, int *setted)
{
	if (cub->side_dist.x < cub->side_dist.y)
	{
		cub->side_dist.x += cub->delta_dist.x;
		m_crds->x += step.x;
		cub->side = 0;
	}
	else
	{
		cub->side_dist.y += cub->delta_dist.y;
		m_crds->y += step.y;
		cub->side = 1;
	}
	if (!(*setted) && cub->ray.x == cub->direction.x
		&& cub->ray.y == cub->direction.y
		&& cub->map[(int)m_crds->y][(int)m_crds->x] != M_FLOOR)
	{
		if ((cub->map[(int)m_crds->y][(int)m_crds->x] == M_DOOR_CLOSED
			|| cub->map[(int)m_crds->y][(int)m_crds->x] == M_DOOR_OPEN))
			cub->focused = *m_crds;
		else
			cub->focused.x = -1;
		*setted = 1;
	}
}

void	wall_coll(t_cub *cub, t_vec new_pos, t_vec map_cords)
{
	t_vec	d;
	t_vec	inc;
	double	step;
	int		i;

	d.x = (new_pos.x - cub->pos.x) / (double)TILE_SIZE;
	d.y = (new_pos.y - cub->pos.y) / (double)TILE_SIZE;
	step = fmax(fabs(d.x), fabs(d.y));
	inc.x = (d.x / step) / (double)TILE_SIZE;
	inc.y = (d.y / step) / (double)TILE_SIZE;
	d.x = new_pos.x / (double)TILE_SIZE;
	d.y = new_pos.y / (double)TILE_SIZE;
	i = -1;
	while (++i < step)
	{
		if (!is_collision(cub->map[(int)d.y][(int)map_cords.x]))
			d.y += inc.y;
		if (!is_collision(cub->map[(int)map_cords.y][(int)d.x]))
			d.x += inc.x;
	}
	if (!is_collision(cub->map[(int)d.y][(int)map_cords.x]))
		cub->pos.y = new_pos.y;
	if (!is_collision(cub->map[(int)map_cords.y][(int)d.x]))
		cub->pos.x = new_pos.x;
}
