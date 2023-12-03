/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/12/04 01:56:14 by maygen           ###   ########.fr       */
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
			if (cub->map->map[i][j] == 'N' || cub->map->map[i][j] == 'W' || cub->map->map[i][j] == 'E' || cub->map->map[i][j] == 'S')
			{
				cub->player->x = j;
				cub->player->y = i;
				cub->player->direction = cub->map->map[i][j];
				count++;
			}
	}
	if (count != 1)
		print_err("hatalı player sayısı ", ft_itoa(count));
}

void	open_window(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, 1920, 1080, "a");
	mlx_loop(cub->mlx);
}

int	main(int gc, char **gv)
{
	t_cub3d	*allcub;

	allcub = malloc(sizeof(t_cub3d));
	allcub->map = malloc(sizeof(t_map));
	allcub->player = malloc(sizeof(t_point));
	if (gc == 2)
	{
		map_fill(gv, allcub->map);
		player_fill(allcub);

		printf("map_name: %s\n",allcub->map->map_name);
		printf("map_width: %d\n",allcub->map->map_width);
		printf("map_height: %d\n",allcub->map->map_height);
		printf("cub_height: %d\n",allcub->map->cub_height);
		printf("no: %s\n",allcub->map->no);
		printf("so: %s\n",allcub->map->so);
		printf("we: %s\n",allcub->map->we);
		printf("ea: %s\n",allcub->map->ea);
		printf("f_color: %d\n",allcub->map->f_color);
		printf("c_color: %d\n",allcub->map->c_color);

		// int i = -1;
		// while (allcub->map->map[++i])
		// 	printf("map: %s\n",allcub->map->map[i]);

		printf("x: %d\n",allcub->player->x);
		printf("y: %d\n",allcub->player->y);
		printf("direction: %c\n",allcub->player->direction);

		open_window(allcub);
	}
	else
		return (print_err("invalid argument count", NULL));

	//system("leaks cub3d");
}
