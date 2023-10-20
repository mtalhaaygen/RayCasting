/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/10/20 20:16:33 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_null(t_map	*map_value)
{
	map_value->c_color = NULL;
	map_value->f_color = NULL;
	map_value->no = NULL;
	map_value->so = NULL;
	map_value->we = NULL;
	map_value->ea = NULL;
}

// char	*ft_trim(char	*s1)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(s1) - 1;
// 	while (s1[i] && (s1[i] == 32 || s1[i] == 9)) // vertical tab => 9
// 		i++;
// 	while (s1[len] && (s1[len] == 32 || s1[len] == 9))
// 		len--;
//     s1[len + 1] = '\0';
// 	return (s1 + i);
// }

void	map_reader2(t_map	*map_value, int fd, int i)
{
	int		flag;
	char	*tmp;
	int		j;

	flag = 1;
	j = 0;
	while (i++ < map_value->map_height)
		tmp = get_next_line(fd);
}

int	floor_read(t_map	*map_value, int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i++ < map_value->map_height)
	{
		tmp = get_next_line(fd);
		if (ft_strncmp(tmp, "NO", 2) == 0)
			map_value->no = ft_strdup(tmp);
		else if (ft_strncmp(tmp, "SO", 2) == 0)
			map_value->so = ft_strdup(tmp);
		else if (ft_strncmp(tmp, "WE", 2) == 0)
			map_value->we = ft_strdup(tmp);
		else if (ft_strncmp(tmp, "EA", 2) == 0)
			map_value->ea = ft_strdup(tmp);
		else if (ft_strncmp(tmp, "F", 1) == 0)
			map_value->f_color = ft_strdup(tmp);
		else if (ft_strncmp(tmp, "C", 1) == 0)
			map_value->c_color = ft_strdup(tmp);
		free(tmp);
		if (map_value->no && map_value->so && map_value->we && map_value->ea && map_value->c_color && map_value->f_color)
			break ;
	}
	return (i);
}

void	map_reader(t_map	*map_value)
{
	char	*tmp;
	int		fd;
	int		i;

	tmp = ft_strdup("nane");
	fd = open(map_value->map_name, O_RDONLY);
	if (fd == -1)
		print_err("open error", NULL);
	map_value->map_height = 0;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		map_value->map_height++;
	}
	free(tmp);
	map_value->map = malloc(sizeof(char *) * map_value->map_height);
	close(fd);
	fd = open(map_value->map_name, O_RDONLY);
	if (fd == -1)
		print_err("open error", NULL);
	i = floor_read(map_value, fd);
	map_reader2(map_value, fd, i);
}

int	print_err(char *str, char *arg)
{
	if (!arg)
		printf("%s\n", str);
	else
		printf("%s %s\n", str, arg);
	exit(1);
}

int	filename_extension(char *str)
{
	char	*extension;

	extension = ft_strchr(str, '.');
	if (ft_strcmp(extension, ".cub"))
		print_err("file extension not valid", NULL);
	return (0);
}

 // tüm haritayı okuyup structdaki verileri dolduracak
	// player bir tane olacak , W- E-N-S den bir tane olacak
	// haritanın içinde space olabilir, ama tab olamaz, tüm spaceleri 1 yap
	// wall_check(map_value->map); // map duvarlarını kontrol edecek
t_map	*map_check(char **gv, t_map *map_value)
{
	map_value = malloc(sizeof(t_map));
	filename_extension(gv[1]);
	map_value->map_name = ft_strdup(gv[1]);
	map_null(map_value);
	map_reader(map_value);
	return (map_value);
}

int	main(int gc, char **gv)
{
	t_map	*map_value;

	map_value = NULL;
	if (gc == 2)
	{
		map_value = map_check(gv, map_value);
		printf("no:*%s*", map_value->no);
		printf("so:*%s*", map_value->so);
		printf("we:*%s*", map_value->we);
		printf("ea:*%s*", map_value->ea);
		printf("c_color:*%s*", map_value->c_color);
		printf("f_color:*%s*", map_value->f_color);
	}
	else
		return (print_err("invalid argument count", NULL));
	// system("leaks cub3d");
}
