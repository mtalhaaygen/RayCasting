/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/12/13 18:40:15 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_fill(t_cub3d *cub)
{
	int i;
	int j;
	int count;

	i = -1;
	count = 0;
	while (cub->map->map[++i])
	{
		j = -1;
		while (cub->map->map[i][++j])
			if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'W' ||
				cub->map->map[i][j] == 'E' || cub->map->map[i][j] == 'S')
			{
				cub->player->x = (double)j + 0.5;
				cub->player->y = (double)i + 0.5;
				decide_which_dir(cub, i, j);
				cub->map->map[i][j] = '0';
				count++;
			}
	}
	if (count != 1)
		print_err("hatalı player sayısı ", ft_itoa(count));
}

int    ray_casting(t_cub3d *cub)
{
    int     x;
    int     lineHeight;
    int     hit; //was there a wall hit?
    int     side; //was a NS or a EW wall hit?
    
    x = -1;
    mlx_clear_window(cub->mlx, cub->mlx_win);
    move(cub);
    while(++x < WIDTH)
    {
        fill_the_values(cub, x);
        hit = 0;
        fill_sideDist(cub);
        while (hit == 0)
            side = single_ray_until_hit(cub, &hit);
        lineHeight = the_range_of_pixels(cub, side);
        texture_pixel(cub, side, lineHeight);
        put_pixels(cub, x, side);
    }
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
    cub->player->moveSpeed = 0.04;
    cub->player->rotSpeed = 0.04;
    return (0);
}

void	open_window(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,
		&cub->img.sizeline, &cub->img.endian);
	fill_textures(cub);
	default_key(cub);
	mlx_hook(cub->mlx_win, 2, 0, keyPress, cub);
	mlx_hook(cub->mlx_win, 3, 0, keyRelease, cub);
	mlx_hook(cub->mlx_win, 17, 1L<<2, destroy, cub);
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

		/*printf("x: %f\n",allcub->player->x);
		printf("y: %f\n",allcub->player->y);
		printf("direction: %c\n",allcub->player->direction);
		printf("ea: %s\n",allcub->map->ea);
		printf("no: %s\n",allcub->map->no);
		printf("so: %s\n",allcub->map->so);
		printf("we: %s\n",allcub->map->we);

		int i = -1;
		
		while(allcub->map->map[++i])
		{
			printf("%s\n", allcub->map->map[i]);
		} */

		open_window(allcub);
	}
	else
		return (print_err("invalid argument count", NULL));
	mlx_destroy_image(allcub->mlx, allcub->img.img);
}
