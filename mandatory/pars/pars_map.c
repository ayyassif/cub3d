/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:53:32 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/29 18:55:15 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_empty(t_cub *cub, size_t ln, size_t col)
{
	if (ln == 0 || ln == cub->height - 1 || col == 0 || col == cub->width - 1)
		return (-1);
	if (cub->map[ln - 1][col].value == E_VOID)
		return (-1);
	if (cub->map[ln + 1][col].value == E_VOID)
		return (-1);
	if (cub->map[ln][col - 1].value == E_VOID)
		return (-1);
	if (cub->map[ln][col + 1].value == E_VOID)
		return (-1);
	return (0);
}

int	pars_map(t_cub *cub)
{
	size_t	ln;
	size_t	col;
	int		p;

	p = 0;
	ln = 0;
	while (ln < cub->height)
	{
		col = 0;
		while (col < cub->width)
		{
			if ((cub->map[ln][col].value == E_EMPTY
				|| is_player(cub->map[ln][col].value))
				&& check_empty(cub, ln, col) == -1)
				return (ft_putendl_fd("ERROR", 2), -1);
			if (is_player(cub->map[ln][col].value))
				p++;
			col++;
		}
		ln++;
	}
	if (p != 1)
		return (ft_putendl_fd("ERROR", 2), -1);
	return (0);
}
