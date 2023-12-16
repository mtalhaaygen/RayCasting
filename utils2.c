/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:15:15 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/16 11:53:36 by maygen           ###   ########.fr       */
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
	cub->player->dir_x = x;
	cub->player->dir_y = y;
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

void	fill_textures(t_cub3d *cub)
{
	if_not_img(cub);
	cub->txt = malloc(sizeof(t_img) * 4);
	cub->txt[0].img = mlx_xpm_file_to_image(cub->mlx, cub->map->no, \
		&cub->txt[0].w, &cub->txt[0].h);
	cub->txt[1].img = mlx_xpm_file_to_image(cub->mlx, cub->map->so, \
		&cub->txt[1].w, &cub->txt[1].h);
	cub->txt[2].img = mlx_xpm_file_to_image(cub->mlx, cub->map->we, \
		&cub->txt[2].w, &cub->txt[2].h);
	cub->txt[3].img = mlx_xpm_file_to_image(cub->mlx, cub->map->ea, \
		&cub->txt[3].w, &cub->txt[3].h);
	cub->txt[0].addr = mlx_get_data_addr(cub->txt[0].img, &cub->txt[0].bpp, \
		&cub->txt[0].sizeline, &cub->txt[0].endian);
	cub->txt[1].addr = mlx_get_data_addr(cub->txt[1].img, &cub->txt[1].bpp, \
		&cub->txt[1].sizeline, &cub->txt[1].endian);
	cub->txt[2].addr = mlx_get_data_addr(cub->txt[2].img, &cub->txt[2].bpp, \
		&cub->txt[2].sizeline, &cub->txt[2].endian);
	cub->txt[3].addr = mlx_get_data_addr(cub->txt[3].img, &cub->txt[3].bpp, \
		&cub->txt[3].sizeline, &cub->txt[3].endian);
}
