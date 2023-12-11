/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:02:17 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/11 19:48:27 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    go_straight(t_cub3d *cub)
{
	if (cub->map->map[(int)(cub->player->y)][(int)(cub->player->x +
			cub->player->dirx * cub->player->moveSpeed)] == '0')
		cub->player->x += cub->player->dirx * cub->player->moveSpeed;
	if (cub->map->map
		[(int)(cub->player->y + cub->player->diry * cub->player->moveSpeed)]
		[(int)(cub->player->x)] == '0')
		cub->player->y += cub->player->diry * cub->player->moveSpeed;
}

void    go_left(t_cub3d *cub)
{
    if(cub->map->map[(int)(cub->player->y)][(int)(cub->player->x -
			cub->player->diry * cub->player->moveSpeed)] == '0')
        cub->player->x += cub->player->diry * cub->player->moveSpeed;
    if(cub->map->map
		[(int)(cub->player->y - cub->player->dirx * cub->player->moveSpeed)]
		[(int)(cub->player->x)] == '0')
        cub->player->y -= cub->player->dirx * cub->player->moveSpeed;
}

void    go_back(t_cub3d *cub)
{
    if(cub->map->map[(int)(cub->player->y)][(int)(cub->player->x -
			cub->player->dirx * cub->player->moveSpeed)] == '0')
        cub->player->x -= cub->player->dirx * cub->player->moveSpeed;
    if(cub->map->map
		[(int)(cub->player->y - cub->player->diry * cub->player->moveSpeed)]
		[(int)(cub->player->x)] == '0')
        cub->player->y -= cub->player->diry * cub->player->moveSpeed;
}
void    go_right(t_cub3d *cub)
{
    if(cub->map->map[(int)( cub->player->y)][(int)(cub->player->x +
			cub->player->diry * cub->player->moveSpeed)] == '0')
        cub->player->x -= cub->player->diry * cub->player->moveSpeed;
    if(cub->map->map
		[(int)(cub->player->y + cub->player->dirx * cub->player->moveSpeed)]
		[(int)(cub->player->x)] == '0')
        cub->player->y += cub->player->dirx * cub->player->moveSpeed;    
}

void    turn_to_left(t_cub3d *cub)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = cub->player->dirx;
    oldPlaneX = cub->player->planeX;
    cub->player->dirx = cub->player->dirx * cos(-cub->player->rotSpeed) -
							cub->player->diry * sin(-cub->player->rotSpeed);
    cub->player->diry = oldDirX * sin(-cub->player->rotSpeed) +
							cub->player->diry * cos(-cub->player->rotSpeed);
    cub->player->planeX = cub->player->planeX * cos(-cub->player->rotSpeed) -
							cub->player->planeY * sin(-cub->player->rotSpeed);
    cub->player->planeY = oldPlaneX * sin(-cub->player->rotSpeed) +
							cub->player->planeY * cos(-cub->player->rotSpeed);
}
