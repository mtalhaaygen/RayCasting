/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:15:15 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/11 20:16:47 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		destroy(t_cub3d *cub)
{
	//free
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	//system("leaks cub3d"); //leak var
    exit (0);
}

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
