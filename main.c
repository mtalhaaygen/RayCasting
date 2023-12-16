/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/12/16 11:46:20 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_fill(t_cub3d *cub)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (cub->map->map[++i])
	{
		j = -1;
		while (cub->map->map[i][++j])
		{
			if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'W' || \
				cub->map->map[i][j] == 'E' || cub->map->map[i][j] == 'S')
			{
				cub->player->x = (double)j + 0.5;
				cub->player->y = (double)i + 0.5;
				decide_which_dir(cub, i, j);
				cub->map->map[i][j] = '0';
				count++;
			}
		}
	}
	if (count != 1)
		print_err("number of player ", NULL);
}

int	ray_casting(t_cub3d *cub)
{
	int	x;
	int	line_height;
	int	hit;
	int	side;

	x = -1;
	mlx_clear_window(cub->mlx, cub->mlx_win);
	move(cub);
	while (++x < WIDTH)
	{
		fill_the_values(cub, x);
		hit = 0;
		fill_side_dist(cub);
		while (hit == 0)
			side = single_ray_until_hit(cub, &hit);
		line_height = the_range_of_pixels(cub, side);
		texture_pixel(cub, side, line_height);
		put_pixels(cub, x, side);
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
	cub->player->move_speed = 0.04;
	cub->player->rot_speed = 0.04;
	return (0);
}

void	open_window(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, \
		&cub->img.sizeline, &cub->img.endian);
	fill_textures(cub);
	default_key(cub);
	mlx_hook(cub->mlx_win, 2, 0, key_press, cub);
	mlx_hook(cub->mlx_win, 3, 0, key_release, cub);
	mlx_hook(cub->mlx_win, 17, 1L << 2, destroy, cub);
	mlx_loop_hook(cub->mlx, &ray_casting, cub);
	mlx_loop(cub->mlx);
}

int	main(int gc, char **gv)
{
	t_cub3d	*allcub;

	allcub = malloc(sizeof(t_cub3d));
	allcub->map = malloc(sizeof(t_map));
	allcub->player = malloc(sizeof(t_point));
	allcub->rays = malloc(sizeof(t_ray));
	if (gc == 2)
	{
		map_fill(gv, allcub->map);
		player_fill(allcub);
		open_window(allcub);
	}
	else
		return (print_err("invalid argument count", NULL));
	mlx_destroy_image(allcub->mlx, allcub->img.img);
}
