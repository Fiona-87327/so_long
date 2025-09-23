/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:29:45 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/23 21:14:00 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->rows && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	error_exit(const char *msg)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(EXIT_FAILURE);
}

// int	validate_file_extension(const char *filename)
// {
// 	const char	*extension;
// 	int		len;

// 	len = ft_strlen(filename);
// 	if (len < 4)
// 		return (0);
// 	extension = filename + (len - 4);
// 	if (ft_strncmp(extension, ".ber", 4) != 0)
// 	{
// 		error_exit("Map file must have .ber extension");
// 		return (0);
// 	}
// 	return (1);
// }
