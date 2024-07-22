/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:11:52 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/16 19:41:16 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

void	draw_line(t_dot *start, t_dot *end, t_data img);
void	put_pixel(t_data *data, int x, int y, int color);
int		in_visible_erea(t_dot *dot);
void	init_step(t_step *step, t_dot *start, t_dot *end);

void	drow_img(t_fdf *fdf)
{
	fdf->map_data->img.img = mlx_new_image(fdf->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	fdf->map_data->img.addr = mlx_get_data_addr(
			fdf->map_data->img.img, &fdf->map_data->img.bits_per_pixel,
			&fdf->map_data->img.line_length, &fdf->map_data->img.endian);
	fdf->map_data->map3d = t_dot_allocate_2d_arr(fdf->map_data->width,
			fdf->map_data->height);
	create_3d_map(fdf->map_data);
	rotate_map(fdf->map_data);
	isometric_view(fdf->map_data);
	transate_to_positive(fdf->map_data);
	scale_3d_map(fdf->map_data);
	center_map_to_screen(fdf->map_data);
	for_each_t_dot(fdf->map_data, draw_lines);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win,
		fdf->map_data->img.img, 0, 0);
}

void	draw_line(t_dot *start, t_dot *end, t_data img)
{
	t_dot	*tmp_dot;
	t_step	*step;

	step = malloc(sizeof(t_step));
	if (step == NULL)
		return ;
	tmp_dot = copy_dot(start);
	init_step(step, start, end);
	while (((int)(tmp_dot->x - end->x) || (int)(tmp_dot->y - end->y)))
	{
		if (in_visible_erea(tmp_dot))
			put_pixel(&img, (int)tmp_dot->x, (int)tmp_dot->y,
				create_trgb(0, tmp_dot->color->r, tmp_dot->color->g,
					tmp_dot->color->b));
		tmp_dot->x += step->step_x;
		tmp_dot->y += step->step_y;
		tmp_dot->color->r += step->step_r;
		tmp_dot->color->g += step->step_g;
		tmp_dot->color->b += step->step_b;
	}
	free(step);
	free(tmp_dot->color);
	free(tmp_dot);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	in_visible_erea(t_dot *dot)
{
	if (dot->x < 0 || dot->x >= SCREEN_WIDTH
		|| dot->y < 0 || dot->y >= SCREEN_HEIGHT)
		return (0);
	return (1);
}

void	init_step(t_step *step, t_dot *start, t_dot *end)
{
	float	x_step;
	float	y_step;

	x_step = end->x - start->x;
	y_step = end->y - start->y;
	step->step_x = 0;
	step->step_y = 0;
	step->step_r = 0;
	step->step_g = 0;
	step->step_b = 0;
	step->steps = fmax(fabs(x_step), fabs(y_step));
	if (step->steps == 0)
		step->steps = 1;
	if (x_step)
		step->step_x = x_step / (float)step->steps;
	if (y_step)
		step->step_y = y_step / (float)step->steps;
	if (end->color->r - start->color->r)
		step->step_r = (end->color->r - start->color->r) / step->steps;
	if (end->color->g - start->color->g)
		step->step_g = (end->color->g - start->color->g) / step->steps;
	if (end->color->b - start->color->b)
		step->step_b = (end->color->b - start->color->b) / step->steps;
}
