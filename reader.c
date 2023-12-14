/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:19:14 by maygen            #+#    #+#             */
/*   Updated: 2023/12/14 20:09:15 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_null(t_map	*map_value)
{
	map_value->c_color = -1;
	map_value->f_color = -1;
	map_value->no = NULL;
	map_value->so = NULL;
	map_value->we = NULL;
	map_value->ea = NULL;
}

int	map_reader(t_map	*map_value)
{
	char	*tmp;
	int		fd;

	tmp = ft_strdup("nane");
	fd = open(map_value->map_name, O_RDONLY);
	if (fd == -1)
		print_err("open error", NULL);
	map_value->cub_height = 0;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (map_value->cub_height == 0 && tmp == NULL)
			print_err("Empty map" ,map_value->map_name);
		map_value->cub_height++;
	}
	free(tmp);
	close(fd);
	fd = open(map_value->map_name, O_RDONLY);//?
	if (fd == -1)
		print_err("open error", NULL);
	return (fd);
}

char	*find_texture(char *tmp)
{
	if (!ft_strchr(tmp, '.'))
		print_err("Invalid texture", tmp);
	return (ft_strdup(ft_strchr(tmp, '.')));
}

void fill_the_textures(t_map *map_value, char *tmp)
{
	if (!map_value->no && ft_strncmp(tmp, "NO", 2) == 0)
		map_value->no = find_texture(tmp);
	else if (!map_value->so && ft_strncmp(tmp, "SO", 2) == 0)
		map_value->so = find_texture(tmp);
	else if (!map_value->we && ft_strncmp(tmp, "WE", 2) == 0)
		map_value->we = find_texture(tmp);
	else if (!map_value->ea && ft_strncmp(tmp, "EA", 2) == 0)
		map_value->ea = find_texture(tmp);
	else if (map_value->f_color < 0 && ft_strncmp(tmp, "F", 1) == 0)
		map_value->f_color = color_assigment(tmp);
	else if (map_value->c_color < 0 && ft_strncmp(tmp, "C", 1) == 0)
		map_value->c_color = color_assigment(tmp);
	else
		print_err("FLOOR_READER cub invalid line =>", tmp);
}

int	floor_read(t_map	*map_value, int fd)
{
	char	*tmp;
	char	*fre;
	int		i;

	i = -1;
	while (++i < map_value->cub_height)
	{
		fre = get_next_line(fd);
		if (ft_strcmp(fre, "\n") != 0)
		{
			tmp = ft_trim(fre);
			fill_the_textures(map_value, tmp);
		}
		free(fre);
		if (map_value->no && map_value->so && map_value->we && map_value->ea && map_value->f_color >= 0 && map_value->c_color >= 0)
			break ;
	}
	return (i);
}

void	map_fill(char **gv, t_map *map_value)
{
	int i;
	int	fd;

	filename_extension(gv[1], ".cub");
	map_value->map_name = ft_strdup(gv[1]);
	map_null(map_value);
	fd = map_reader(map_value);
	i = floor_read(map_value, fd);
	map_reader2(map_value, fd, i);
	map_end(fd); // haritanın geri kalan kısmında herhangi bir karakter olmamalı
	check_same(map_value);
	check_wall(map_value);
	check_maps_border(map_value);
}
