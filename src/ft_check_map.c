/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:48:43 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/25 16:26:02 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_valid_chars(t_map *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			c = map->grid[i][j];
			if (c != WALL && c != FLOOR && c != PLAYER && c != COLLECTIBLE
				&& c != EXIT)
			{
				error_exit("Invalid character in map");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_wall(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->cols)
	{
		if (map->grid[0][x] != WALL || map->grid[map->rows - 1][x] != WALL)
		{
			error_exit("Map is not surrounded by walls");
			return (0);
		}
		x++;
	}
	y = 1;
	while (y < map->rows - 1)
	{
		if (map->grid[y][0] != WALL || map->grid[y][map->cols - 1] != WALL)
		{
			error_exit("Map is not surrounded by walls");
			return (0);
		}
		y++;
	}
	return (1);
}

static int	check_element_counts(t_map *map)
{
	if (map->n_player != 1)
	{
		error_exit("Map must have exactly one player");
		return (0);
	}
	if (map->n_exit != 1)
	{
		error_exit("Map must have exactly one exit");
		return (0);
	}
	if (map->n_collect < 1)
	{
		error_exit("Map must have at least one collectible");
		return (0);
	}
	return (1);
}

static int	check_map_if_rectangle(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if ((int)ft_strlen(map->grid[i]) != map->cols)
		{
			error_exit("Map is not rectangular");
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!check_valid_chars(map))
		return (0);
	if (!check_wall(map))
		return (0);
	if (!check_map_if_rectangle(map))
		return (0);
	if (!check_element_counts(map))
		return (0);
	return (1);
}
