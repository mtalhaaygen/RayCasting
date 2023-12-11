/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:23 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/11 20:19:52 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_px_img(t_cub3d *f, int x, int y, int color)
{
	char	*dst;

	dst = f->img.addr + (y * f->img.sizeline + x * (f->img.bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color(t_img txt, int x, int y)
{
	char	*dst;

	dst = txt.addr + (y *  txt.sizeline + x * (txt.bpp / 8));
	return (*(unsigned int *)dst);
}

void    put_pixels(t_cub3d *cub, int x, int side)
{
    int y;
    int texY;
    int color;

    y = -1;
    while (++y < HEIGHT)
    {
        if (y < cub->rays->drawStart)
            put_px_img(cub, x, y, cub->map->c_color);
        else if (y >= cub->rays->drawStart && y <= cub->rays->drawEnd)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            texY = (int)cub->player->texPos & (64 - 1);
            cub->player->texPos += cub->player->step;
            if (side == 0 && cub->rays->rayDirX > 0)
                color = get_color(cub->txt[0], cub->player->texX, texY);
            else if (side == 0 && cub->rays->rayDirX < 0)
                color = get_color(cub->txt[1], cub->player->texX, texY);
            else if (side == 1 && cub->rays->rayDirY > 0)
                color = get_color(cub->txt[2], cub->player->texX, texY);
            else if (side == 1 && cub->rays->rayDirY < 0)
                color = get_color(cub->txt[3], cub->player->texX, texY);
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            /* if(side == 1)
                color = (color >> 1) & 8355711; */
            put_px_img(cub, x, y, color);
        }
        else
            put_px_img(cub, x, y, cub->map->f_color);
    }
}

void    fill_textures(t_cub3d *cub)
{
	cub->txt[0].img = mlx_xpm_file_to_image(cub->mlx, cub->map->no,
        &cub->txt[0].w, &cub->txt[0].h);
	cub->txt[1].img = mlx_xpm_file_to_image(cub->mlx, cub->map->so,
        &cub->txt[1].w, &cub->txt[1].h);
	cub->txt[2].img = mlx_xpm_file_to_image(cub->mlx, cub->map->we,
        &cub->txt[2].w, &cub->txt[2].h);
	cub->txt[3].img = mlx_xpm_file_to_image(cub->mlx, cub->map->ea,
        &cub->txt[3].w, &cub->txt[3].h);
    cub->txt[0].addr = mlx_get_data_addr(cub->txt[0].img, &cub->txt[0].bpp,
        &cub->txt[0].sizeline, &cub->txt[0].endian);
    cub->txt[1].addr = mlx_get_data_addr(cub->txt[1].img, &cub->txt[1].bpp,
        &cub->txt[1].sizeline, &cub->txt[1].endian);
    cub->txt[2].addr = mlx_get_data_addr(cub->txt[2].img, &cub->txt[2].bpp,
        &cub->txt[2].sizeline, &cub->txt[2].endian);
    cub->txt[3].addr = mlx_get_data_addr(cub->txt[3].img, &cub->txt[3].bpp,
        &cub->txt[3].sizeline, &cub->txt[3].endian);
}
