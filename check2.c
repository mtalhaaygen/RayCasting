/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:42:54 by maygen            #+#    #+#             */
/*   Updated: 2023/12/21 17:09:10 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	comma_count(char *tmp, int comma)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (tmp[++i])
		if (tmp[i] == comma)
			count++;
	return (count);
}

void	check_maps_border(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->map_width - 1 && map->map[0][i] && \
		map->map[map->map_height - 1][i])
	{
		if (map->map[0][i] != '1' && map->map[0][i] != ' ' && \
			map->map[0][i] != '\n')
			print_err("Error first line of the map", map->map[0]);
		if (map->map[map->map_height - 1][i] != '1' && \
				map->map[map->map_height - 1][i] != ' ' && \
					map->map[map->map_height - 1][i] != '\n')
			print_err("Error last line of the map", \
				map->map[map->map_height - 1]);
	}
}

int	is_number(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_trim(str);
	while (tmp[++i])
		if (!(tmp[i] >= '0' && tmp[i] <= '9'))
			return (1);
	return (0);
}

void	map_null(t_map	*map)
{
	map->c_color = -1;
	map->f_color = -1;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
}
