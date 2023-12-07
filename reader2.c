/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:21:19 by maygen            #+#    #+#             */
/*   Updated: 2023/12/02 15:41:38 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_assigment(char	*tmp)
{
	int		i;
	char	**dbl_arr;
	int		x[3];
	int		color;

	dbl_arr = ft_split(tmp + 1, ','); // tmp + 1 yaptım çünkü satırdaki F yada C harfini atlamak için
	i = -1;
	while (dbl_arr[++i])
	{
		x[i] = ft_atoi(dbl_arr[i]);
		if (x[i] < 0 || x[i] > 255)
			print_err("hatalı renk kodu ", NULL);
		free(dbl_arr[i]);
	}
	free(dbl_arr);
	if (i != 3)
		print_err("hatalı renk kodu ", NULL);
	color = (x[0] << 16) + (x[1] << 8) + x[2];
	// color = (x[0] * 65536) + (x[1] * 256) + x[2];
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

void	map_reader2(t_map	*map_value, int fd, int i)
{
	char	*tmp;
	int		j;
	int		map_index;

	tmp = get_next_line(fd);
	while (ft_strcmp(tmp, "\n") == 0)
	{
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	map_value->map_height = map_value->cub_height - i;
	map_value->map = malloc(sizeof(char *) * map_value->map_height + 1);
	map_value->map[map_value->map_height] = NULL;
	j = 0;
	map_index = -1;
	while (++map_index < map_value->map_height - 1)
	{
		j = 0;
		while (tmp[j] && tmp[j] == 32)
		{
			tmp[j] = '1';
			j++;
		}
		if (tmp[j] == '1')
		{
			map_value->map[map_index] = ft_strdup(tmp);
			free(tmp);
			tmp = get_next_line(fd);
		}
		else if (ft_strcmp(tmp, "\n") != 0)
			print_err("2 MAP_READER2 cub invalid line =>", tmp);
		else
			break;
	}
}