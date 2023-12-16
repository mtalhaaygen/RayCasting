/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:23 by msaritas          #+#    #+#             */
/*   Updated: 2023/12/16 10:29:10 by msaritas         ###   ########.fr       */
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

	dst = txt.addr + (y * txt.sizeline + x * (txt.bpp / 8));
	return (*(unsigned int *)dst);
}

int	decide_color(t_cub3d *cub, int side, int tex_y)
{
	int	color;

	color = 0;
	if (side == 0 && cub->rays->ray_dir_x > 0)
		color = get_color(cub->txt[2], cub->player->tex_x, tex_y);
	else if (side == 0 && cub->rays->ray_dir_x < 0)
		color = get_color(cub->txt[3], cub->player->tex_x, tex_y);
	else if (side == 1 && cub->rays->ray_dir_y > 0)
		color = get_color(cub->txt[0], cub->player->tex_x, tex_y);
	else if (side == 1 && cub->rays->ray_dir_y < 0)
		color = get_color(cub->txt[1], cub->player->tex_x, tex_y);
	return (color);
}

void	put_pixels(t_cub3d *cub, int x, int side)
{
	int	y;
	int	tex_y;
	int	color;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < cub->rays->draw_start)
			put_px_img(cub, x, y, cub->map->c_color);
		else if (y >= cub->rays->draw_start && y <= cub->rays->draw_end)
		{
			tex_y = (int)cub->player->tex_pos & (64 - 1);
			cub->player->tex_pos += cub->player->step;
			color = decide_color(cub, side, tex_y);
			put_px_img(cub, x, y, color);
		}
		else
			put_px_img(cub, x, y, cub->map->f_color);
	}
}

void	if_not_img(t_cub3d *cub)
{
	if (open(cub->map->no, O_RDONLY) == -1)
		print_err("Error: ", "path to north image is not valid");
	else if (open(cub->map->so, O_RDONLY) == -1)
		print_err("Error: ", "path to south image is not valid");
	else if (open(cub->map->we, O_RDONLY) == -1)
		print_err("Error: ", "path to west image is not valid");
	else if (open(cub->map->ea, O_RDONLY) == -1)
		print_err("Error: ", "path to east image is not valid");
}
