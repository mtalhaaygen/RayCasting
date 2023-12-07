#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/gnl.h"
# include "math.h"
# define PI 3.14159265359

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
	int		f_color;
	int		c_color;
}	t_map;

typedef struct s_point
{
	double	x;
	double	y;
	double dirx;
	double diry;
	double	planeX;
	double	planeY;
	double moveSpeed;
	double rotSpeed;
	double a;
	int direction;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sizeline;
	int		endian;
} t_img;

typedef struct s_ray
{
	double	vert_dist;
	double	hor_dist;
	double	vert_y;
	double	hor_y;
	double	hor_x;
	double	vert_x;
	double	dx;
	double	dy;
	int		sx;
	int		sy;
	float	vert_w;
	float	hor_w;
}t_ray;

typedef struct s_txt
{
	unsigned int	height;
	unsigned int	width;
	void			*addr;

}t_txt;

typedef struct s_cub3d
{
	t_point *player;
	t_ray	ray;
	t_img	img;
	t_map	*map;
	t_txt	*txt;
	void	*mlx;
	void	*mlx_win;
	int		txt_idx;
	float	txt_w;
	float	view;
}	t_cub3d;

int		print_err(char *str, char *arg);
void	filename_extension(char *str, char *dot);
char	*ft_trim(char *s1);

void	map_fill(char **gv, t_map *map_value);

int		color_assigment(char	*tmp);
void	map_end(int fd);
void	map_reader2(t_map	*map_value, int fd, int i);

int		vectors(t_cub3d *cub);
float	ft_ray(t_cub3d *cub, float v);
void	draw(t_cub3d *cub);
int		move(int key, t_cub3d *cub);
void	check_same(t_map	*map_value);
void    open_window(t_cub3d *cub);

#endif