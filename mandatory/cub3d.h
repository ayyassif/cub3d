/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:43:13 by hakaraou          #+#    #+#             */
/*   Updated: 2024/08/30 11:40:36 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
// # include "../MLX42.h"

typedef enum e_type
{
	E_EMPTY,
	E_BLOCK,
	E_PLAYER_W,
	E_PLAYER_S,
	E_PLAYER_E,
	E_PLAYER_N,
	E_VOID
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

typedef struct s_texture
{
	t_id	identifier;
	char	*path;
}			t_texture;

typedef struct s_map
{
	t_type	value;
}			t_map;

typedef struct s_line_map
{
	char				*line_map;
	struct s_line_map	*next;
}				t_line_map;

typedef struct s_cub
{
	t_texture	texture[4];
	t_color		floor;
	t_color		ceiling;
	t_map		**map;
	t_line_map	*line_map;
	size_t		height;
	size_t		width;
	size_t		ofset_front;
	size_t		ofset_back;
	int			fd;
	int			endl;
}				t_cub;

void	ft_putendl_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		is_white_space(char c);
int		ft_pars(t_cub *cub, char *name_file);
char	*ft_strtrim(char *s1);
int		ft_atoi(char *str);
int		set_floor_ceiling(t_cub *cub, char *line);
int		set_texture(t_texture *texture, char *line);
int		set_line_map(t_line_map **line_map, char *line);
void	free_cub(t_cub *cub);
void	free_texture(t_cub *cub);
void	free_line_map(t_line_map **line_map);
int		ft_ofset_front(char *line);
int		creat_map(t_cub *cub);
int		check_texture(t_texture *texture);
int		check_colors(t_color *floor, t_color *ceiling);
int		ft_strcmp(char *s1, char *s2);
int		check_file_name(char *file);
void	free_map(t_cub *cub);
int		pars_map(t_cub *cub);
int		is_player(t_type value);
char	*ft_back_strtrim(char *s1);


void ft_write_cub(t_cub *cub);

#endif