/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:01:01 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/02 16:53:42 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_type	set_type_block_1(char c, t_cub *cub)
{
	if (c == ' ')
		return (E_VOID);
	if (c == '0')
		return (E_EMPTY);
	if (c == '1')
		return (E_BLOCK);
	if (c == 'W')
		return (cub->player_dir = M_PI, E_PLAYER_W);
	if (c == 'S')
		return (cub->player_dir = (M_PI * 0.5),E_PLAYER_S);
	if (c == 'E')
		return (cub->player_dir = 0, E_PLAYER_E);
	if (c == 'N')
		return (cub->player_dir = (M_PI * 1.5), E_PLAYER_N);
	else
		return (9);
}

static t_type	set_type_block_0(char c, t_cub *cub)
{
	if (c != '\n')
		return (set_type_block_1(c, cub));
	return (set_type_block_1(' ', cub));
}

static int	put_map(t_cub *cub)
{
	size_t		i;
	size_t		j;
	size_t		k;
	t_line_map	*tmp;

	tmp = cub->line_map;
	j = 0;
	while (tmp && j < cub->height)
	{
		i = cub->ofset_front;
		k = -1;
		while (tmp->line_map[i] && ++k < cub->width)
		{
			cub->map[j][k].value = set_type_block_0(tmp->line_map[i], cub);
			if (cub->map[j][k].value == 9)
				return (-1);
			i++;
		}
		while (++k < cub->width)
			cub->map[j][k].value = set_type_block_1(' ', cub);
		j++;
		tmp = tmp->next;
	}
	return (0);
}

int	creat_map(t_cub *cub)
{
	size_t	i;

	i = 0;
	cub->map = malloc(sizeof(t_map *) * cub->height);
	if (!cub->map)
		return (free_texture(cub), ft_putendl_fd("error: malloc", 2), -1);
	while (i < cub->height)
	{
		cub->map[i] = malloc(sizeof(t_map) * cub->width);
		if (!cub->map[i])
			return (free_cub(cub), ft_putendl_fd("error: malloc", 2), -1);
		i++;
	}
	if (put_map(cub) == -1)
		return (free_cub(cub), ft_putendl_fd("ERROR", 2), -1);
	return (0);
}
