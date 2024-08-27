/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:43:13 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/27 14:07:12 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "pars/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef enum e_type
{
	E_EMPTY,
	E_BLOCK,
	E_PLAYER
}	t_type;

typedef enum e_id
{
	E_NO,
	E_SO,
	E_WE,
	E_EA
}	t_id;


typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}		t_color;

// typedef struct s_floor
// {
// 	t_color	*color;
// }			t_floor;

// typedef struct s_ceiling
// {
// 	t_color	*color;
// }			t_ceiling;

typedef struct s_texture
{
	t_id	identifier;
	char	*path;
}			t_texture;

typedef struct s_map
{
	t_type	value;
}		t_map;

typedef struct s_cub
{
	t_texture	texture[4];
	t_color		floor;
	t_color		ceiling;
	t_map		**map;
}				t_cub;

void	ft_putendl_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	is_white_space(char c);
int	ft_pars(t_cub *cub, char *name_file);
char	*ft_strtrim(char *s1);
int	ft_atoi(char *str);
int	set_floor_ceiling(t_cub *cub, char *line);
int	set_texture(t_texture *texture, char *line);






void ft_write_cub(t_cub *cub);

#endif