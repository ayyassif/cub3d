/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:24:48 by ayyassif          #+#    #+#             */
/*   Updated: 2024/09/18 09:52:54 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	textures(t_cub *cub, int side, t_vec ray)
{
	if (side == 0 && ray.x > 0)
		cub->line_color = create_rgb(255, 50, 150); // EAST
	else if (side == 0)
		cub->line_color = create_rgb(100, 200, 100); // WEST
	else if (ray.y > 0)
		cub->line_color = create_rgb(50, 50, 200); // SOUTH
	else
		cub->line_color = create_rgb(255, 200, 100); // NORTH
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

static double	ray_dda(t_cub *cub, t_vec delta_dist, t_vec map_cords, t_vec ray)
{
	int		side;
	t_vec	side_dist;
	t_vec	step;

	side_dist = side_dist_setter(ray, &map_cords, delta_dist, &step);
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_cords.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_cords.y += step.y;
			side = 1;
		}
		if (cub->map[(int)map_cords.y][(int)map_cords.x].value == M_WALL)
			break ;
	}
	if (side)
		return (textures(cub, side, ray), side_dist.y - delta_dist.y);
	return (textures(cub, side, ray), side_dist.x - delta_dist.x);
}

static double	ray_distance(t_cub *cub, t_vec ray)
{
	t_vec	map_cords;
	t_vec	delta_dist;

	map_cords.x = cub->pos.x / cub->tile_size;
	map_cords.y = cub->pos.y / cub->tile_size;
	if (ray.x)
		delta_dist.x = fabs(1 / ray.x);
	else
		delta_dist.x = INFINITY;
	if (ray.y)
		delta_dist.y = fabs(1 / ray.y);
	else
		delta_dist.y = INFINITY;
	return (ray_dda(cub, delta_dist, map_cords, ray));
}

void	ray_casting(t_cub *cub, double perp_wall_dist)
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
		perp_wall_dist = ray_distance(cub, ray);
		lineHeight = (int)(HEIGHT / perp_wall_dist);
		drawStart = (HEIGHT - lineHeight) / 2;
		if( drawStart < 0)
			drawStart = 0;
		drawEnd = drawStart + lineHeight;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		ver_line(cub, drawStart, drawEnd, x);
	}
}
