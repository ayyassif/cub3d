/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:24:48 by ayyassif          #+#    #+#             */
/*   Updated: 2024/11/04 14:18:06 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_vec	side_dist_setter(t_vec ray, t_vec *map_cords,
								t_vec delta_dist, t_vec *step)
{
	t_vec	side_dist;

	if (ray.x < 0)
	{
		step->x = -1;
		side_dist.x = (map_cords->x - (int)map_cords->x) * delta_dist.x;
	}
	else
	{
		step->x = 1;
		side_dist.x = ((int)map_cords->x + 1 - map_cords->x) * delta_dist.x;
	}
	if (ray.y < 0)
	{
		step->y = -1;
		side_dist.y = (map_cords->y - (int)map_cords->y) * delta_dist.y;
	}
	else
	{
		step->y = 1;
		side_dist.y = ((int)map_cords->y + 1 - map_cords->y) * delta_dist.y;
	}
	map_cords->x = (int)map_cords->x;
	map_cords->y = (int)map_cords->y;
	return (side_dist);
}

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
		&& cub->map[(int)m_crds->y][(int)m_crds->x].value != M_FLOOR)
	{
		if ((cub->map[(int)m_crds->y][(int)m_crds->x].value == M_DOOR_CLOSED
			|| cub->map[(int)m_crds->y][(int)m_crds->x].value == M_DOOR_OPEN))
			cub->focused = *m_crds;
		else
			cub->focused.x = -1;
		*setted = 1;
	}
}

static int	ray_dda(t_cub *cub, t_vec m_crds)
{
	t_vec	step;
	int		setted;
	size_t	i;

	setted = 0;
	cub->side_dist = side_dist_setter(cub->ray, &m_crds,
			cub->delta_dist, &step);
	i = 0;
	while (++i)
	{
		steps_and_door(cub, &m_crds, step, &setted);
		if (cub->map[(int)m_crds.y][(int)m_crds.x].value == M_WALL)
			return (1);
		if (cub->map[(int)m_crds.y][(int)m_crds.x].value == M_DOOR_CLOSED)
			return (2);
	}
	return (0);
}

static void	ray_dda_1(t_cub *cub)
{
	if (cub->side)
	{
		cub->perp_wall_dist = cub->side_dist.y - cub->delta_dist.y;
		cub->tex_pos_x = cub->pos.x / TILE_SIZE;
		cub->tex_pos_x += cub->ray.x * cub->perp_wall_dist;
	}
	else
	{
		cub->perp_wall_dist = cub->side_dist.x - cub->delta_dist.x;
		cub->tex_pos_x = cub->pos.y / TILE_SIZE;
		cub->tex_pos_x += cub->ray.y * cub->perp_wall_dist;
	}
	cub->tex_pos_x -= floor(cub->tex_pos_x);
}

static void	ray_distance(t_cub *cub)
{
	t_vec	map_cords;
	int		type_tex;

	map_cords.x = cub->pos.x / TILE_SIZE;
	map_cords.y = cub->pos.y / TILE_SIZE;
	if (cub->ray.x)
		cub->delta_dist.x = fabs(1 / cub->ray.x);
	else
		cub->delta_dist.x = INFINITY;
	if (cub->ray.y)
		cub->delta_dist.y = fabs(1 / cub->ray.y);
	else
		cub->delta_dist.y = INFINITY;
	type_tex = ray_dda(cub, map_cords);
	ray_dda_1(cub);
	textures(cub, type_tex);
}

void	ray_casting(t_cub *cub)
{
	double	camera_x;
	int		lineheight;
	int		drawstart;
	int		drawend;

	cub->x = -1;
	while (++cub->x < WIDTH)
	{
		camera_x = 2 * cub->x / (double)WIDTH - 1;
		cub->ray.x = (cub->direction.x + cub->cam_plane.x * camera_x);
		cub->ray.y = (cub->direction.y + cub->cam_plane.y * camera_x);
		ray_distance(cub);
		lineheight = (int)(HEIGHT / cub->perp_wall_dist);
		drawstart = (HEIGHT - lineheight) / 2;
		drawend = (HEIGHT + lineheight) / 2;
		ver_line(cub, drawstart, drawend);
	}
}
