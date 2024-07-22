/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:38:36 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/16 19:07:11 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	move_keys(t_map *map, int keycode);
static int	scale_keys(t_map *map, int keycode);
static int	rotate_keys(t_map *map, int keycode);

int	close_window_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	clean_exit(fdf);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (scale_keys(fdf->map_data, keycode))
	{
		object_zoom(fdf);
		return (0);
	}
	if (move_keys(fdf->map_data, keycode))
	{
		move_view_point(fdf);
		return (0);
	}
	if (keycode == ESC_KEY_MAC)
	{
		clean_exit(fdf);
	}
	if (rotate_keys(fdf->map_data, keycode))
	{
		mlx_destroy_image(fdf->mlx, fdf->map_data->img.img);
		t_dot_free_2d_arr(fdf->map_data);
		drow_img(fdf);
	}
	ft_printf("keycode: %d\n", keycode);
	return (0);
}

static int	move_keys(t_map *map, int keycode)
{
	if (keycode == MOVE_UP)
		map->moves_y += 10;
	else if (keycode == MOVE_DOWN)
		map->moves_y -= 10;
	else if (keycode == MOVE_LEFT)
		map->moves_x += 10;
	else if (keycode == MOVE_RIGHT)
		map->moves_x -= 10;
	else
		return (0);
	return (1);
}

static int	scale_keys(t_map *map, int keycode)
{
	if (keycode == SCALE_UP)
		map->scale = 1.1;
	else if (keycode == SCALE_DOWN)
		map->scale = 0.9;
	else
		return (0);
	return (1);
}

static int	rotate_keys(t_map *map, int keycode)
{
	if (keycode == ROTATE_LEFT)
		map->degrees_rotate += 1;
	else if (keycode == ROTATE_RIGHT)
		map->degrees_rotate -= 1;
	else
		return (0);
	return (1);
}
