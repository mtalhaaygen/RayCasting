/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:19:14 by maygen            #+#    #+#             */
/*   Updated: 2023/12/16 11:51:49 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_reader(t_map *map)
{
	char	*tmp;
	int		fd;

	tmp = ft_strdup("");
	fd = open(map->map_name, O_RDONLY);
	if (fd == -1)
		print_err("open error", NULL);
	map->cub_height = 0;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (map->cub_height == 0 && tmp == NULL)
			print_err("Empty map", map->map_name);
		map->cub_height++;
	}
	free(tmp);
	close(fd);
	fd = open(map->map_name, O_RDONLY);
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

void	fill_the_textures(t_map *map, char *tmp)
{
	if (!map->no && ft_strncmp(tmp, "NO", 2) == 0)
		map->no = find_texture(tmp);
	else if (!map->so && ft_strncmp(tmp, "SO", 2) == 0)
		map->so = find_texture(tmp);
	else if (!map->we && ft_strncmp(tmp, "WE", 2) == 0)
		map->we = find_texture(tmp);
	else if (!map->ea && ft_strncmp(tmp, "EA", 2) == 0)
		map->ea = find_texture(tmp);
	else if (map->f_color < 0 && ft_strncmp(tmp, "F", 1) == 0)
		map->f_color = color_assigment(tmp);
	else if (map->c_color < 0 && ft_strncmp(tmp, "C", 1) == 0)
		map->c_color = color_assigment(tmp);
	else
		print_err("FLOOR_READER cub invalid line =>", tmp);
}

int	floor_read(t_map	*map, int fd)
{
	char	*tmp;
	char	*fre;
	int		i;

	i = -1;
	while (++i < map->cub_height)
	{
		fre = get_next_line(fd);
		if (ft_strcmp(fre, "\n") != 0)
		{
			tmp = ft_trim(fre);
			fill_the_textures(map, tmp);
		}
		free(fre);
		if (map->no && map->so && map->we && map->ea && \
					map->f_color >= 0 && map->c_color >= 0)
			break ;
	}
	return (i);
}

void	map_fill(char **gv, t_map *map)
{
	int	i;
	int	fd;

	filename_extension(gv[1], ".cub");
	map->map_name = ft_strdup(gv[1]);
	map_null(map);
	fd = map_reader(map);
	i = floor_read(map, fd);
	map_reader2(map, fd, i);
	map_end(fd);
	check_same(map);
	check_wall(map);
	check_maps_border(map);
}
