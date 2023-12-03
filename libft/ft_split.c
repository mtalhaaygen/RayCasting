/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:41:29 by maygen            #+#    #+#             */
/*   Updated: 2023/12/03 22:04:25 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getwordcount(char const *s, char c)
{
	int	i;
	int	rt;

	i = 0;
	rt = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			rt++;
		while (s[i] != c && s[i])
			i++;
	}
	return (rt);
}

static char	**ft_splitter(char const *s, char c, char **rt)
{
	int	i;
	int	j;
	int	templen;

	i = 0;
	j = -1;
	while (s[i])
	{
		templen = 0;
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			j++;
		while (s[i + templen] != c && s[i + templen])
			templen++;
		if (templen > 0)
			rt[j] = ft_substr(s, i, templen);
		i += templen;
	}
	rt[++j] = 0;
	return (rt);
}

char	**ft_split(char const *s, char c)
{
	char	**rt;

	if (!s)
		return (0);
	rt = (char **)malloc(sizeof(char *) * (ft_getwordcount(s, c) + 1));
	if (!rt)
		return (0);
	rt = ft_splitter(s, c, rt);
	return (rt);
}
