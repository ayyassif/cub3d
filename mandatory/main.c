/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/15 12:46:24 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void f() {
	system("leaks cub3D");
	system("lsof -c cub3D");
}

int	main(int ac, char **av)
{
	t_cub	cub;
atexit(f);
	if (ac != 2 || check_file_name(av[1]))
		return (ft_putendl_fd("ERROR:\n\tinvalid parametre", 2), -1);
	if (ft_pars(&cub, av[1]) == -1)
		return (close(cub.fd), -1);
	close(cub.fd);
	if (execution(&cub) == -1)
		return (free_cub(&cub), -1);
	// ft_write_cub(&cub);	
	free_cub(&cub);
	int i = 2;
	while (++i < OPEN_MAX)
		close (i);// leaks fd 9adithom bhad l3iba
	mlx_delete_image(cub.s_map.mlx_s_map, cub.s_map.img_s_map);
	return (0);
}
