/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaritas <msaritas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:05:21 by maygen            #+#    #+#             */
/*   Updated: 2023/12/14 20:21:53 by msaritas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strnew(int size, char c)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		print_err("Error ft_strnew", NULL);
	i = 0;
	while (i < size)
	{
		str[i] = c;
		i++;
	}
	str[i - 1] = '\n'; // mapin satır sonlarına \n karakteri eklemek için
	str[i] = 0;
	return (str);
}

void	check_wall_end(t_map	*map_value)
{
	// haritada tüm satırları aynı genişliğe ulaştırmak için tüm satırların sonuna yeteri kadar space at
	char	*ptr;
	int		i;

	i = -1;
	while (map_value->map[++i])
	{
		if (map_value->map_width > (int)ft_strlen(map_value->map[i]))
		{
			if (map_value->map[i][ft_strlen(map_value->map[i]) - 1] == '\n')
				map_value->map[i][ft_strlen(map_value->map[i]) - 1] = '\0'; // \n karakterini sil
			ptr = ft_strnew(map_value->map_width - ft_strlen(map_value->map[i]), ' ');
			map_value->map[i] = ft_strjoin(map_value->map[i], ptr);
			free(ptr);
		}
	}
}

void	check_same(t_map	*map_value)
{
	filename_extension(map_value->no + 1, ".xpm"); // +1 ile . karaterini atlıyorum
	filename_extension(map_value->so + 1, ".xpm");
	filename_extension(map_value->we + 1, ".xpm");
	filename_extension(map_value->ea + 1, ".xpm");
	if (ft_strcmp(map_value->no, map_value->so) == 0)
		print_err("Error check_same", "North and South texture are SAME");
	if (ft_strcmp(map_value->no, map_value->ea) == 0)
		print_err("Error check_same", "North and East texture are SAME");
	if (ft_strcmp(map_value->no, map_value->we) == 0)
		print_err("Error check_same", "North and West texture are SAME");
	if (ft_strcmp(map_value->so, map_value->ea) == 0)
		print_err("Error check_same", "South and East texture are SAME");
	if (ft_strcmp(map_value->so, map_value->we) == 0)
		print_err("Error check_same", "South and West texture are SAME");
	if (ft_strcmp(map_value->ea, map_value->we) == 0)
		print_err("Error check_same", "East and West texture are SAME");
}

void	check_wall(t_map	*map_value)
{
	int	i;
	int	j;

	i = -1;
	check_wall_end(map_value);
	while (map_value->map[++i])
	{
		j = -1;
		while (map_value->map[i][++j])
		{
			if (map_value->map[i][j] == '1' || map_value->map[i][j] == '0' || map_value->map[i][j] == 'N' || map_value->map[i][j] == 'S' || map_value->map[i][j] == 'W' || map_value->map[i][j] == 'E' || map_value->map[i][j] == '\n')
				continue;
			else if (map_value->map[i][j] == ' ')
			{
				if (i < map_value->map_height - 1 && map_value->map[i + 1][j])
					if (map_value->map[i + 1][j] != ' ' && map_value->map[i + 1][j] != '1' && map_value->map[i + 1][j] != '\n')
						print_err("Error check_wall", NULL);
				if (i > 0 && map_value->map[i - 1][j])
					if (map_value->map[i - 1][j] != ' ' && map_value->map[i - 1][j] != '1' && map_value->map[i - 1][j] != '\n')
						print_err("1 Error check_wall", NULL);
				if (map_value->map[i][j + 1])
					if (map_value->map[i][j + 1] != ' ' && map_value->map[i][j + 1] != '1' && map_value->map[i][j + 1] != '\n')
						print_err("2 Error check_wall", NULL);
				if (j > 0 && map_value->map[i][j - 1])
					if (map_value->map[i][j - 1] != ' ' && map_value->map[i][j - 1] != '1' && map_value->map[i][j - 1] != '\n')
						print_err("3 Error check_wall", NULL);
			}
			else
				print_err("Error check_wall map have a invalid character ", NULL);
		}
	}
}
