/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:23:26 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/03 22:58:24 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int    vectors(t_cub3d *cub)
{
    int     x;
    int     mapx;
    int     mapy;
    int     stepX;
    int     stepY;
    int     hit; //was there a wall hit?
    int     side; //was a NS or a EW wall hit?
    double planeX;
    double planeY;
    double cameraX;
    //double cameraY;
    double rayDirX;
    double rayDirY;
    double time;
    double oldtime;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double  deltaDistY;
    double  perpWallDist;
    int     lineHeight;
    int drawStart;
    int drawEnd;
    
    planeX = 0;
    planeY = 0.66;
    time = 0;
    oldtime = 0;
    hit = 0;
    
    x = -1;
    while (++x < 800)
    {
        cameraX = 2 * x / (double)(800) - 1;
        rayDirX = cub->player->dirx + planeX * cameraX;
        rayDirY = cub->player->diry + planeY * cameraX;
        mapx = cub->player->x;
        mapy = cub->player->y;
        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
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
            if (cub->map->map[mapx][mapy] > 0)
                hit = 1;
        } 
        if  (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        //printf("xx%f\n", perpWallDist);
        if (perpWallDist != 0) {
            lineHeight = (int)(600 / perpWallDist);
            drawStart = -lineHeight / 2 + 600 / 2;
            drawEnd = lineHeight / 2 + 600 / 2;

            if (drawStart < 0) drawStart = 0;
            if (drawEnd >= 600) drawEnd = 600 - 1;

            int color;

            switch (cub->map->map[mapx][mapy]) {
                case 1: color = 0xFF0000; break; // red
                default: color = 0xFFFF00; break; // yellow
            }

            // give x and y sides different brightness
            if (side == 1) {
                color = color / 2; // Adjust brightness
            }

            // Draw the pixels of the stripe as a vertical line
            while (drawStart >= drawEnd && drawStart > 0 && drawEnd > 0) {
                mlx_pixel_put(cub->mlx, cub->mlx_win, x, drawStart, color);
                // draw_vertical_line(x, drawStart, drawEnd, color);
                drawStart -= 1;
            }
        }
    }

    cub->player->moveSpeed = 0.06;
    cub->player->rotSpeed = 0.04;
    cub->player->planeX = planeX;
    cub->player->planeY = planeY;
    return (0);
}

int move(int key, t_cub3d *cub)
{
    //void *img;
    int width;

    width = 64;
    //printf("key:%d\n", key);
    if (key == 13) //w
    {
        /* img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x, cub->player->y - 64); 
        cub->player->y -= 64; */
        //cub->player->y--;
        //cub->player->y += cub->player->diry;
        //cub->player->x += cub->player->dirx;
        if(!cub->map->map[(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)][(int)( cub->player->y)]) cub->player->x += cub->player->dirx * cub->player->moveSpeed;
        if(!cub->map->map[(int)(cub->player->x)][(int)(cub->player->y + cub->player->diry * cub->player->moveSpeed)]) cub->player->y += cub->player->diry * cub->player->moveSpeed;
    }   
    else if (key == 0)//a
    {
        /* img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x - 64, cub->player->y); 
        cub->player->x -= 64; */
        //cub->player->x--;
        //cub->player->x += cub->player->dirx;
        if(!cub->map->map[(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)][(int)( cub->player->y)]) cub->player->x += cub->player->dirx * cub->player->moveSpeed;
        
    }
    else if (key == 1)//s
    {
        /* img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x, cub->player->y + 64); 
        cub->player->y += 64; */
        //cub->player->y++;
        /* cub->player->y -= cub->player->diry;
        cub->player->x -= cub->player->dirx; */
        if(!cub->map->map[(int)(cub->player->x - cub->player->dirx * cub->player->moveSpeed)][(int)(cub->player->y)]) cub->player->x -= cub->player->dirx * cub->player->moveSpeed;
        if(!cub->map->map[(int)(cub->player->x)][(int)(cub->player->y - cub->player->diry * cub->player->moveSpeed)]) cub->player->y -= cub->player->diry * cub->player->moveSpeed;   
    }
    else if (key == 2)//d
    {
        //img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x + 64, cub->player->y); 
        //cub->player->x += 64;
        //cub->player->x++;
        //cub->player->x -= cub->player->dirx;
        if(!cub->map->map[(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)][(int)( cub->player->y)]) cub->player->x -= cub->player->dirx * cub->player->moveSpeed;
    }
    else if (key == 124) //to the right
    {
        //img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x + 64, cub->player->y); 
        //cub->player->x += 64;
        double oldDirX = cub->player->dirx;
        cub->player->dirx = cub->player->dirx * cos(-cub->player->rotSpeed) - cub->player->diry * sin(-cub->player->rotSpeed); //-rotspeed
        cub->player->diry = oldDirX * sin(-cub->player->rotSpeed) + cub->player->diry * cos(-cub->player->rotSpeed);
        double oldPlaneX = cub->player->planeX;
        cub->player->planeX = cub->player->planeX * cos(-cub->player->rotSpeed) - cub->player->planeY * sin(-cub->player->rotSpeed);
        cub->player->planeY = oldPlaneX * sin(-cub->player->rotSpeed) + cub->player->planeY * cos(-cub->player->rotSpeed);
        /*cub->player->a -= 0.1;
        if (cub->player->a < 0)
            cub->player->a += 2 * PI;
        cub->player->dirx = cos(cub->player->a) * 5;
        cub->player->diry = sin(cub->player->a) * 5; */
    }
    else if (key == 123) //to the left
    {
        //img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x + 64, cub->player->y); 
        //cub->player->x += 64;
        double oldDirX = cub->player->dirx;
        cub->player->dirx = cub->player->dirx * cos(cub->player->rotSpeed) - cub->player->diry * sin(cub->player->rotSpeed); //rotspeed
        cub->player->diry = oldDirX * sin(cub->player->rotSpeed) + cub->player->diry * cos(cub->player->rotSpeed);
        double oldPlaneX = cub->player->planeX;
        cub->player->planeX = cub->player->planeX * cos(cub->player->rotSpeed) - cub->player->planeY * sin(cub->player->rotSpeed);
        cub->player->planeY = oldPlaneX * sin(cub->player->rotSpeed) + cub->player->planeY * cos(cub->player->rotSpeed);
        /* cub->player->a += 0.1;
        if (cub->player->a > 2 * PI)
            cub->player->a -= 2 * PI;
        cub->player->dirx = cos(cub->player->a) * 5;
        cub->player->diry = sin(cub->player->a) * 5; */
    }
    return (0);
}

void    insert_map(t_map *map, t_cub3d *cub)
{
    (void)map;
    /* void    *img;
    int     width;
    int     i;
    int     j;

    j = -1;
    width = 64;
    while(map->map[++j])
    {
        i = -1;
        while(map->map[j][++i])
        {
            if (map->map[j][i] == '1')
            {
                img = mlx_xpm_file_to_image(cub->mlx, "pics/colorstone.xpm", &width, &width);
                mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, 64 * i, 64 * j);
            }
            else if (map->map[j][i] == '0')
            {
                img = mlx_xpm_file_to_image(cub->mlx, "pics/a.xpm", &width, &width);
                mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, 64 * i, 64 * j);
            }
            else if (map->map[j][i] == 'N')
            {
                img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
                //cub->player->x = 64*i;
                //cub->player->y = 64*j;
                //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, 64 * i, 64 * j);
                cub->player->x = i;
                printf("x: %d\n", cub->player->x);
                cub->player->y = j;
                printf("x: %d\n", cub->player->y);
            }
        }
    } */
    //vectors(cub);
    mlx_key_hook(cub->mlx_win, move, cub);
}
