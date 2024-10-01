/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/10/01 16:44:14 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void f() {
	system("leaks cub3D");
}
//-------------------------------
int	intro(t_cub *cub)
{
  	mlx_texture_t* texture = mlx_load_png("mandatory/textures/DON'T FORGET TO (1).png");
	if (!texture)
		exit(1);
	int	y = -1;
	while (++y < HEIGHT)
	{
		int	x = -1;
			double t_y = y / (double)HEIGHT;
			t_y *= texture->height;
		while (++x < WIDTH)
		{
			double t_x = x / (double)WIDTH;
			t_x *= texture->width;
			int index = ((int)t_y * texture->width + (int)t_x) * 4;
			ft_put_pixel(cub->s_map.img_s_map, x, y, color_from_pixel(texture, index));
		}
		
	}
	mlx_image_to_window(cub->s_map.mlx_s_map, cub->s_map.img_s_map, 0, 0);
	mlx_delete_texture(texture);
	return (0);
}
//-------------------------------

int	main(int ac, char **av)
{
	t_cub	cub;
//atexit(f);
	if (ac != 2 || check_file_name(av[1]))
		return (ft_putendl_fd("ERROR:\n\tinvalid parametre", 2), -1);
	if (ft_pars(&cub, av[1]) == -1)
		return (close(cub.fd), -1);
	close(cub.fd);
	if (execution(&cub) == -1)
		return (free_cub(&cub), -1);
	// ft_write_cub(&cub);	
	free_cub(&cub);
	mlx_delete_image(cub.s_map.mlx_s_map, cub.s_map.img_s_map);
	return (0);
}



//   mlx_delete_image(mlx, img);
//   mlx_delete_texture(texture);

//   mlx_terminate(mlx);
//   return (EXIT_SUCCESS);