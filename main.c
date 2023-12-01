/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 08:22:35 by maygen            #+#    #+#             */
/*   Updated: 2023/12/01 19:06:22 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    open_window(t_map *map)
{
	//map = malloc(sizeof(t_map));

	printf("aaaaaaa\n");
    map->mlx = mlx_init();
	printf("sdfghj\n");
    map->mlx_win = mlx_new_window(map->mlx, 1920, 1080, "a");
    mlx_loop(map->mlx);
}

int	color_assigment(char	*tmp)
{
	printf("start\n");
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
	printf("***%d - %d - %d???\n", x[0], x[1], x[2]);
	color = (x[0] << 16) + (x[1] << 8) + x[2];
	// color = (x[0] * 65536) + (x[1] * 256) + x[2];
	return (color);
}

void	map_null(t_map	**map_value)
{
	(*map_value)->c_color = 0;
	(*map_value)->f_color = 0;
	(*map_value)->no = NULL;
	(*map_value)->so = NULL;
	(*map_value)->we = NULL;
	(*map_value)->ea = NULL;
}

char	*ft_trim(char	*s1)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i] && (s1[i] == 32 || s1[i] == 9)) // vertical tab => 9
		i++;
	while (s1[len] && (s1[len] == 32 || s1[len] == 9))
		len--;
	s1[len + 1] = '\0';
	return (s1 + i);
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

void	map_reader2(t_map	**map_value, int fd, int i)
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
	(*map_value)->map_height = (*map_value)->cub_height - i;
	(*map_value)->map = malloc(sizeof(char *) * (*map_value)->map_height + 1);
	(*map_value)->map[(*map_value)->map_height] = NULL;
	j = 0;
	map_index = -1;
	while (++map_index < (*map_value)->map_height - 1)
	{
		j = 0;
		while (tmp[j] && tmp[j] == 32)
			j++;
		if (tmp[j] == '1')
		{
			(*map_value)->map[map_index] = ft_strdup(tmp);
			free(tmp);
			tmp = get_next_line(fd);
		}
		else if (ft_strcmp(tmp, "\n") != 0)
			print_err("2 MAP_READER2 cub invalid line =>", tmp);
		else
			break;
	}
}

int	floor_read(t_map	**map_value, int fd)
{
	char	*tmp;
	char	*fre;
	int		i;

	i = -1;
	while (++i < (*map_value)->cub_height)
	{
		fre = get_next_line(fd);
		if (ft_strcmp(fre, "\n") != 0)
		{
			tmp = ft_trim(fre);
			if (ft_strncmp(tmp, "NO", 2) == 0 && !(*map_value)->no)
				(*map_value)->no = ft_strdup(ft_strchr(tmp, '.'));
			else if (ft_strncmp(tmp, "SO", 2) == 0 && !(*map_value)->so)
				(*map_value)->so = ft_strdup(ft_strchr(tmp, '.'));
			else if (ft_strncmp(tmp, "WE", 2) == 0  && !(*map_value)->we)
				(*map_value)->we = ft_strdup(ft_strchr(tmp, '.'));
			else if (ft_strncmp(tmp, "EA", 2) == 0  && !(*map_value)->ea)
				(*map_value)->ea = ft_strdup(ft_strchr(tmp, '.'));
			else if (ft_strncmp(tmp, "F", 1) == 0  && !(*map_value)->f_color)
				(*map_value)->f_color = 14443773;
			else if (ft_strncmp(tmp, "C", 1) == 0  && !(*map_value)->c_color)
				(*map_value)->c_color = 14753566;
			else
				print_err("FLOOR_READER cub invalid line =>", tmp);
		}
		free(fre);
		if ((*map_value)->no && (*map_value)->so && (*map_value)->we && (*map_value)->ea && (*map_value)->c_color && (*map_value)->f_color)
			break ;
	}
	return (i);
}

int	map_reader(t_map	**map_value)
{
	char	*tmp;
	int		fd;

	tmp = ft_strdup("nane");
	fd = open((*map_value)->map_name, O_RDONLY);
	if (fd == -1)
		print_err("open error", NULL);
	(*map_value)->cub_height = 0;
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		(*map_value)->cub_height++;
	}
	free(tmp);
	close(fd);
	fd = open((*map_value)->map_name, O_RDONLY);
	if (fd == -1)
		print_err("open error", NULL);
	return (fd);
}

int	print_err(char *str, char *arg)
{
	if (!arg)
		printf("%s\n", str);
	else
		printf("%s \"%s\"\n", str, arg);
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

t_map	*map_check(char **gv, t_map *map_value)
{
	int i;
	int	fd;

	filename_extension(gv[1]);
	map_value->map_name = ft_strdup(gv[1]);
	map_null(&map_value);
	fd = map_reader(&map_value);
	i = floor_read(&map_value, fd);
	map_reader2(&map_value, fd, i);
	map_end(fd); // haritanın geri kalan kısmında herhangi bir karakter olmamalı
	//check_same(map_value);
	// check_player(map_value, )
	// check_wall
	return (map_value);
}

int	main(int gc, char **gv)
{
	// t_cub3d	*allcub;
	t_map	*map_value;

	map_value = malloc(sizeof(t_map));
	if (gc == 2)
	{
		map_value = map_check(gv, map_value);
		// printf("no:*%s\n", map_value->no);
		// printf("so:*%s\n", map_value->so);
		// printf("we:*%s\n", map_value->we);
		// printf("ea:*%s\n", map_value->ea);
		printf("c_color:*%d\n", map_value->c_color);
		printf("f_color:*%d\n", map_value->f_color);
		// printf("**********************************\n");

		// int i = 0;
		// while (map_value->map[i])
		// {
		// 	printf("map[%d]:%s\n", i, map_value->map[i]);
		// 	i++;
		// }
		
		// printf("**********************************\n");
		open_window(map_value);
	}
	else
		return (print_err("invalid argument count", NULL));

	//system("leaks cub3d");
}
