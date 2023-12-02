/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maygen <maygen@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:05:21 by maygen            #+#    #+#             */
/*   Updated: 2023/12/02 15:50:38 by maygen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_same(t_map	*map_value)
{
	printf("check %s", map_value->no);
	printf("check %s", map_value->so);
	printf("check %s", map_value->we);
	printf("check %s", map_value->ea);
}