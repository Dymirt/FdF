/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:44:58 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/16 14:58:49 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	center_map_to_screen(t_map *map);
void	crop_scale(t_map *map);

void	transate_to_positive(t_map *map)
{
	for_each_t_dot(map, to_positive);
	reset_min_max(map);
}

void	center_map_to_screen(t_map *map)
{
	map->moves_x = (SCREEN_WIDTH / 2) - ((map->max_x - map->min_x) / 2);
	map->moves_y = (SCREEN_HEIGHT / 2) - ((map->max_y - map->min_y) / 2);
	apply_moves(map);
}

void	rotate_map(t_map *map)
{
	for_each_t_dot(map, rotate_point);
	reset_min_max(map);
}

void	object_zoom(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->map_data->img.img);
	fdf->map_data->img.img = mlx_new_image(fdf->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	fdf->map_data->img.addr = mlx_get_data_addr(
			fdf->map_data->img.img, &fdf->map_data->img.bits_per_pixel,
			&fdf->map_data->img.line_length, &fdf->map_data->img.endian);
	scale_3d_map(fdf->map_data);
	for_each_t_dot(fdf->map_data, draw_lines);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win,
		fdf->map_data->img.img, 0, 0);
	fdf->map_data->scale = 1;
}

void	move_view_point(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->map_data->img.img);
	fdf->map_data->img.img = mlx_new_image(fdf->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	fdf->map_data->img.addr = mlx_get_data_addr(
			fdf->map_data->img.img, &fdf->map_data->img.bits_per_pixel,
			&fdf->map_data->img.line_length, &fdf->map_data->img.endian);
	apply_moves(fdf->map_data);
	for_each_t_dot(fdf->map_data, draw_lines);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win,
		fdf->map_data->img.img, 0, 0);
}
