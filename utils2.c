/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:15:15 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/15 16:18:31 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy(t_cub3d *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	exit(0);
}

void	fill_player_dir(t_cub3d *cub, double x, double y)
{
	cub->player->dirx = x;
	cub->player->diry = y;
	if (x < 0.0)
		cub->player->plane_y = -0.66;
	else if (x > 0.0)
		cub->player->plane_y = 0.66;
	else
		cub->player->plane_y = 0;
	if (y < 0.0)
		cub->player->plane_x = 0.66;
	else if (y > 0.0)
		cub->player->plane_x = -0.66;
	else
		cub->player->plane_x = 0;
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
