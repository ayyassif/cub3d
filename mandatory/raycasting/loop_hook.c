/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:05:44 by ayyassif          #+#    #+#             */
/*   Updated: 2024/09/14 16:39:57 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_s_map(t_cub *cub)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < cub->height)
	{
		x = 0;
		while (x < cub->width)
		{
			draw_square(cub, x * cub->tile_size,
				y * cub->tile_size, create_rgb(0, 0, 0));
			if (cub->map[y][x].value == M_WALL)
				draw_square(cub, x * cub->tile_size,
					y * cub->tile_size, create_rgb(100, 150, 100));
			x++;
		}
		y++;
	}
}

static int	ft_intlen(int n)
{
	int				len;
	unsigned int	nb;

	nb = n;
	len = 0;
	if (n < 0)
	{
		nb = -n;
		len++;
	}
	if (!nb)
		return (1);
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	nb;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	nb = n;
	if (n < 0)
		nb = -n;
	while (len--)
	{
		str[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

static void	wall_coll(t_cub *cub, t_vec new_pos, t_vec map_cords)
{
	t_vec	d;
	t_vec	inc;
	double	step;
	int		i;

	d.x = (new_pos.x - cub->pos.x) / (double)cub->tile_size;
	d.y = (new_pos.y - cub->pos.y) / (double)cub->tile_size;
	step = fmax(fabs(d.x), fabs(d.y));
	inc.x = (d.x / step) / (double)cub->tile_size;		
	inc.y = (d.y / step) / (double)cub->tile_size;
	d.x = new_pos.x / (double)cub->tile_size;
	d.y = new_pos.y / (double)cub->tile_size;
	i = -1;
	while (++i < step)
	{
		if (cub->map[(int)d.y][(int)map_cords.x].value != M_WALL)
			d.y += inc.y;
		if (cub->map[(int)map_cords.y][(int)d.x].value != M_WALL)
			d.x += inc.x;
	}
	if (cub->map[(int)d.y][(int)map_cords.x].value != M_WALL)
		cub->pos.y = new_pos.y;
	if (cub->map[(int)map_cords.y][(int)d.x].value != M_WALL)
		cub->pos.x = new_pos.x;
}

static void	move_process(t_cub *cub, t_vec *velo)
{
	t_vec	new_pos;
	double	move_speed;
	double	perp_wall_dist;
	t_vec	map_cords;

	map_cords.x = cub->pos.x / cub->tile_size;
	map_cords.y = cub->pos.y / cub->tile_size;
	if (velo)
	{
		move_speed = SPEED * cub->s_map.mlx_s_map->delta_time;
		new_pos.x = cub->pos.x + velo->x * move_speed;
		new_pos.y = cub->pos.y + velo->y * move_speed;
		wall_coll(cub, new_pos, map_cords);
	}
	mlx_delete_image(cub->s_map.mlx_s_map, cub->s_map.img_s_map);
	cub->s_map.img_s_map = mlx_new_image(cub->s_map.mlx_s_map, WIDTH, HEIGHT);
	perp_wall_dist = 0;
	ray_casting(cub, perp_wall_dist);
	draw_s_map(cub);
	player_square_draw(cub);
	dda(cub->pos ,cub->direction, cub, create_rgb(0, 255, 0));
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
}

static t_vec	vec_rotation(t_vec vec, double theta)
{
	t_vec	prime_vec;
	
	theta = theta * (M_PI / 180);
	prime_vec.x = vec.x * (double)cosf(theta) - vec.y * (double)sinf(theta);
	prime_vec.y = vec.x * (double)sinf(theta) + vec.y * (double)cosf(theta);
	return (prime_vec);
}

void	loop_hook(void *v_cub)
{
	t_cub	*cub;
	t_vec	velocity;
	int		theta;

	cub = (t_cub *)v_cub;
	if (cub->pressed_down.turn_left_right)
	{
		cub->direction = vec_rotation(cub->direction,
			cub->pressed_down.turn_left_right * ROT_ANG);
		cub->cam_plane = vec_rotation(cub->cam_plane,
			cub->pressed_down.turn_left_right * ROT_ANG);
	}
	theta = cub->pressed_down.left_right * 90;
	if (cub->pressed_down.frwd_bckwd && cub->pressed_down.left_right)
		theta = theta + cub->pressed_down.frwd_bckwd * theta / 2;
	else if (cub->pressed_down.frwd_bckwd == 1)
		theta = 180;
	velocity = vec_rotation(cub->direction, theta);
	if (cub->pressed_down.frwd_bckwd != -1 && theta == 0)
		move_process(cub, NULL);
	else
		move_process(cub, &velocity);
}