/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:58:34 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/16 19:08:15 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	load_map(t_map *map, int fd);
static int	is_valid_line_lenth(char **line, int lenth);
int			add_line(t_map *map, char *line);
static char	**get_map_line(char *line, int *lenth);

void	read_map_file(t_fdf *fdf, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd > 0)
	{
		load_map(fdf->map_data, fd);
		close(fd);
		if (fdf->map_data->map2d == NULL)
		{
			ft_printf("Error reading file\n");
			free(fdf->map_data);
			free(fdf);
			exit(1);
		}
	}
}

static void	load_map(t_map *map, int fd)
{
	char	*line;

	map->map2d = NULL;
	while (fd > 0)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			if (add_line(map, line) == 0)
			{
				free(line);
				ft_printf("col: %d\n", map->height);
				while (map->height > 0)
				{
					ft_free_split(map->map2d[--map->height]);
				}
				free(map->map2d);
				map->map2d = NULL;
				break ;
			}
			free(line);
		}
		else
			break ;
	}
}

int	add_line(t_map *map, char *line)
{
	char	**map_line;

	map_line = get_map_line(line, &map->width);
	if (map_line == NULL)
	{
		return (0);
	}
	map->map2d = (char ***)ft_realloc(
			map->map2d, sizeof(char **) * (map->height++),
			sizeof(char **) * map->height);
	if (map->map2d == NULL)
	{
		ft_printf("Memory allocation for reading map failed\n");
		free(map_line);
		return (0);
	}
	map->map2d[map->height - 1] = map_line;
	return (1);
}

static int	is_valid_line_lenth(char **line, int lenth)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i < lenth)
	{
		ft_printf("Invalid map line lenth %d < %d ", i, lenth);
		return (0);
	}
	return (1);
}

static char	**get_map_line(char *line, int *lenth)
{
	char	**map_line;

	map_line = ft_split(line, ' ');
	if (map_line == NULL)
	{
		ft_printf("Memory allocation for reading map failed\n");
		return (0);
	}
	if (*lenth == 0)
		while (map_line[*lenth])
			*lenth += 1;
	else if (!is_valid_line_lenth(map_line, *lenth))
	{
		ft_free_split(map_line);
		return (0);
	}
	return (map_line);
}
