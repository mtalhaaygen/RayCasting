/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:04:26 by maygen            #+#    #+#             */
/*   Updated: 2023/12/16 11:25:45 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/gnl.h"
# include "math.h"
# define WIDTH 800
# define HEIGHT 600

typedef struct s_map
{
	char	**map;
	char	*map_name;
	int		map_width;
	int		map_height;
	int		cub_height;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*keys;
	int		f_color;
	int		c_color;
}	t_map;

typedef struct s_point
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	wall_x; //where exactly the wall was hit
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	double	step;
	double	tex_pos;
	int		tex_x;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sizeline;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_ray
{
	int		draw_start;
	int		draw_end;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;

}	t_ray;

typedef struct s_cub3d
{
	t_point	*player;
	t_img	img;
	t_map	*map;
	t_ray	*rays;
	t_img	*txt;
	void	*mlx;
	void	*mlx_win;
	void	*img_no;
	void	*img_so;
	void	*img_we;
	void	*img_ea;
}	t_cub3d;

int		print_err(char *str, char *arg);
void	filename_extension(char *str, char *dot);
char	*ft_trim(char *s1);
int		is_number(char *str);
void	map_fill(char **gv, t_map *map);

int		color_assigment(char	*tmp);
void	map_end(int fd);
void	map_reader2(t_map	*map, int fd, int i);
void	check_same(t_map	*map);
void	check_maps_border(t_map *map);
void	check_wall(t_map	*map);
void	map_null(t_map	*map);

void	decide_which_dir(t_cub3d *cub, int i, int j);
int		ray_casting(t_cub3d *cub);
void	open_window(t_cub3d *cub);

void	go_straight(t_cub3d *cub);
void	go_left(t_cub3d *cub);
void	go_back(t_cub3d *cub);
void	go_right(t_cub3d *cub);
void	turn_to_left(t_cub3d *cub);
void	turn_to_right(t_cub3d *cub);

void	if_not_img(t_cub3d *cub);
void	put_pixels(t_cub3d *cub, int x, int side);
void	fill_textures(t_cub3d *cub);
void	default_key(t_cub3d *cub);

void	fill_the_values(t_cub3d *cub, int x);
void	fill_side_dist(t_cub3d *cub);
int		single_ray_until_hit(t_cub3d *cub, int *hit);
int		the_range_of_pixels(t_cub3d *cub, int side);
void	texture_pixel(t_cub3d *cub, int side, int line_height);

int		destroy(t_cub3d *cub);
int		move(t_cub3d *cub);
int		key_press(int key, t_cub3d *cub);
int		key_release(int key, t_cub3d *cub);

#endif