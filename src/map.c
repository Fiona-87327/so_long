/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 22:19:03 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/22 09:49:24 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_file_extension(const char *filename)
{
	int len = ft_strlen(filename);
	return (len >= 5 && ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}

static char	*read_file_content(const char *filename)
{
	int		fd;
	char	*line, *content, *temp;
	if (!check_file_extension(filename)) { error_exit("Invalid file extension. Must be .ber"); return NULL; }
	fd = open(filename, O_RDONLY);
	if (fd < 0) { error_exit("Cannot open map file"); return NULL; }
	content = ft_strdup("");
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = ft_strjoin(content, line);
		free(content); free(line);
		content = temp;
	}
	close(fd);
	return content;
}

static void	count_map_elements(t_map *map)
{
	int i = 0, j;
	map->n_player = 0; map->n_exit = 0; map->n_collect = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			char c = map->grid[i][j];
			if (c == PLAYER) map->n_player++;
			else if (c == EXIT) map->n_exit++;
			else if (c == COLLECTIBLE) map->n_collect++;
			j++;
		}
		i++;
	}
}

t_map	*parse_map(const char *filename)
{
	t_map	*map;
	char	*content;
	char	**lines;
	content = read_file_content(filename);
	if (!content) return NULL;
	map = malloc(sizeof(t_map));
	if (!map) { free(content); error_exit("Memory allocation failed"); return NULL; }
	lines = ft_split(content, '\n'); free(content);
	if (!lines) { free(map); error_exit("Failed to split map lines"); return NULL; }
	map->rows = 0;
	while (lines[map->rows]) map->rows++;
	if (map->rows == 0) { free(lines); free(map); error_exit("Empty map file"); return NULL; }
	map->cols = ft_strlen(lines[0]);
	map->grid = lines;
	count_map_elements(map);
	return map;
}

