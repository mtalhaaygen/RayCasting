#include "cub3d.h"

int	print_err(char *str, char *arg)
{
	if (!arg)
		printf("%s\n", str);
	else
		printf("%s %s\n",str, arg);
	exit(1);
}

int	filename_extension(char *str)
{
	char *extension;

	extension =  ft_strchr(str, '.');
	if (ft_strcmp(extension, ".cub"))
		print_err("file extension not valid", NULL);
	return (0);
}

t_map	*map_check(char **gv, t_map *map_value)
{
	filename_extension(gv[1]);
	map_reader(map_value); // tüm haritayı okuyup structdaki verileri dolduracak
	wall_check(map_value->map); // map duvarlarını kontrol edecek
}

int main(int gc, char **gv)
{
	t_map *map_value;
 
	if (gc == 2)
	{
		map_value = map_check(gv, map_value);

	}
	else
		return (print_err("invalid argument count", NULL));
}