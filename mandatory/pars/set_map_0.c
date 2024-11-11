/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:58:40 by hakaraou          #+#    #+#             */
/*   Updated: 2024/11/11 13:18:10 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_line_map	*find_l_node(t_line_map *last)
{
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	set_line_map(t_line_map **line_map, char *line)
{
	t_line_map	*node;
	t_line_map	*l_node;

	if (!line_map || !line)
		return (1);
	node = malloc(sizeof(t_line_map));
	if (!node)
		return (ft_putendl_fd("error: malloc", 2), -1);
	node->next = NULL;
	node->line_map = ft_strdup(line);
	if (!node->line_map)
		return (1);
	if (!(*line_map))
		*line_map = node;
	else
	{
		l_node = find_l_node(*line_map);
		l_node->next = node;
	}
	return (0);
}

int	ft_ofset_front(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_white_space(line[i]))
		i++;
	return (i);
}

void	set_cub(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		cub->texture[i].path = NULL;
		cub->texture[i].tex_png = NULL;
	}
	cub->height = 0;
	cub->width = 0;
	cub->ofset_front = 0;
	cub->ofset_back = 0;
	cub->line_map = NULL;
	cub->floor.red = -1;
	cub->floor.blue = -1;
	cub->floor.green = -1;
	cub->ceiling.red = -1;
	cub->ceiling.blue = -1;
	cub->ceiling.green = -1;
	cub->map = NULL;
	cub->endl = 0;
	cub->pressed_down.frwd_bckwd = 0;
	cub->pressed_down.left_right = 0;
	cub->pressed_down.turn_left_right = 0;
	cub->tex_id = 0;
	cub->sword = ft_strdup("mandatory/textures/sword walking/sword00.png");
	if (!cub->sword)
		return ; //return ERROR!!!!
}
