/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/29 13:24:20 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void f(){
	system("leaks cub3D");
}
int	main(int ac, char **av)
{
	t_cub	cub;
// atexit(f);
	// void *ptr = mlx_init(20, 20, "hihi", false);
	// (void)ptr;
	if (ac != 2)
		return (ft_putendl_fd("ERROR", 2), -1);
	if (ft_pars(&cub, av[1]) == -1)
		return (close(cub.fd), -1);
	ft_write_cub(&cub);
	free_cub(&cub);
	close(cub.fd);
	return (0);
}
