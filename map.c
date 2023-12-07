/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:23:26 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/07 20:12:32 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    movement(t_cub3d *cub, int direct)
{
    float   dist;
    float   dx;
    float   dy;
    float   angle;

    angle = cub->view + direct * PI / 2;
    //dx = LINEAR_STEP * cos(angle);
    dx = 1 * cos(angle);
    dy = 1 * sin(angle);
    if (dy > 0)
        dist = ft_ray(cub, PI / 2);
    else
        dist = ft_ray(cub, -PI / 2);
    if (dist * dist < dy * dy)
        dy = 0.0f;
    dist = ft_ray(cub, angle);
    if (dist * dist < dy * dy + dx * dx)
        if (dy * dx != 0)
            dy = 0.0f;
    cub->player->x += dx;
    cub->player->y -= dy;
}
int move(int key, t_cub3d *cub)
{
    //void *img;
    int width;

    width = 64;
    printf("key:%d\n", key);
    if (key == 13) //w
    {
        movement(cub, 0);
        /* img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x, cub->player->y - 64); 
        cub->player->y -= 64; */
        //cub->player->y--;
        //cub->player->y += cub->player->diry;
        //cub->player->x += cub->player->dirx;
        //if(!cub->map->map[(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)][(int)( cub->player->y)]) cub->player->x += cub->player->dirx * cub->player->moveSpeed;
        //if(!cub->map->map[(int)(cub->player->x)][(int)(cub->player->y + cub->player->diry * cub->player->moveSpeed)]) cub->player->y += cub->player->diry * cub->player->moveSpeed;
    }   
    else if (key == 0)//a
    {
        movement(cub, 3);
        /* img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x - 64, cub->player->y); 
        cub->player->x -= 64; */
        //cub->player->x--;
        //cub->player->x += cub->player->dirx;
        //if(!cub->map->map[(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)][(int)( cub->player->y)]) cub->player->x += cub->player->dirx * cub->player->moveSpeed;
        
    }
    else if (key == 1)//s
    {
        movement(cub, 2);
        
        /* img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x, cub->player->y + 64); 
        cub->player->y += 64; */
        //cub->player->y++;
        /* cub->player->y -= cub->player->diry;
        cub->player->x -= cub->player->dirx; */
        //if(!cub->map->map[(int)(cub->player->x - cub->player->dirx * cub->player->moveSpeed)][(int)(cub->player->y)]) cub->player->x -= cub->player->dirx * cub->player->moveSpeed;
        //if(!cub->map->map[(int)(cub->player->x)][(int)(cub->player->y - cub->player->diry * cub->player->moveSpeed)]) cub->player->y -= cub->player->diry * cub->player->moveSpeed;   
    }
    else if (key == 2)//d
    {
        movement(cub, 1);
        //img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x + 64, cub->player->y); 
        //cub->player->x += 64;
        //cub->player->x++;
        //cub->player->x -= cub->player->dirx;
        //if(!cub->map->map[(int)(cub->player->x + cub->player->dirx * cub->player->moveSpeed)][(int)( cub->player->y)]) cub->player->x -= cub->player->dirx * cub->player->moveSpeed;
    }
    else if (key == 124) //to the right
    {
        //img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x + 64, cub->player->y); 
        //cub->player->x += 64;
        //printf("heyy\n");
/*         double oldDirX = cub->player->dirx;
        cub->player->dirx = cub->player->dirx * cos(-cub->player->rotSpeed) - cub->player->diry * sin(-cub->player->rotSpeed); //-rotspeed
        cub->player->diry = oldDirX * sin(-cub->player->rotSpeed) + cub->player->diry * cos(-cub->player->rotSpeed);
        double oldPlaneX = cub->player->planeX;
        cub->player->planeX = cub->player->planeX * cos(-cub->player->rotSpeed) - cub->player->planeY * sin(-cub->player->rotSpeed);
        cub->player->planeY = oldPlaneX * sin(-cub->player->rotSpeed) + cub->player->planeY * cos(-cub->player->rotSpeed); */
        /*cub->player->a -= 0.1;
        if (cub->player->a < 0)
            cub->player->a += 2 * PI;
        cub->player->dirx = cos(cub->player->a) * 5;
        cub->player->diry = sin(cub->player->a) * 5; */
        //cub->view += ANGLE_STEP * PI;
        cub->view += 0.02f * PI;
    }
    else if (key == 123) //to the left
    {
        //img = mlx_xpm_file_to_image(cub->mlx, "pics/b.xpm", &width, &width);
        //mlx_put_image_to_window(cub->mlx, cub->mlx_win, img, cub->player->x + 64, cub->player->y); 
        //cub->player->x += 64;
        /* double oldDirX = cub->player->dirx;
        cub->player->dirx = cub->player->dirx * cos(cub->player->rotSpeed) - cub->player->diry * sin(cub->player->rotSpeed); //rotspeed
        cub->player->diry = oldDirX * sin(cub->player->rotSpeed) + cub->player->diry * cos(cub->player->rotSpeed);
        double oldPlaneX = cub->player->planeX;
        cub->player->planeX = cub->player->planeX * cos(cub->player->rotSpeed) - cub->player->planeY * sin(cub->player->rotSpeed);
        cub->player->planeY = oldPlaneX * sin(cub->player->rotSpeed) + cub->player->planeY * cos(cub->player->rotSpeed); */
        /* cub->player->a += 0.1;
        if (cub->player->a > 2 * PI)
            cub->player->a -= 2 * PI;
        cub->player->dirx = cos(cub->player->a) * 5;
        cub->player->diry = sin(cub->player->a) * 5; */
        //cub->view -= ANGLE_STEP * PI;
        cub->view -= 0.02f * PI;
    }
    return (0);
}

void    ft_ray_initial_calc(t_cub3d *cub, t_ray *r, float v)
{
    r->dx = cos(v);
    r->dy = -sin(v);
    r->sx = 1;
    if (r->dx < 0)
        r->sx = -1;
    r->sy = 1;
    if (r->dy < 0)
        r->sy = -1;
    r->vert_x = (int) cub->player->x;
    if (r->sx > 0)
        r->vert_x += 1.0f;
    r->hor_y = (int) cub->player->y;
    if (r->sy > 0)
        r->hor_y += 1.0f;
}

void    ft_ray_next_step_calc(t_cub3d *cub, t_ray *r)
{
    if (r->sx != 0)
    {
        r->vert_y = cub->player->y + r->dy / r->dx * (r->vert_x - cub->player->x);
        r->vert_dist = sqrt(pow(cub->player->x - r->vert_x, 2.0) + pow(cub->player->y - r->vert_y, 2.0));
        r->vert_w = r->vert_y - (int) r->vert_y;
        if (r->sx > 0)
            r->vert_w = 1 - r->vert_w;
    }
    else
        r->vert_dist = INFINITY;
    if (r->sy != 0)
    {
        r->hor_x = cub->player->x + r->dx / r->dy * (r->hor_y - cub->player->y);
        r->hor_dist = sqrt(pow(cub->player->x - r->hor_x, 2.0) + pow(cub->player->y - r->hor_y, 2.0));
        r->hor_w = r->hor_x - (int) r->hor_x;
        if (r->sy < 0)
            r->hor_w = 1 - r->hor_w;
    }
    else
        r->hor_dist = INFINITY;
}

float    ft_save_color(t_cub3d *cub, float dist, int color_idx, float w)
{
    cub->txt_idx = color_idx;
    cub->txt_w = w;
    return (dist);
}

float ft_ray(t_cub3d *cub, float v)
{

    ft_ray_initial_calc(cub, &cub->ray, v);
    while(1)
    {
        ft_ray_next_step_calc(cub, &cub->ray);
        if (cub->ray.vert_dist < cub->ray.hor_dist)
        {
            if (cub->map->map[(int)cub->ray.vert_y][(int)cub->ray.vert_x + (cub->ray.sx - 1) / 2] == '1')
                return (ft_save_color(cub, cub->ray.vert_dist, cub->ray.sx + 1, cub->ray.vert_w));
            else
                cub->ray.vert_x += cub->ray.sx;
        }
        else
        {
            if (cub->map->map[(int)cub->ray.hor_y + (cub->ray.sy - 1) / 2][(int)cub->ray.hor_x] == '1')
                return (ft_save_color(cub, cub->ray.hor_dist, cub->ray.sy + 2, cub->ray.hor_w));
            else
                cub->ray.hor_y += cub->ray.sy;
        }
    }
    // kestiği nokta float tek bir nokta mı olacak ya x,y gibi çift değer olmalı
}

void    ft_line(t_cub3d *cub, int w, float dist)
{
    unsigned int *dst;
    unsigned int *src;
    unsigned int h;
    float       src_f;
    float       d_shift;

    h = (float) 600 / dist;
    src_f = 0.0f;
    d_shift = (float) cub->txt[cub->txt_idx].height / h; // game->txt[game->txt_idx].height ?
    if (h > 600)
    {
        src_f = 0.5f * (h - 600) / h * cub->txt[cub->txt_idx].height;
        h = 600;
    }
    src = (unsigned int *) cub->txt[cub->txt_idx].addr;
    src += (int)((float) cub->txt_w * cub->txt[cub->txt_idx].width);
    dst = (unsigned int *) cub->img.addr + w + (600 - h) / 2 * 600;
    while(h-- > 0)
    {
        //*dst = *(src + ((int)src_f) * cub->txt[cub->txt_idx].width);
        *dst = cub->txt_idx * 255 + (1 - cub->txt_idx) * (255 << 8);
        dst += 800;
        src_f += d_shift;
    }
}

void    raycasting(t_cub3d *cub)
{
    int     x;
    float   dv;
    float   v;

    //v = game->view - FOV / 2;
    v = cub->view - 0.01 / 2;
    //dv = FOV / (WINDOW_W - 1);
    dv = 0.01 / (800 - 1);

    x = -1;
    while(++x < 800)
    {
        ft_line(cub, x, ft_ray(cub, v) * cos(10.5 - v));
        ft_line(cub, x, ft_ray(cub, v));
        v += dv;
    }
}

/* int    vectors(t_cub3d *cub)
{
    int     x;
    int     mapx;
    int     mapy;
    int     stepX;
    int     stepY;
    int     hit; //was there a wall hit?
    int     side; //was a NS or a EW wall hit?
    //double planeX;
    //double planeY;
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
    
    cub->player->planeX = 0;
    cub->player->planeY = 0.66;
    time = 0;
    oldtime = 0;
    hit = 0;
    cub->player->dirx = 0.0;
    cub->player->diry = 0.0;
    
    x = -1;
    while(++x < 800)
    {
        cameraX = 2 * x / (double)(800 - 1);
        rayDirX = cub->player->dirx + cub->player->planeX * cameraX;
        rayDirY = cub->player->diry + cub->player->planeY * cameraX;
        // her turda mapx mapy değerleri player ın konumunu tutuyor
        mapx = (int)cub->player->x;
        mapy = (int)cub->player->y;
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
        //if (perpWallDist != 0) {
            lineHeight = (int)(600 / perpWallDist);
            drawStart = -lineHeight / 2 + 600 / 2;
            drawEnd = lineHeight / 2 + 600 / 2;

            if (drawStart < 0) drawStart = 0;
            if (drawEnd >= 600) drawEnd = 600 - 1;

            int color;

            //printf("%c - ", cub->map->map[mapx][mapy]);
            //printf("*%d-%d* / ", mapx, mapy);
            if (cub->map->map[mapx][mapy] == '1')
            {
                printf("aaa\n");
                color = 0xFFFF00; // yellow
            }
            else if (cub->map->map[mapx][mapy] == '0')
                color = 0xFF0000;// red

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
        //}
    }

    cub->player->moveSpeed = 0.06;
    cub->player->rotSpeed = 0.04;
    return (0);
} */


/* void    insert_map(t_map *map, t_cub3d *cub)
{
    (void)map;
     void    *img;
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
    }
    //vectors(cub);
} */

void    ceiling_and_floor(t_cub3d *cub)
{
    unsigned int *addr;
    unsigned int i;
    unsigned int j;
    
    addr = (unsigned int *) cub->img.addr;
    i = 800 * 600 / 2 + 1;
    j = i;
    while(--i > 0)
        *addr++ = cub->map->c_color;
    while(--j > 0)
        *addr++ = cub->map->f_color;
}

void	draw(t_cub3d *cub)
{
    cub->img.img = mlx_new_image(cub->mlx, 800, 600);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, &cub->img.sizeline, &cub->img.endian);
    ceiling_and_floor(cub);
    raycasting(cub);
    //mlx_loop_hook(cub->mlx, &vectors, cub);
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img.img, 0, 0);
    mlx_destroy_image(cub->mlx, cub->img.img);
}