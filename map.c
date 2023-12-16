/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:23:26 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/16 10:25:51 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_the_values(t_cub3d *cub, int x)
{
	cub->rays->camera_x = ((2 * x) / (double)WIDTH) - 1;
	cub->rays->ray_dir_x = cub->player->dirx + \
		cub->player->plane_x * cub->rays->camera_x;
	cub->rays->ray_dir_y = cub->player->diry + \
		cub->player->plane_y * cub->rays->camera_x;
	cub->rays->mapx = (int)cub->player->x;
	cub->rays->mapy = (int)cub->player->y;
	if (cub->rays->ray_dir_x == 0)
		cub->rays->delta_dist_x = 1e30;
	else
		cub->rays->delta_dist_x = fabs(1 / cub->rays->ray_dir_x);
	if (cub->rays->ray_dir_y == 0)
		cub->rays->delta_dist_y = 1e30;
	else
		cub->rays->delta_dist_y = fabs(1 / cub->rays->ray_dir_y);
}

void	fill_side_dist(t_cub3d *cub)
{
	if (cub->rays->ray_dir_x < 0)
	{
		cub->rays->step_x = -1;
		cub->rays->side_dist_x = (cub->player->x - cub->rays->mapx)
			* cub->rays->delta_dist_x;
	}
	else
	{
		cub->rays->step_x = 1;
		cub->rays->side_dist_x = (cub->rays->mapx + 1.0 - cub->player->x)
			* cub->rays->delta_dist_x;
	}
	if (cub->rays->ray_dir_y < 0)
	{
		cub->rays->step_y = -1;
		cub->rays->side_dist_y = (cub->player->y - cub->rays->mapy)
			* cub->rays->delta_dist_y;
	}
	else
	{
		cub->rays->step_y = 1;
		cub->rays->side_dist_y = (cub->rays->mapy + 1.0 - cub->player->y)
			* cub->rays->delta_dist_y;
	}
}

int	single_ray_until_hit(t_cub3d *cub, int *hit)
{
	int	side;

	if (cub->rays->side_dist_x < cub->rays->side_dist_y)
	{
		cub->rays->side_dist_x += cub->rays->delta_dist_x;
		cub->rays->mapx += cub->rays->step_x;
		side = 0;
	}
	else
	{
		cub->rays->side_dist_y += cub->rays->delta_dist_y;
		cub->rays->mapy += cub->rays->step_y;
		side = 1;
	}
	if (cub->map->map[cub->rays->mapy][cub->rays->mapx] == '1')
		*hit = 1;
	return (side);
}

int	the_range_of_pixels(t_cub3d *cub, int side)
{
	int	line_height;

	if (side == 0)
		cub->rays->perp_wall_dist = (cub->rays->side_dist_x
				- cub->rays->delta_dist_x);
	else
		cub->rays->perp_wall_dist = (cub->rays->side_dist_y
				- cub->rays->delta_dist_y);
	line_height = (int)(HEIGHT / cub->rays->perp_wall_dist);
	cub->rays->draw_start = -line_height / 2 + HEIGHT / 2;
	cub->rays->draw_end = line_height / 2 + HEIGHT / 2;
	if (cub->rays->draw_start < 0)
		cub->rays->draw_start = 0;
	if (cub->rays->draw_end >= HEIGHT)
		cub->rays->draw_end = HEIGHT - 1;
	return (line_height);
}

void	texture_pixel(t_cub3d *cub, int side, int line_height)
{
	if (side == 0)
		cub->player->wall_x = cub->player->y
			+ cub->rays->perp_wall_dist * cub->rays->ray_dir_y;
	else
		cub->player->wall_x = cub->player->x
			+ cub->rays->perp_wall_dist * cub->rays->ray_dir_x;
	cub->player->wall_x -= (int)cub->player->wall_x;
	cub->player->tex_x = (int)(cub->player->wall_x * (double)(64));
	if (side == 0 && cub->rays->ray_dir_x > 0)
		cub->player->tex_x = 64 - cub->player->tex_x - 1;
	if (side == 1 && cub->rays->ray_dir_y < 0)
		cub->player->tex_x = 64 - cub->player->tex_x - 1;
	cub->player->step = 1.0 * 64 / line_height;
	cub->player->tex_pos = (cub->rays->draw_start \
		- HEIGHT / 2 + line_height / 2)
		* cub->player->step;
}
