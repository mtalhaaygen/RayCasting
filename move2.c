/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:02:17 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/16 11:12:47 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x +
			cub->player->dir_x * cub->player->move_speed)] == '0')
		cub->player->x += cub->player->dir_x * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y + cub->player->dir_y * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y += cub->player->dir_y * cub->player->move_speed;
}

void	go_left(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x +
			cub->player->dir_y * cub->player->move_speed)] == '0')
		cub->player->x += cub->player->dir_y * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y - cub->player->dir_x * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y += -cub->player->dir_x * cub->player->move_speed;
}

void	go_back(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x -
			cub->player->dir_x * cub->player->move_speed)] == '0')
		cub->player->x -= cub->player->dir_x * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y - cub->player->dir_y * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y -= cub->player->dir_y * cub->player->move_speed;
}

void	go_right(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x -
			cub->player->dir_y * cub->player->move_speed)] == '0')
		cub->player->x -= cub->player->dir_y * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y + cub->player->dir_x * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y -= -cub->player->dir_x * cub->player->move_speed;
}

void	turn_to_left(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player->dir_x;
	old_plane_x = cub->player->plane_x;
	cub->player->dir_x = cub->player->dir_x * cos(-cub->player->rot_speed) - \
							cub->player->dir_y * sin(-cub->player->rot_speed);
	cub->player->dir_y = old_dir_x * sin(-cub->player->rot_speed) + \
							cub->player->dir_y * cos(-cub->player->rot_speed);
	cub->player->plane_x = cub->player->plane_x * \
						cos(-cub->player->rot_speed) - \
							cub->player->plane_y * sin(-cub->player->rot_speed);
	cub->player->plane_y = old_plane_x * sin(-cub->player->rot_speed) + \
							cub->player->plane_y * cos(-cub->player->rot_speed);
}
