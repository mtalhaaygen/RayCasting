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

typedef struct s_txt
{
	unsigned int	height;
	unsigned int	width;
	void			*addr;

}t_txt;

typedef struct s_ray
{
	int		drawStart;
    int		drawEnd;
	int		mapx;
	int		mapy;
	int		stepX;
	int		stepY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
    double	sideDistY;
    double	deltaDistX;
    double	deltaDistY;
    double	perpWallDist;

} t_ray;

typedef struct s_cub3d
{
	t_point *player;
	t_img	img;
	t_map	*map;
	t_ray	*rays;
	t_txt	*txt; //duvarlar için resim eklersek diye
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

void	map_fill(char **gv, t_map *map_value);

int		color_assigment(char	*tmp);
void	map_end(int fd);
void	map_reader2(t_map	*map_value, int fd, int i);

void	check_same(t_map	*map_value);
void	check_wall(t_map	*map_value);

int		vectors(t_cub3d *cub);
float	ft_ray(t_cub3d *cub, float v);
int		draw(t_cub3d *cub);
int		move(int key, t_cub3d *cub);
void	open_window(t_cub3d *cub);
// void	insert_map(t_map *map, t_cub3d *cub);
// int		vectors(t_cub3d *cub);

#endif