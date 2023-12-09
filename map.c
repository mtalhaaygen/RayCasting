/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:23:26 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/09 14:45:02 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int move(int key, t_cub3d *cub)
{
    int width;

    width = 64;
    if (key == 13) //w
    {
        if(cub->map->map[(int)(cub->player->y)][(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)] == '0') 
            cub->player->x += cub->player->dirx * cub->player->moveSpeed;
        if(cub->map->map[(int)(cub->player->y + cub->player->diry * cub->player->moveSpeed)][(int)(cub->player->x)] == '0') 
            cub->player->y += cub->player->diry * cub->player->moveSpeed;
    }
    else if (key == 0)//a
    {
        if(cub->map->map[(int)( cub->player->y)][(int)(cub->player->x - cub->player->diry * cub->player->moveSpeed)] == '0')
            cub->player->x -= cub->player->diry * cub->player->moveSpeed;
        if(cub->map->map[(int)(cub->player->y - cub->player->dirx * cub->player->moveSpeed)][(int)(cub->player->x)] == '0')
            cub->player->y -= cub->player->dirx * cub->player->moveSpeed;
    }
    else if (key == 1)//s
    {
        if(cub->map->map[(int)( cub->player->y)][(int)(cub->player->x - cub->player->dirx * cub->player->moveSpeed)] == '0')
            cub->player->x -= cub->player->dirx * cub->player->moveSpeed;
        if(cub->map->map[(int)(cub->player->y - cub->player->diry * cub->player->moveSpeed)][(int)(cub->player->x)] == '0')
            cub->player->y -= cub->player->diry * cub->player->moveSpeed;
    }
    else if (key == 2)//d
    {
        if(cub->map->map[(int)( cub->player->y)][(int)(cub->player->x + cub->player->diry * cub->player->moveSpeed)] == '0')
            cub->player->x += cub->player->diry * cub->player->moveSpeed;
        if(cub->map->map[(int)(cub->player->y + cub->player->dirx * cub->player->moveSpeed)][(int)(cub->player->x)] == '0')
            cub->player->y += cub->player->dirx * cub->player->moveSpeed;
    }
    else if (key == 123) //to the left
    {
        double oldDirX = cub->player->dirx;
        double oldPlaneX = cub->player->planeX;
        cub->player->dirx = cub->player->dirx * cos(-cub->player->rotSpeed) - cub->player->diry * sin(-cub->player->rotSpeed);
        cub->player->diry = oldDirX * sin(-cub->player->rotSpeed) + cub->player->diry * cos(-cub->player->rotSpeed);
        cub->player->planeX = cub->player->planeX * cos(-cub->player->rotSpeed) - cub->player->planeY * sin(-cub->player->rotSpeed);
        cub->player->planeY = oldPlaneX * sin(-cub->player->rotSpeed) + cub->player->planeY * cos(-cub->player->rotSpeed);
    }
    else if (key == 124) //to the right
    {
        double oldDirX = cub->player->dirx;
        double oldPlaneX = cub->player->planeX;
        cub->player->dirx = cub->player->dirx * cos(cub->player->rotSpeed) - cub->player->diry * sin(cub->player->rotSpeed);
        cub->player->diry = oldDirX * sin(cub->player->rotSpeed) + cub->player->diry * cos(cub->player->rotSpeed);
        cub->player->planeX = cub->player->planeX * cos(cub->player->rotSpeed) - cub->player->planeY * sin(cub->player->rotSpeed);
        cub->player->planeY = oldPlaneX * sin(cub->player->rotSpeed) + cub->player->planeY * cos(cub->player->rotSpeed);
    }
    else if (key == 53) //esc, seg veriyor
    {
        mlx_destroy_window(cub->mlx, cub->mlx_win);
    }
    return (0);
}

void	put_px_img(t_cub3d *f, int x, int y, int color)
{
	char	*dst;

	dst = f->img.addr + (y * f->img.sizeline + x * (f->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int    vectors(t_cub3d *cub)
{
    int     x;
    int     mapx;
    int     mapy;
    int     stepX;
    int     stepY;
    int     hit; //was there a wall hit?
    int     side; //was a NS or a EW wall hit?
    double cameraX;
    double rayDirX;
    double rayDirY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double  deltaDistY;
    double  perpWallDist;
    int     lineHeight;
    int drawStart;
    int drawEnd;
    

    x = -1;
    mlx_clear_window(cub->mlx, cub->mlx_win);
    while(++x < 800)
    {
        cameraX = ((2 * x) / (double)800) - 1;
        rayDirX = cub->player->dirx + cub->player->planeX * cameraX;
        rayDirY = cub->player->diry + cub->player->planeY * cameraX;
        // her turda mapx mapy değerleri player ın konumunu tutuyor
        mapx = (int)cub->player->x;
        mapy = (int)cub->player->y;
        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        hit = 0;
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (cub->player->x - mapx) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapx + 1.0 - cub->player->x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (cub->player->y - mapy) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapy + 1.0 - cub->player->y) * deltaDistY;
        }
        while (hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapx += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapy += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (cub->map->map[mapy][mapx] == '1')
                hit = 1;
        } 
        if  (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        lineHeight = (int)(600 / perpWallDist);
        drawStart = -lineHeight / 2 + 600 / 2;
        drawEnd = lineHeight / 2 + 600 / 2;
        
        if (drawStart < 0)
            drawStart = 0;
        if (drawEnd >= 600)
            drawEnd = 600 - 1;

        int color = 0xFFFF00; // yellow

        // give x and y sides different brightness
        if (side == 1) {
            color = color / 2; // Adjust brightness
        }

        // Draw the pixels of the stripe as a vertical line
        int y = -1;
        while (++y < 600)
        {
            if (y < drawStart)
                put_px_img(cub, x, y, cub->map->c_color);
            else if (y >= drawStart && y <= drawEnd)
                put_px_img(cub, x, y, color);
            else
                put_px_img(cub, x, y, cub->map->f_color);
        }
    }
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
    cub->player->moveSpeed = 0.06;
    cub->player->rotSpeed = 0.04;
    return (0);
}
