/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:42:54 by maygen            #+#    #+#             */
/*   Updated: 2023/12/15 17:31:16 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_maps_border(t_map *map_value)
{
	int	i;

	i = -1;
	while (++i < map_value->map_width - 1 && map_value->map[0][i] && \
		map_value->map[map_value->map_height - 1][i])
	{
		if (map_value->map[0][i] != '1' && map_value->map[0][i] != ' ' && \
			map_value->map[0][i] != '\n')
			print_err("Error first line of the map", map_value->map[0]);
		if (map_value->map[map_value->map_height - 1][i] != '1' && \
				map_value->map[map_value->map_height - 1][i] != ' ' && \
					map_value->map[map_value->map_height - 1][i] != '\n')
			print_err("Error last line of the map", \
				map_value->map[map_value->map_height - 1]);
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

void	map_null(t_map	*map_value)
{
	map_value->c_color = -1;
	map_value->f_color = -1;
	map_value->no = NULL;
	map_value->so = NULL;
	map_value->we = NULL;
	map_value->ea = NULL;
}
