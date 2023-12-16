/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:21:19 by maygen            #+#    #+#             */
/*   Updated: 2023/12/16 12:03:28 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_assigment(char	*tmp)
{
	int		i;
	char	**color_code;
	int		x[3];
	int		color;

	color_code = ft_split(tmp + 1, ',');
	i = 0;
	while (color_code[i])
	{
		if (is_number(color_code[i]))
			print_err("Error color code invalid", color_code[i]);
		x[i] = ft_atoi(color_code[i]);
		if (x[i] < 0 || x[i] > 255)
			print_err("Error color code not RGB", color_code[i]);
		free(color_code[i]);
		i++;
	}
	free(color_code);
	if (i != 3)
		print_err("Error color code not RGB", NULL);
	color = (x[0] << 16) + (x[1] << 8) + x[2];
	color = (x[0] * 65536) + (x[1] * 256) + x[2];
	return (color);
}

void	map_end(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		if (ft_strcmp(tmp, "\n") != 0)
			print_err("map_end invalid argument", NULL);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}

int	map_reader_loop(t_map	*map, int fd, char **tmp, int map_index)
{
	int	j;

	j = 0;
	while ((*tmp) && (*tmp)[j] && (*tmp)[j] == 32)
		j++;
	if ((*tmp) && (*tmp)[j] == '1')
	{
		if ((*tmp)[ft_strlen((*tmp)) - 2] != '1' &&
			(*tmp)[ft_strlen((*tmp)) - 2] != ' ')
			print_err("MAP_READER2 cub invalid line =>", (*tmp));
		map->map[map_index] = ft_strdup((*tmp));
		if (map->map_width < (int)ft_strlen((*tmp)))
			map->map_width = ft_strlen((*tmp));
		free((*tmp));
		(*tmp) = get_next_line(fd);
	}
	else if ((*tmp) && ft_strcmp((*tmp), "\n") != 0)
		print_err("2 MAP_READER2 cub invalid line =>", (*tmp));
	else
	{
		map->map_height = map_index;
		free(*tmp);
		return (1);
	}
	return (0);
}

void	map_reader2(t_map	*map, int fd, int i)
{
	char	*tmp;
	int		map_index;

	tmp = get_next_line(fd);
	while (ft_strcmp(tmp, "\n") == 0)
	{
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	map->map_width = -1;
	map->map_height = map->cub_height - i;
	map->map = malloc(sizeof(char *) * map->map_height + 1);
	map->map[map->map_height] = NULL;
	map_index = -1;
	while (++map_index < map->map_height - 1)
	{
		if (map_reader_loop(map, fd, &tmp, map_index))
		{
			map->map[map->map_height] = NULL;
			break ;
		}
	}
}
