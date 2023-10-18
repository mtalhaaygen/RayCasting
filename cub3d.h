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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_color;
	char	*c_color;
}	t_map;

typedef struct s_cub3d
{
	int		x;
	int		y;
	t_map	map;
}	t_cub3d;

int	print_err(char *str, char *arg);

#endif