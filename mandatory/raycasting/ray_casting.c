/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:24:48 by ayyassif          #+#    #+#             */
/*   Updated: 2024/09/22 19:50:21 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	textures(t_cub *cub, t_vec ray)
{
	if (cub->side == 0 && ray.x > 0)
		cub->texture_id = 0;
	else if (cub->side == 0)
		cub->texture_id = 1;
	else if (ray.y > 0)
		cub->texture_id = 2;
	else
		cub->texture_id = 3;
}

static t_vec	side_dist_setter(t_vec ray, t_vec *map_cords, t_vec delta_dist, t_vec *step)
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

static void	ray_dda(t_cub *cub, t_vec map_cords, t_vec ray)
{
	t_vec	step;

	cub->side_dist = side_dist_setter(ray, &map_cords, cub->delta_dist, &step);
	while (1)
	{
		if (cub->side_dist.x < cub->side_dist.y)
		{
			cub->side_dist.x += cub->delta_dist.x;
			map_cords.x += step.x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist.y += cub->delta_dist.y;
			map_cords.y += step.y;
			cub->side = 1;
		}
		if (cub->map[(int)map_cords.y][(int)map_cords.x].value == M_WALL)
			break ;
	}
}

static void	ray_dda_1(t_cub *cub, t_vec *ray)
{
	if (cub->side)	
	{
		cub->perp_wall_dist = cub->side_dist.y - cub->delta_dist.y;
		cub->tex_pos_x = cub->pos.x / cub->tile_size + ray->x * cub->perp_wall_dist;
		cub->tex_pos_x -= floor(cub->tex_pos_x);
		// printf("vert %f %f %f %f %f\n", cub->pos.x, cub->perp_wall_dist, cub->tex_pos_x, ray->x, ray->y);
	}
	else
	{
		cub->perp_wall_dist = cub->side_dist.x - cub->delta_dist.x;
		cub->tex_pos_x = cub->pos.y / cub->tile_size + ray->y * cub->perp_wall_dist;
		cub->tex_pos_x -= floor(cub->tex_pos_x);
		// printf("hori %f %f %f %f %f\n", cub->pos.y, cub->perp_wall_dist, cub->tex_pos_x, ray->x, ray->y);
	}
}

static void	ray_distance(t_cub *cub, t_vec ray)
{
	t_vec	map_cords;

	map_cords.x = cub->pos.x / cub->tile_size;
	map_cords.y = cub->pos.y / cub->tile_size;
	if (ray.x)
		cub->delta_dist.x = fabs(1 / ray.x);
	else
		cub->delta_dist.x = INFINITY;
	if (ray.y)
		cub->delta_dist.y = fabs(1 / ray.y);
	else
		cub->delta_dist.y = INFINITY;
	ray_dda(cub, map_cords, ray);
	ray_dda_1(cub, &ray);
	textures(cub, ray);
}

void	ray_casting(t_cub *cub)
{
	double	camera_x;
	t_vec	ray;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray.x = (cub->direction.x + cub->cam_plane.x * camera_x);
		ray.y = (cub->direction.y + cub->cam_plane.y * camera_x);
		ray_distance(cub, ray);
		lineHeight = (int)(HEIGHT / cub->perp_wall_dist);
		drawStart = (HEIGHT - lineHeight) / 2;
		drawEnd = (HEIGHT + lineHeight) / 2;	
		ver_line(cub, drawStart, drawEnd, x);
	}
}
