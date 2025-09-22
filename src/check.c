/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:48:43 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/22 09:49:02 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_rect_and_border(t_map *map)
{
	int i;
	for (i = 0; i < map->rows; i++)
		if ((int)ft_strlen(map->grid[i]) != map->cols) { error_exit("Map is not rectangular"); return 0; }
	for (i = 0; i < map->cols; i++)
		if (map->grid[0][i] != WALL || map->grid[map->rows - 1][i] != WALL) { error_exit("Map border must be walls"); return 0; }
	for (i = 0; i < map->rows; i++)
		if (map->grid[i][0] != WALL || map->grid[i][map->cols - 1] != WALL) { error_exit("Map border must be walls"); return 0; }
	return 1;
}

static int	check_chars_and_counts(t_map *map)
{
	int i = 0, j;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			char c = map->grid[i][j];
			if (c != WALL && c != FLOOR && c != PLAYER && c != COLLECTIBLE && c != EXIT)
			{ error_exit("Invalid character in map"); return 0; }
			j++;
		}
		i++;
	}
	if (map->n_player != 1) { error_exit("Map must have exactly one player"); return 0; }
	if (map->n_exit != 1) { error_exit("Map must have exactly one exit"); return 0; }
	if (map->n_collect < 1) { error_exit("Map must have at least one collectible"); return 0; }
	return 1;
}

int	validate_map(t_map *map)
{
	if (!check_rect_and_border(map)) return 0;
	if (!check_chars_and_counts(map)) return 0;
	return 1;
}
