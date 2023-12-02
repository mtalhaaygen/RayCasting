#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/gnl.h"
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
	int	x;
	int	y;
	int direction;
}	t_point;

typedef struct s_cub3d
{
	t_point *player;
	// t_point *ray;
	t_map	*map;
	void	*mlx;
	void	*mlx_win;
}	t_cub3d;


int		print_err(char *str, char *arg);
void	filename_extension(char *str, char *dot);
char	*ft_trim(char *s1);

void	map_fill(char **gv, t_map *map_value);

int		color_assigment(char	*tmp);
void	map_end(int fd);
void	map_reader2(t_map	*map_value, int fd, int i);

void	check_same(t_map	*map_value);
void    open_window(t_cub3d *cub);

#endif