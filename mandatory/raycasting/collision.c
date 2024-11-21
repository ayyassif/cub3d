/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:10:19 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/21 12:46:31 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
