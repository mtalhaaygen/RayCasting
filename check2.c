/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:42:54 by maygen            #+#    #+#             */
/*   Updated: 2023/12/14 18:30:04 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_maps_border(t_map *map_value)
{
	int	i;

	i = -1;
	while (++i < map_value->map_width - 1 && map_value->map[0][i] && map_value->map[map_value->map_height - 1][i])
	{
		if (map_value->map[0][i] != '1' && map_value->map[0][i] != ' ' && map_value->map[0][i] != '\n')
			print_err("Error first line of the map", map_value->map[0]);
		if (map_value->map[map_value->map_height - 1][i] != '1' && map_value->map[map_value->map_height - 1][i] != ' ' && map_value->map[map_value->map_height - 1][i] != '\n')
			print_err("Error last line of the map", map_value->map[map_value->map_height - 1]);
	}
}

int	is_number(char *str)
{
	int	i;

	i = -1;
	while (str[i] == ' ' && str[i] == 9) // sanırım tab karakteri ascii değeri 9
		i++;
	while (str[++i])
	{
		if (str[i] == ' ' || str[i] == 9)
			break;
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (1);
	}
	if (str[i + 1] == '\0')
		return (0);
	return (1);
}
