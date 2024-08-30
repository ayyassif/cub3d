/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:44:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/30 10:55:24 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void f() {
	system("leaks cub3D");
}
int	main(int ac, char **av)
{
	t_cub	cub;
//atexit(f);
	if (ac != 2 || check_file_name(av[1]))
		return (ft_putendl_fd("ERROR", 2), -1);
	if (ft_pars(&cub, av[1]) == -1)
		return (close(cub.fd), -1);
	ft_write_cub(&cub);
	free_cub(&cub);
	close(cub.fd);
	return (0);
}
