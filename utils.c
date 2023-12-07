/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:14:33 by maygen            #+#    #+#             */
/*   Updated: 2023/12/02 14:18:36 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_err(char *str, char *arg)
{
	if (!arg)
		printf("%s\n", str);
	else
		printf("%s \"%s\"\n", str, arg);
	exit(1);
}

void	filename_extension(char *str, char *dot)
{
	char	*extension;

	extension = ft_strchr(str, '.');
	if (ft_strcmp(extension, dot))
		print_err("file extension not valid", NULL);
}

char	*ft_trim(char *s1)
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