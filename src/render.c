/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:43:29 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/22 18:58:57 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_game *game, int x, int y)
{
	char	c;

	c = game->map->grid[y][x];
	mlx_image_to_window(game->mlx, game->img_floor, x * TILE_SIZE, y
		* TILE_SIZE);
	if (c == WALL)
		mlx_image_to_window(game->mlx, game->img_wall, x * TILE_SIZE, y
			* TILE_SIZE);
	else if (c == COLLECTIBLE)
		mlx_image_to_window(game->mlx, game->img_collect, x * TILE_SIZE, y
			* TILE_SIZE);
	else if (c == EXIT)
		mlx_image_to_window(game->mlx, game->img_exit, x * TILE_SIZE, y
			* TILE_SIZE);
	else if (c == PLAYER)
	{
		if (game->player_dir == 0)
			mlx_image_to_window(game->mlx, game->img_player_r, x * TILE_SIZE, y
				* TILE_SIZE);
		else
			mlx_image_to_window(game->mlx, game->img_player_l, x * TILE_SIZE, y
				* TILE_SIZE);
	}
}

void	render_game(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
}

void	move_update(t_game *game, int new_x, int new_y)
{
	game->map->grid[game->player_y][game->player_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map->cols || new_y < 0
		|| new_y >= game->map->rows)
		return (0);
	if (game->map->grid[new_y][new_x] == WALL)
		return (0);
	if (game->map->grid[new_y][new_x] == EXIT
		&& game->collected < game->map->n_collect)
		return (0);
	if (game->map->grid[new_y][new_x] == COLLECTIBLE)
	{
		game->collected++;
		game->map->grid[new_y][new_x] = FLOOR;
	}
	if (game->map->grid[new_y][new_x] == EXIT
		&& game->collected == game->map->n_collect)
	{
		ft_printf("Congratulations! You won in %d moves!\n", game->move_count
			+ 1);
		cleanup_game(game);
		exit(0);
	}
	move_update(game, new_x, new_y);
	game->map->grid[new_y][new_x] = PLAYER;
	render_game(game);
	return (1);
}
