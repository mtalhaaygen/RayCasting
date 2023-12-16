/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:21:19 by maygen            #+#    #+#             */
/*   Updated: 2023/12/16 10:04:03 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_assigment(char	*tmp)
{
	int		i;
	char	**dbl_arr;
	int		x[3];
	int		color;

	dbl_arr = ft_split(tmp + 1, ',');
	i = 0;
	while (dbl_arr[i])
	{
		if (is_number(dbl_arr[i]))
			print_err("Error color code invalid", dbl_arr[i]);
		x[i] = ft_atoi(dbl_arr[i]);
		if (x[i] < 0 || x[i] > 255)
			print_err("Error color code not RGB", dbl_arr[i]);
		free(dbl_arr[i]);
		i++;
	}
	free(dbl_arr);
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

int	map_reader_loop(t_map	*map_value, int fd, char **tmp, int map_index)
{
	int	j;

	j = 0;
	while ((*tmp) && (*tmp)[j] && (*tmp)[j] == 32)
		j++;
	if ((*tmp) && (*tmp)[j] == '1')
	{
		// burada tmp nin sondan bir önceki karakterinin 1 olup olmadığını kontrol edebiliriz
		if ((*tmp)[ft_strlen((*tmp)) - 2] != '1' && (*tmp)[ft_strlen((*tmp)) - 2] != ' ')
			print_err("MAP_READER2 cub invalid line =>", (*tmp));
		map_value->map[map_index] = ft_strdup((*tmp));
		if (map_value->map_width < (int)ft_strlen((*tmp)))
			map_value->map_width = ft_strlen((*tmp));
		free((*tmp));
		(*tmp) = get_next_line(fd);
	}
	else if ((*tmp) && ft_strcmp((*tmp), "\n") != 0)
		print_err("2 MAP_READER2 cub invalid line =>", (*tmp));
	else
	{
		map_value->map_height = map_index;
		map_value->map[map_index] = NULL;
		return (1);
	}
	return (0);
}

void	map_reader2(t_map	*map_value, int fd, int i)
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
	map_value->map_width = -1;
	map_value->map_height = map_value->cub_height - i;
	map_value->map = malloc(sizeof(char *) * map_value->map_height + 1);
	map_value->map[map_value->map_height] = NULL;
	map_index = -1;
	while (++map_index < map_value->map_height - 1)
		if (map_reader_loop(map_value, fd, &tmp, map_index))
			break ;
}
