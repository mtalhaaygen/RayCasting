/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:14:33 by maygen            #+#    #+#             */
/*   Updated: 2023/12/21 17:12:03 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\r' || c == '\f' || c == '\v')
		return (1);
	else
		return (0);
}

int	print_err(char *str, char *arg)
{
	if (!arg)
		printf("%s", str);
	else
		printf("%s \"%s\"", str, arg);
	printf(" Error\n");
	exit(1);
}

void	filename_extension(char *str, char *dot)
{
	char	*extension;

	extension = ft_strchr_last(str, '.');
	if (ft_strcmp(extension, dot))
		print_err("file extension not valid", extension);
}

char	*ft_trim(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	end[1] = '\0';
	return (str);
}
