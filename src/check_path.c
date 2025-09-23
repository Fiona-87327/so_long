/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:28:25 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/23 20:32:52 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_free_visited(int **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	dfs(t_map *map, int x, int y, int **visited)
{
	if (x < 0 || x >= map->cols || y < 0 || y >= map->rows)
		return ;
	if (map->grid[y][x] == WALL || visited[y][x])
		return ;
	visited[y][x] = 1;
	dfs(map, x + 1, y, visited);
	dfs(map, x - 1, y, visited);
	dfs(map, x, y + 1, visited);
	dfs(map, x, y - 1, visited);
}

static int	is_path_valid(t_map *map, int **visited)
{
	int	collect_found;
	int	exit_found;
	int	y;
	int	x;

	collect_found = 0;
	exit_found = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->grid[y][x] == COLLECTIBLE && visited[y][x])
				collect_found++;
			if (map->grid[y][x] == EXIT && visited[y][x])
				exit_found = 1;
			x++;
		}
		y++;
	}
	return (collect_found == map->n_collect && exit_found);
}

static void	find_player_position(t_map *map, int *player_x, int *player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			if (map->grid[y][x] == PLAYER)
			{
				*player_x = x;
				*player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	check_path(t_map *map)
{
	int	**visited;
	int	i;
	int	player_x;
	int	player_y;
	int	result;

	visited = malloc(sizeof(int *) * map->rows);
	if (!visited)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		visited[i] = malloc(sizeof(int) * map->cols);
		if (!visited[i])
		return (ft_free_visited(visited, i), 0);
		ft_memset(visited[i], 0, sizeof(int) * map->cols);
		i++;
	}
	find_player_position(map, &player_x, &player_y);
	dfs(map, player_x, player_y, visited);
	result = is_path_valid(map, visited);
	ft_free_visited(visited, map->rows);
	return (result);
}
