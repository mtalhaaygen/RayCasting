/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:23:26 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/10 19:10:36 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_px_img(t_cub3d *f, int x, int y, int color)
{
	char	*dst;

	dst = f->img.addr + (y * f->img.sizeline + x * (f->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void    fill_the_values(t_cub3d *cub, int x)
{
    cub->rays->cameraX = ((2 * x) / (double)800) - 1;
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

void    the_range_of_pixels(t_cub3d *cub, int side)
{
    int lineHeight;

    if  (side == 0)
		cub->rays->perpWallDist = (cub->rays->sideDistX
				- cub->rays->deltaDistX);
    else
		cub->rays->perpWallDist = (cub->rays->sideDistY
				- cub->rays->deltaDistY);
    lineHeight = (int)(600 / cub->rays->perpWallDist);
    cub->rays->drawStart = -lineHeight / 2 + 600 / 2;
    cub->rays->drawEnd = lineHeight / 2 + 600 / 2; 
    if (cub->rays->drawStart < 0)
        cub->rays->drawStart = 0;
    if (cub->rays->drawEnd >= 600)
        cub->rays->drawEnd = 600 - 1;
}

void    put_pixels(t_cub3d *cub, int x, int color)
{
    int y;

    y = -1;
    while (++y < 600)
    {
        if (y < cub->rays->drawStart)
            put_px_img(cub, x, y, cub->map->c_color);
        else if (y >= cub->rays->drawStart && y <= cub->rays->drawEnd)
            put_px_img(cub, x, y, color);
        else
            put_px_img(cub, x, y, cub->map->f_color);
    }
}

int    vectors(t_cub3d *cub)
{
    int     x;
    int     hit; //was there a wall hit?
    int     side; //was a NS or a EW wall hit?
    
    x = -1;
    mlx_clear_window(cub->mlx, cub->mlx_win);
    move(cub);
    while(++x < 800)
    {
        fill_the_values(cub, x);
        hit = 0;
        fill_sideDist(cub);
        while (hit == 0)
            side = single_ray_until_hit(cub, &hit);
        the_range_of_pixels(cub, side);
        int color = 0xFFFF00; // duvar rengi olacak.
        // give x and y sides different brightness
        if (side == 1) {
            color = color / 2; // Adjust brightness
        }
        put_pixels(cub, x, color);
        // Draw the pixels of the stripe as a vertical line
    }
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
    cub->player->moveSpeed = 0.06;
    cub->player->rotSpeed = 0.04;
    return (0);
}
