/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:48:41 by maygen            #+#    #+#             */
/*   Updated: 2023/12/15 16:53:36 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr_last(const char *str, int c)
{
	int		i;

	i = ft_strlen(str);
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[i]);
	while (str[--i] && i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
	}
	return (0);
}
