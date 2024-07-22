/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_each_t_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:27:18 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/15 01:30:19 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	update_min_max(t_map *map, t_dot *dot);
void	reset_min_max(t_map *map);

void	for_each_t_dot(t_map *map, void (*f)(t_map *, t_dot *))
{
	int	col;
	int	row;

	col = 0;
	map->tmp = (t_tmp *)malloc(sizeof(t_tmp));
	while (col < map->height)
	{
		row = 0;
		while (row < map->width)
		{
			map->tmp->col = col;
			map->tmp->row = row;
			f(map, map->map3d[col][row]);
			row++;
		}
		col++;
	}
	free(map->tmp);
}

void	update_min_max(t_map *map, t_dot *dot)
{
	map->min_x = fmin(dot->x, map->min_x);
	map->min_y = fmin(dot->y, map->min_y);
	map->max_x = fmax(dot->x, map->max_x);
	map->max_y = fmax(dot->y, map->max_y);
}

void	reset_min_max(t_map *map)
{
	map->min_x = 0;
	map->min_y = 0;
	map->max_x = 0;
	map->max_y = 0;
	for_each_t_dot(map, update_min_max);
}
