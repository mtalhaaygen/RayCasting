/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:01:17 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/16 11:25:37 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_to_right(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player->dir_x;
	old_plane_x = cub->player->plane_x;
	cub->player->dir_x = cub->player->dir_x * cos(cub->player->rot_speed) - \
							cub->player->dir_y * sin(cub->player->rot_speed);
	cub->player->dir_y = old_dir_x * sin(cub->player->rot_speed) + \
							cub->player->dir_y * cos(cub->player->rot_speed);
	cub->player->plane_x = cub->player->plane_x * cos(cub->player->rot_speed) - \
							cub->player->plane_y * sin(cub->player->rot_speed);
	cub->player->plane_y = old_plane_x * sin(cub->player->rot_speed) + \
							cub->player->plane_y * cos(cub->player->rot_speed);
}

void	default_key(t_cub3d *cub)
{
	cub->map->keys = malloc(sizeof(int) * 7);
	cub->map->keys[0] = 0;
	cub->map->keys[1] = 0;
	cub->map->keys[2] = 0;
	cub->map->keys[3] = 0;
	cub->map->keys[4] = 0;
	cub->map->keys[5] = 0;
	cub->map->keys[6] = 0;
}

int	move(t_cub3d *cub)
{
	if (cub->map->keys[0])
		go_straight(cub);
	else if (cub->map->keys[2])
		go_back(cub);
	if (cub->map->keys[1])
		go_left(cub);
	else if (cub->map->keys[3])
		go_right(cub);
	if (cub->map->keys[4])
		turn_to_left(cub);
	if (cub->map->keys[5])
		turn_to_right(cub);
	if (cub->map->keys[6])
		destroy(cub);
	return (0);
}

int	key_press(int key, t_cub3d *cub)
{
	if (key == 13)
		cub->map->keys[0] = 1;
	else if (key == 0)
		cub->map->keys[1] = 1;
	else if (key == 1)
		cub->map->keys[2] = 1;
	else if (key == 2)
		cub->map->keys[3] = 1;
	else if (key == 123)
		cub->map->keys[4] = 1;
	else if (key == 124)
		cub->map->keys[5] = 1;
	else if (key == 53)
		cub->map->keys[6] = 1;
	return (0);
}

int	key_release(int key, t_cub3d *cub)
{
	if (key == 13)
		cub->map->keys[0] = 0;
	else if (key == 0)
		cub->map->keys[1] = 0;
	else if (key == 1)
		cub->map->keys[2] = 0;
	else if (key == 2)
		cub->map->keys[3] = 0;
	else if (key == 123)
		cub->map->keys[4] = 0;
	else if (key == 124)
		cub->map->keys[5] = 0;
	else if (key == 53)
		cub->map->keys[6] = 0;
	return (0);
}
