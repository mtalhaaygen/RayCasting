/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/12/10 19:25:58 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_player_dir(t_cub3d *cub, double x, double y)
{
	cub->player->dirx = x;
	cub->player->diry = y;
	if (x < 0.0)
		cub->player->planeY = -0.66;
	else if (x > 0.0)
		cub->player->planeY = 0.66;
	else
		cub->player->planeY = 0;
	if (y < 0.0)
		cub->player->planeX = 0.66;
	else if (y > 0.0)
		cub->player->planeX = -0.66;
	else
		cub->player->planeX = 0;
}

void	decide_which_dir(t_cub3d *cub, int i, int j)
{
	if (cub->map->map[i][j] == 'N')
		fill_player_dir(cub, 0.0, -1.0);
	else if (cub->map->map[i][j] == 'S')
		fill_player_dir(cub, 0.0, 1.0);
	else if (cub->map->map[i][j] == 'W')
		fill_player_dir(cub, -1.0, 0.0);
	else if (cub->map->map[i][j] == 'E')
		fill_player_dir(cub, 1.0, 0.0);
	
}

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
			if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'W' || cub->map->map[i][j] == 'E' || cub->map->map[i][j] == 'S')
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
int		destroy(t_cub3d *cub)
{
	//free
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	//system("leaks cub3d"); //leak var
    exit (0);
}

void	open_window(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, 800, 600, "cub3d");
	cub->img.img = mlx_new_image(cub->mlx, 800, 600);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, &cub->img.sizeline, &cub->img.endian);
	mlx_hook(cub->mlx_win, 2, 0, keyPress, cub);
	mlx_hook(cub->mlx_win, 3, 0, keyRelease, cub);
	mlx_hook(cub->mlx_win, 17, 1L<<2, destroy, cub);
	mlx_loop_hook(cub->mlx, &vectors, cub);
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

		/* printf("x: %f\n",allcub->player->x);
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
	//system("leaks cub3d");
}
