/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:19:03 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/23 12:57:30 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	*init_map_structure(char *content)
{
	t_map	*map;
	char	**lines;

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
	map->grid = lines;
	return (map);
}

static int	set_map_dimensions(t_map *map)
{
	map->rows = 0;
	while (map->grid[map->rows])
		map->rows++;
	if (map->rows == 0)
	{
		free(map->grid);
		free(map);
		error_exit("Empty map file");
		return (0);
	}
	map->cols = ft_strlen(map->grid[0]);
	return (1);
}

char	*read_file_content(const char *filename)
{
	int		fd;
	char	*content;
	char	*line;
	char	*temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	content = ft_strdup("");
	if (!content)
		error_exit("Memory allocation failed");
	line = get_next_line(fd);
	while (line != NULL)
	{
		temp = ft_strjoin(content, line);
		free(content);
		free(line);
		if (!temp)
			error_exit("Memory allocation failed");
		content = temp;
		line = get_next_line(fd);
	}
	close(fd);
	return (content);
}

void	count_map_elements(t_map *map)
{
	int	i;
	int	j;

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
}

t_map	*parse_map(const char *filename)
{
	t_map	*map;
	char	*content;

	content = read_file_content(filename);
	if (!content)
		return (NULL);
	map = init_map_structure(content);
	if (!map)
		return (NULL);
	if (!set_map_dimensions(map))
		return (NULL);
	count_map_elements(map);
	return (map);
}
