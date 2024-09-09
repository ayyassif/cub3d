/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayyassif <ayyassif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:43:13 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/09 14:58:14 by ayyassif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "../MLX42.h"
# include <math.h>

# define WIDTH 955
# define HEIGHT 800
# define LEFT_KEY 0
# define RIGHT_KEY 2
# define UP_KEY 13
# define DOWN_KEY 1

# define SPEED 2

//tmp
# define TILE_SIZE 80

typedef struct s_s_map
{
	mlx_t		*mlx_s_map;
	mlx_image_t	*img_s_map;
}	t_s_map;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef enum e_type
{
	M_FLOOR,
	M_WALL,
	M_PLAYER_W,
	M_PLAYER_S,
	M_PLAYER_E,
	M_PLAYER_N,
	M_VOID
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

typedef struct s_pressed_down
{
	int	is_frwd;
	int	is_bckwd;
	int	is_right;
	int	is_left;
	int	is_turn_right;
	int	is_turn_left;
}		t_prsd_dwn;


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
	t_s_map		s_map;
	t_vec		pos;
	t_vec		direction;
	t_prsd_dwn	pressed_down;
}				t_cub;

int		ft_pars(t_cub *cub, char *name_file);

int		creat_map(t_cub *cub);
int		set_param(t_cub *cub, char *line, int i);
int		set_line_map(t_line_map **line_map, char *line);
void	set_cub(t_cub *cub);

int		check_file_name(char *file);
int		pars_map(t_cub *cub);
int		check_texture(t_texture *texture);
int		check_colors(t_color *floor, t_color *ceiling);

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);
int		ft_ofset_front(char *line);
char	*ft_strdup(const char *s1);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strtrim(char *s1);
char	*ft_back_strtrim(char *s1);

void	free_texture(t_cub *cub);
void	free_line_map(t_line_map **line_map);
void	free_cub(t_cub *cub);

int		is_player(t_type value);
int		is_white_space(char c);

void	ft_write_cub(t_cub *cub);

//-------------------------------------------------------------

int		mini_map(t_cub *cub);

//----------------------------------------------------------------

#endif