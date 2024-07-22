/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_each_t_dot_mod_func.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:38:25 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/16 17:21:51 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	to_positive(t_map *map, t_dot *dot)
{
	dot->x += fabs(map->min_x);
	dot->y += fabs(map->min_y);
}

void	scale_dot(t_map *map, t_dot *dot)
{
	dot->x *= map->scale;
	dot->y *= map->scale;
}

void	move_dot(t_map *map, t_dot *dot)
{
	dot->x += map->moves_x;
	dot->y += map->moves_y;
}

void	draw_lines(t_map *map, t_dot *dot)
{
	int	col;
	int	row;

	col = map->tmp->col;
	row = map->tmp->row;
	if (row + 1 < map->width)
		draw_line(dot, map->map3d[col][row + 1], map->img);
	if (col + 1 < map->height)
		draw_line(dot, map->map3d[col + 1][row], map->img);
}

void	rotate_point(t_map *map, t_dot *dot)
{
	float	radians;
	float	cos_theta;
	float	sin_theta;

	radians = map->degrees_rotate * (M_PI / 180.0);
	cos_theta = cos(radians);
	sin_theta = sin(radians);
	dot->x = dot->x * cos_theta + dot->y * sin_theta;
	dot->y = -dot->x * sin_theta + dot->y * cos_theta;
}
