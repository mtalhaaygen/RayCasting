/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:23:26 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/11 20:17:31 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    fill_the_values(t_cub3d *cub, int x)
{
    cub->rays->cameraX = ((2 * x) / (double)WIDTH) - 1;
    cub->rays->rayDirX = cub->player->dirx +
		cub->player->planeX * cub->rays->cameraX;
    cub->rays->rayDirY = cub->player->diry +
		cub->player->planeY * cub->rays->cameraX;
    // her turda mapx mapy değerleri player ın konumunu tutuyor
    cub->rays->mapx = (int)cub->player->x;
    cub->rays->mapy = (int)cub->player->y;
    if (cub->rays->rayDirX == 0)
        cub->rays->deltaDistX = 1e30;
    else
        cub->rays->deltaDistX = fabs(1 / cub->rays->rayDirX);
    if (cub->rays->rayDirY == 0)
        cub->rays->deltaDistY = 1e30;
    else
        cub->rays->deltaDistY = fabs(1 / cub->rays->rayDirY);
}

void    fill_sideDist(t_cub3d *cub)
{
    if (cub->rays->rayDirX < 0)
    {
        cub->rays->stepX = -1;
        cub->rays->sideDistX = (cub->player->x - cub->rays->mapx)
			* cub->rays->deltaDistX;
    }
    else
    {
        cub->rays->stepX = 1;
        cub->rays->sideDistX = (cub->rays->mapx + 1.0 - cub->player->x)
			* cub->rays->deltaDistX;
    }
    if (cub->rays->rayDirY < 0)
    {
        cub->rays->stepY = -1;
        cub->rays->sideDistY = (cub->player->y - cub->rays->mapy)
			* cub->rays->deltaDistY;
    }
    else
    {
        cub->rays->stepY = 1;
        cub->rays->sideDistY = (cub->rays->mapy + 1.0 - cub->player->y)
			* cub->rays->deltaDistY;
    }
}

int    single_ray_until_hit(t_cub3d *cub, int *hit)
{
    int side;

    //jump to next map square, either in x-direction, or in y-direction
    if (cub->rays->sideDistX < cub->rays->sideDistY)
    {
        cub->rays->sideDistX += cub->rays->deltaDistX;
        cub->rays->mapx += cub->rays->stepX;
        side = 0;
    }
    else
    {
        cub->rays->sideDistY += cub->rays->deltaDistY;
        cub->rays->mapy += cub->rays->stepY;
        side = 1;
    }
    //Check if ray has hit a wall
    if (cub->map->map[cub->rays->mapy][cub->rays->mapx] == '1')
        *hit = 1;
    return (side);
}

int the_range_of_pixels(t_cub3d *cub, int side)
{
    int lineHeight;

    if  (side == 0)
		cub->rays->perpWallDist = (cub->rays->sideDistX
				- cub->rays->deltaDistX);
    else
		cub->rays->perpWallDist = (cub->rays->sideDistY
				- cub->rays->deltaDistY);
    lineHeight = (int)(HEIGHT / cub->rays->perpWallDist);
    cub->rays->drawStart = -lineHeight / 2 + HEIGHT / 2;
    cub->rays->drawEnd = lineHeight / 2 + HEIGHT / 2; 
    if (cub->rays->drawStart < 0)
        cub->rays->drawStart = 0;
    if (cub->rays->drawEnd >= HEIGHT)
        cub->rays->drawEnd = HEIGHT - 1;
    return (lineHeight);
}

void    texture_pixel(t_cub3d *cub, int side, int lineHeight)
{
    //calculate value of wallX
    if (side == 0)
        cub->player->wallX = cub->player->y
            + cub->rays->perpWallDist * cub->rays->rayDirY;
    else
        cub->player->wallX = cub->player->x
            + cub->rays->perpWallDist * cub->rays->rayDirX;
    cub->player->wallX -= (int)cub->player->wallX;
    //x coordinate on the texture
    cub->player->texX = (int)(cub->player->wallX * (double)(64));
    if(side == 0 && cub->rays->rayDirX > 0)
        cub->player->texX = 64 - cub->player->texX - 1;
    if(side == 1 && cub->rays->rayDirY < 0)
        cub->player->texX = 64 - cub->player->texX - 1;
    // How much to increase the texture coordinate per screen pixel
    cub->player->step = 1.0 * 64 / lineHeight;
    // Starting texture coordinate
    cub->player->texPos = (cub->rays->drawStart - HEIGHT / 2 + lineHeight / 2)
        * cub->player->step;
}
