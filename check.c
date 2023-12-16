/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:05:21 by maygen            #+#    #+#             */
/*   Updated: 2023/12/16 11:10:23 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_str_new(int size, char c)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		print_err("Error ft_str_new", NULL);
	i = 0;
	while (i < size)
	{
		str[i] = c;
		i++;
	}
	str[i - 1] = '\n';
	str[i] = 0;
	return (str);
}

void	check_wall_end(t_map	*map)
{
	char	*ptr;
	int		i;

	i = -1;
	while (map->map[++i])
	{
		if (map->map_width > (int)ft_strlen(map->map[i]))
		{
			if (map->map[i][ft_strlen(map->map[i]) - 1] == '\n')
				map->map[i][ft_strlen(map->map[i]) - 1] = '\0';
			ptr = ft_str_new(map->map_width - \
				ft_strlen(map->map[i]), ' ');
			map->map[i] = ft_strjoin(map->map[i], ptr);
			free(ptr);
		}
	}
}

void	check_same(t_map	*map)
{
	filename_extension(map->no + 1, ".xpm");
	filename_extension(map->so + 1, ".xpm");
	filename_extension(map->we + 1, ".xpm");
	filename_extension(map->ea + 1, ".xpm");
	if (ft_strcmp(map->no, map->so) == 0)
		print_err("Error check_same", "North and South texture are SAME");
	if (ft_strcmp(map->no, map->ea) == 0)
		print_err("Error check_same", "North and East texture are SAME");
	if (ft_strcmp(map->no, map->we) == 0)
		print_err("Error check_same", "North and West texture are SAME");
	if (ft_strcmp(map->so, map->ea) == 0)
		print_err("Error check_same", "South and East texture are SAME");
	if (ft_strcmp(map->so, map->we) == 0)
		print_err("Error check_same", "South and West texture are SAME");
	if (ft_strcmp(map->ea, map->we) == 0)
		print_err("Error check_same", "East and West texture are SAME");
}

void	check_wall_space(t_map	*map, int i, int j)
{
	if (i < map->map_height - 1 && map->map[i + 1][j])
		if (map->map[i + 1][j] != ' ' && \
			map->map[i + 1][j] != '1' && \
				map->map[i + 1][j] != '\n')
			print_err("Error check_wall", NULL);
	if (i > 0 && map->map[i - 1][j])
		if (map->map[i - 1][j] != ' ' && \
			map->map[i - 1][j] != '1' && \
				map->map[i - 1][j] != '\n')
			print_err("1 Error check_wall", NULL);
	if (map->map[i][j + 1])
		if (map->map[i][j + 1] != ' ' && \
			map->map[i][j + 1] != '1' && \
				map->map[i][j + 1] != '\n')
			print_err("2 Error check_wall", NULL);
	if (j > 0 && map->map[i][j - 1])
		if (map->map[i][j - 1] != ' ' && \
			map->map[i][j - 1] != '1' && \
				map->map[i][j - 1] != '\n')
			print_err("3 Error check_wall", NULL);
}

void	check_wall(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	check_wall_end(map);
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == '1' || map->map[i][j] == '0' || \
				map->map[i][j] == 'N' || map->map[i][j] == 'S' || \
				map->map[i][j] == 'W' || map->map[i][j] == 'E' || \
					map->map[i][j] == '\n')
				continue ;
			else if (map->map[i][j] == ' ')
				check_wall_space(map, i, j);
			else
				print_err("Error check_wall map invalid character", NULL);
		}
	}
}
