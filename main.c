/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/12/07 19:41:37 by msaritas         ###   ########.fr       */
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
				cub->player->x = (double)j;
				cub->player->y = (double)i;
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
	cub->mlx_win = mlx_new_window(cub->mlx, 800, 600, "a");
	draw(cub);
	mlx_key_hook(cub->mlx_win, &move, cub);
	mlx_loop(cub->mlx);
}

int	main(int gc, char **gv)
{
	t_cub3d	*allcub;

	allcub = malloc(sizeof(t_cub3d));
	allcub->map = malloc(sizeof(t_map));
	allcub->player = malloc(sizeof(t_point));
	allcub->txt = malloc(sizeof(t_txt) * 4);
	allcub->txt[0].width = 64;
	allcub->txt[1].width = 64;
	allcub->txt[2].width = 64;
	allcub->txt[3].width = 64;
	allcub->txt[0].height = 64;
	allcub->txt[1].height = 64;
	allcub->txt[2].height = 64;
	allcub->txt[3].height = 64;
	allcub->view = 10.5;
	//allcub->ray = malloc(sizeof(t_point) * 2);
	if (gc == 2)
	{
		map_fill(gv, allcub->map);
		player_fill(allcub);

		printf("x: %f\n",allcub->player->x);
		printf("y: %f\n",allcub->player->y);
		printf("direction: %c\n",allcub->player->direction);
		int i = -1;
		
		while(allcub->map->map[++i])
		{
			printf("%s\n", allcub->map->map[i]);
		}
		open_window(allcub);
	}
	else
		return (print_err("invalid argument count", NULL));

	//system("leaks cub3d");
}
