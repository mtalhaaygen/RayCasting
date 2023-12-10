/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:01:17 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/10 19:23:01 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    turn_to_right(t_cub3d *cub)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = cub->player->dirx;
    oldPlaneX = cub->player->planeX;
    cub->player->dirx = cub->player->dirx * cos(cub->player->rotSpeed) -
							cub->player->diry * sin(cub->player->rotSpeed);
    cub->player->diry = oldDirX * sin(cub->player->rotSpeed) +
							cub->player->diry * cos(cub->player->rotSpeed);
    cub->player->planeX = cub->player->planeX * cos(cub->player->rotSpeed) -
							cub->player->planeY * sin(cub->player->rotSpeed);
    cub->player->planeY = oldPlaneX * sin(cub->player->rotSpeed) +
							cub->player->planeY * cos(cub->player->rotSpeed);
}

int move(t_cub3d *cub)
{
    if (cub->map->keys[0]) //w
        go_straight(cub);
    else if (cub->map->keys[1])//a
        go_left(cub);
    else if (cub->map->keys[2])//s
        go_back(cub);
    else if (cub->map->keys[3])//d
        go_right(cub);
    else if (cub->map->keys[4]) //to the left
        turn_to_left(cub);
    else if (cub->map->keys[5]) //to the right
        turn_to_right(cub);
    else if (cub->map->keys[6]) //esc
        destroy(cub);
    return (0);
}

int keyPress(int key, t_cub3d *cub)
{
    if (key == 13) //w
        cub->map->keys[0] = 1;
    else if (key == 0)//a
        cub->map->keys[1] = 1;
    else if (key == 1)//s
        cub->map->keys[2] = 1;
    else if (key == 2)//d
        cub->map->keys[3] = 1;
    else if (key == 123) //to the left
        cub->map->keys[4] = 1;
    else if (key == 124) //to the right
        cub->map->keys[5] = 1;
    else if (key == 53) //esc
        cub->map->keys[6] = 1;
    return (0);
}

int keyRelease(int key, t_cub3d *cub)
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
    else if (key == 53) //esc, seg veriyor
        cub->map->keys[6] = 0;
    return (0);
}

