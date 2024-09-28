/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:43:13 by hakaraou          #+#    #+#             */
/*   Updated: 2024/09/28 11:20:55 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "../MLX42.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h> // tmp

# define HEIGHT 800
# define WIDTH 1200
# define ROT_ANG 100
# define M_MAP 5
# define TILE_SIZE 20
# define SPEED 50

typedef enum e_id
{
	E_NO,
	E_SO,
	E_WE,
	E_EA
}		t_id;

typedef enum e_type
{
	M_PLAYER,
	M_FLOOR,
	M_ERROR,
	M_WALL,
	M_VOID
}		t_type;

typedef struct s_map
{
	t_type	value;
}		t_map;

typedef struct s_vec
{
	double	x;
	double	y;
}		t_vec;

typedef struct s_s_map
{
	mlx_image_t	*img_s_map;
	mlx_t		*mlx_s_map;
}		t_s_map;

typedef struct s_line_map
{
	char				*line_map;
	struct s_line_map	*next;
}		t_line_map;

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}		t_color;

typedef struct s_texture
{
	t_id			identifier;
	mlx_texture_t	*tex_png;
	char			*path;
}		t_texture;

typedef struct s_pressed_down
{
	int	left_right;
	int	frwd_bckwd;
	int	turn_left_right;
}		t_prsd_dwn;

typedef struct s_cub
{
	double		tex_pos_y;
	double		tex_pos_x;
	double		perp_wall_dist;
	t_prsd_dwn	pressed_down;
	size_t		width;
	size_t		height;
	size_t		ofset_back;
	size_t		ofset_front;
	t_vec		delta_dist;
	t_vec		direction;
	t_vec		cam_plane;
	t_vec		side_dist;
	t_vec		pos;
	t_vec		ray;
	t_texture	texture[4];
	int			tile_size;
	int			tex_id;
	int			endl;
	int			side;
	int			fd;
	int			x;
	t_line_map	*line_map;
	t_color		ceiling;
	t_color		floor;
	t_map		**map;
	t_s_map		s_map;


	int			start;
}		t_cub;

/*===========================================================================*/
								/*PARSING*/
/*===========================================================================*/
void	set_cub(t_cub *cub);
int		pars_map(t_cub *cub);
int		creat_map(t_cub *cub);
int		check_file_name(char *file);
int		check_texture(t_texture *texture);
int		ft_pars(t_cub *cub, char *name_file);
int		set_param(t_cub *cub, char *line, int i);
int		check_colors(t_color *floor, t_color *ceiling);
int		set_line_map(t_line_map **line_map, char *line);

/*===========================================================================*/
								/*EXECUTION*/
/*===========================================================================*/
void	dda(t_vec vec, t_cub *cub, int color);
void	draw_square(t_cub *cub, double x, double y, int color);
void	ver_line(t_cub *cub, int drawStart, int drawEnd);
void	ft_put_pixel(mlx_image_t *image,
			uint32_t x, uint32_t y, uint32_t color);
void	player_square_draw(t_cub *cub);
void	ray_casting(t_cub *cub);
void	loop_hook(void *v_cub);
void	textures(t_cub *cub);
int		execution(t_cub *cub);
int		create_rgb(int r, int g, int b);
int		color_from_pixel(mlx_texture_t *texture, int index);


/*===========================================================================*/
								/*UTILS*/
/*===========================================================================*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
int		ft_ofset_front(char *line);
int		is_white_space(char c);
int		ft_atoi(char *str);
char	*ft_strtrim(char *s1);
char	*ft_back_strtrim(char *s1);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_cub(t_cub *cub);
void	free_texture(t_cub *cub);
void	ft_putendl_fd(char *s, int fd);
void	free_line_map(t_line_map **line_map);

//----------------------------------
int	intro(t_cub *cub);
//-------------------------------

#endif