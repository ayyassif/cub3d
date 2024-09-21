/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:43:13 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/21 12:27:00 by hakaraou         ###   ########.fr       */
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

# define WIDTH 960
# define HEIGHT 720

# define SPEED 50
# define ROT_ANG 2

//tmp
# define TILE_SIZE 20

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
	M_PLAYER,
	M_VOID,
	M_ERROR
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
	int	frwd_bckwd;
	int	left_right;
	int	turn_left_right;
}		t_prsd_dwn;

typedef struct s_line_map
{
	char				*line_map;
	struct s_line_map	*next;
}				t_line_map;

typedef struct s_cub
{
	t_texture	texture[4];
	int			texture_id;
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
	t_vec		cam_plane;
	int			line_color;
	int			tile_size;
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

int		is_white_space(char c);

void	ft_write_cub(t_cub *cub);

//-------------------------------------------------------------

int		execution(t_cub *cub);
void	loop_hook(void *v_cub);
void	ray_casting(t_cub *cub, double perp_wall_dist);
void	draw_square(t_cub *cub, int x, int y, int color);
void	player_square_draw(t_cub *cub);
void	dda(t_vec pos, t_vec vec, t_cub *cub, int color);
void	ver_line(t_cub *cub, int drawStart, int drawEnd, int x);
int		create_rgb(int r, int g, int b);

//----------------------------------------------------------------

#endif