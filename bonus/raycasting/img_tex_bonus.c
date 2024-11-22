/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_tex_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:24:27 by ayyassif          #+#    #+#             */
/*   Updated: 2024/11/22 11:26:44 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	map_square(t_cub *cub, t_vec tmp, t_vec	start)
{
	int		color;

	color = 0xff000000;
	if (cub->map[(int)tmp.y][(int)tmp.x] == M_FLOOR)
		color = create_rgb(cub->floor.red,
				cub->floor.green, cub->floor.blue);
	else if (cub->map[(int)tmp.y][(int)tmp.x] == M_WALL)
		color = create_rgb(100, 150, 100);
	else if (cub->map[(int)tmp.y][(int)tmp.x] == M_DOOR_CLOSED)
		color = create_rgb(200, 50, 50);
	else if (cub->map[(int)tmp.y][(int)tmp.x] == M_DOOR_OPEN)
		color = create_rgb(150, 25, 25);
	else
		return ;
	draw_square(cub, ((int)tmp.x - start.x + 1) * TILE_SIZE,
		((int)tmp.y - start.y + 1) * TILE_SIZE, color);
}

void	draw_s_map(t_cub *cub)
{
	t_vec	start;
	t_vec	end;
	t_vec	tmp;

	start.x = cub->pos.x / TILE_SIZE - M_MAP;
	start.y = cub->pos.y / TILE_SIZE - M_MAP;
	end.x = cub->pos.x / TILE_SIZE + M_MAP;
	end.y = cub->pos.y / TILE_SIZE + M_MAP;
	tmp.y = start.y;
	while (tmp.y < end.y)
	{
		tmp.x = start.x;
		while (tmp.x < end.x)
		{
			if (tmp.y >= 0 && tmp.y <= cub->height
				&& tmp.x >= 0 && tmp.x <= cub->width)
				map_square(cub, tmp, start);
			tmp.x++;
		}
		tmp.y++;
	}
	player_square_draw(cub);
}

static void	tx_loop(t_cub *cub, t_vec size, t_vec start, mlx_texture_t *texture)
{
	int		y;
	int		x;
	int		index;
	double	t_y;
	double	t_x;

	y = -1;
	while (++y < size.y)
	{
		x = -1;
		t_y = y / (double)size.y;
		t_y *= texture->height;
		while (++x < size.x)
		{
			t_x = x / (double)size.x;
			t_x *= texture->width;
			index = ((int)t_y * texture->width + (int)t_x) * 4;
			if (texture->pixels[index + 4] != 0)
				ft_put_pixel(cub->mlx.img, x + start.x, y + start.y,
					color_from_pixel(texture, index));
		}
	}
	mlx_delete_texture(texture);
}

int	draw_image(t_cub *cub, t_tx_img tx_img, mlx_texture_t *texture)
{
	t_vec	start;
	t_vec	size;

	if (!texture)
		return (-1);
	start.x = 0;
	start.y = 0;
	size.y = HEIGHT;
	size.x = WIDTH;
	if (tx_img == TX_MAP)
	{
		size.y = (M_MAP * 2 + 1) * TILE_SIZE;
		size.x = size.y;
	}
	else if (tx_img == TX_ITEM)
	{
		size.y = texture->height - 1;
		size.x = texture->width - 1;
		start.x = WIDTH - size.x;
		start.y = HEIGHT - size.y;
	}
	tx_loop(cub, size, start, texture);
	return (0);
}

int	animat_items(t_cub *cub)
{
	static int		counter;
	static double	timer;

	timer += cub->mlx.mlx_handle->delta_time;
	if ((timer >= 0.16 && (cub->pressed_down.frwd_bckwd
				|| cub->pressed_down.left_right)) || timer >= 0.5)
	{
		counter++;
		if (counter > 31)
			counter = 0;
		cub->sword[34] = counter / 10 + '0';
		cub->sword[35] = counter % 10 + '0';
		if (cub->pressed_down.frwd_bckwd || cub->pressed_down.left_right)
			timer -= 0.16;
		else
			timer -= 0.5;
	}
	if (draw_image(cub, TX_ITEM, mlx_load_png(cub->sword)))
		return (-1);
	return (0);
}
