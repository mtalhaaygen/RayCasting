/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:01:17 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/15 16:26:33 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_to_right(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player->dirx;
	old_plane_x = cub->player->plane_x;
	cub->player->dirx = cub->player->dirx * cos(cub->player->rot_speed) - \
							cub->player->diry * sin(cub->player->rot_speed);
	cub->player->diry = old_dir_x * sin(cub->player->rot_speed) + \
							cub->player->diry * cos(cub->player->rot_speed);
	cub->player->plane_x = cub->player->plane_x * cos(cub->player->rot_speed) - \
							cub->player->plane_y * sin(cub->player->rot_speed);
	cub->player->plane_y = old_plane_x * sin(cub->player->rot_speed) + \
							cub->player->plane_y * cos(cub->player->rot_speed);
}

void	default_key(t_cub3d *cub)
{
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
	if (cub->map->keys[0]) //w
		go_straight(cub);
	else if (cub->map->keys[2])//s
		go_back(cub);
	if (cub->map->keys[1])//a
		go_left(cub);
	else if (cub->map->keys[3])//d
		go_right(cub);
	if (cub->map->keys[4]) //to the left
		turn_to_left(cub);
	if (cub->map->keys[5]) //to the right
		turn_to_right(cub);
	if (cub->map->keys[6]) //esc
		destroy(cub);
	return (0);
}

int	keyPress(int key, t_cub3d *cub)
{
	if (key == 13) //w
		cub->map->keys[0] = 1;
	else if (key == 0) //a
		cub->map->keys[1] = 1;
	else if (key == 1) //s
		cub->map->keys[2] = 1;
	else if (key == 2) //d
		cub->map->keys[3] = 1;
	else if (key == 123) //to the left
		cub->map->keys[4] = 1;
	else if (key == 124) //to the right
		cub->map->keys[5] = 1;
	else if (key == 53) //esc
		cub->map->keys[6] = 1;
	return (0);
}

int	keyRelease(int key, t_cub3d *cub)
{
	if (key == 13) //w
		cub->map->keys[0] = 0;
	else if (key == 0)//a
		cub->map->keys[1] = 0;
	else if (key == 1)//s
		cub->map->keys[2] = 0;
	else if (key == 2)//d
		cub->map->keys[3] = 0;
	else if (key == 123) //to the left
		cub->map->keys[4] = 0;
	else if (key == 124) //to the right
		cub->map->keys[5] = 0;
	else if (key == 53) //esc
		cub->map->keys[6] = 0;
	return (0);
}

