/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:35:25 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/22 09:58:18 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
	exit(1);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		for (i = 0; i < map->rows; i++)
			free(map->grid[i]);
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

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	new_x = game->player_x;
	new_y = game->player_y;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		cleanup_game(game);
		exit(0);
	}
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		new_y--;
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		new_y++;
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
	{
		new_x--;
		game->player_dir = 1;
	}
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
	{
		new_x++;
		game->player_dir = 0;
	}
	if (new_x != game->player_x || new_y != game->player_y)
		move_player(game, new_x, new_y);
}
