/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyan <jiyan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:27:30 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/21 16:54:28 by jiyan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_file_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}

static char	*read_file_content(const char *filename)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	if (!check_file_extension(filename))
	{
		error_exit("Invalid file extension. Must be .ber");
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error_exit("Cannot open map file");
		return (NULL);
	}
	content = ft_strdup("");
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = ft_strjoin(content, line);
		free(content);
		free(line);
		content = temp;
	}
	close(fd);
	return (content);
}

t_map	*parse_map(const char *filename)
{
	t_map	*map;
	char	*content;
	char	**lines;
	int		i;
	int		j;

	content = read_file_content(filename);
	if (!content)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		free(content);
		error_exit("Memory allocation failed");
		return (NULL);
	}
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
	{
		free(map);
		error_exit("Failed to split map lines");
		return (NULL);
	}
	map->rows = 0;
	while (lines[map->rows])
		map->rows++;
	if (map->rows == 0)
	{
		free(lines);
		free(map);
		error_exit("Empty map file");
		return (NULL);
	}
	map->cols = ft_strlen(lines[0]);
	map->grid = lines;
	map->n_player = 0;
	map->n_exit = 0;
	map->n_collect = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] == PLAYER)
				map->n_player++;
			else if (map->grid[i][j] == EXIT)
				map->n_exit++;
			else if (map->grid[i][j] == COLLECTIBLE)
				map->n_collect++;
			j++;
		}
		i++;
	}
	return (map);
}

int	validate_map(t_map *map)
{
	int		i;
	int		j;
	char	c;

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
	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] != WALL || map->grid[map->rows - 1][i] != WALL)
		{
			error_exit("Map border must be walls");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] != WALL || map->grid[i][map->cols - 1] != WALL)
		{
			error_exit("Map border must be walls");
			return (0);
		}
		i++;
	}
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

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}
