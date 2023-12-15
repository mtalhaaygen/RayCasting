/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:51:37 by maygen            #+#    #+#             */
/*   Updated: 2023/12/15 16:00:21 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include "../libft/libft.h"

char	*multiread(char *str, int fd)
{
	char	*l;
	int		lw;

	l = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!l)
		return (NULL);
	lw = 1;
	while (lw != 0 && !(ft_strchr(str, '\n')))
	{
		lw = read(fd, l, BUFFER_SIZE);
		if (lw == -1)
		{
			free(l);
			free(str);
			return (NULL);
		}
		l[lw] = '\0';
		str = ft_strjoin(str, l);
	}
	free(l);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = multiread(str, fd);
	if (!str)
		return (NULL);
	line = liner(str);
	str = next(str);
	return (line);
}
