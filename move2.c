/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:02:17 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/15 16:22:59 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_straight(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x +
			cub->player->dirx * cub->player->move_speed)] == '0')
		cub->player->x += cub->player->dirx * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y + cub->player->diry * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y += cub->player->diry * cub->player->move_speed;
}

void	go_left(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x +
			cub->player->diry * cub->player->move_speed)] == '0')
		cub->player->x += cub->player->diry * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y - cub->player->dirx * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y += -cub->player->dirx * cub->player->move_speed;
}

void	go_back(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x -
			cub->player->dirx * cub->player->move_speed)] == '0')
		cub->player->x -= cub->player->dirx * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y - cub->player->diry * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y -= cub->player->diry * cub->player->move_speed;
}

void	go_right(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x -
			cub->player->diry * cub->player->move_speed)] == '0')
		cub->player->x -= cub->player->diry * cub->player->move_speed;
	if (cub->map->map
		[(int)(cub->player->y + cub->player->dirx * cub->player->move_speed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y -= -cub->player->dirx * cub->player->move_speed;
}

void	turn_to_left(t_cub3d *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player->dirx;
	old_plane_x = cub->player->plane_x;
	cub->player->dirx = cub->player->dirx * cos(-cub->player->rot_speed) - \
							cub->player->diry * sin(-cub->player->rot_speed);
	cub->player->diry = old_dir_x * sin(-cub->player->rot_speed) + \
							cub->player->diry * cos(-cub->player->rot_speed);
	cub->player->plane_x = cub->player->plane_x * \
						cos(-cub->player->rot_speed) - \
							cub->player->plane_y * sin(-cub->player->rot_speed);
	cub->player->plane_y = old_plane_x * sin(-cub->player->rot_speed) + \
							cub->player->plane_y * cos(-cub->player->rot_speed);
}
