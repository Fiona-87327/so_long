/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:27:12 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/21 13:34:18 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_game *game, const char *map_file)
{
	game->map = parse_map(map_file);
	if (!game->map)
		return (0);
	
	// 验证地图
	if (!validate_map(game->map))
	{
		free_map(game->map);
		return (0);
	}
	
	game->mlx = mlx_init(game->map->cols * TILE_SIZE, 
		game->map->rows * TILE_SIZE, "so_long", false);
	if (!game->mlx)
	{
		free_map(game->map);
		error_exit("Failed to initialize MLX");
	}
	if (!load_textures(game))
	{
		cleanup_game(game);
		return (0);
	}
	game->move_count = 0;
	game->collected = 0;
	int	y = 0;
	while (y < game->map->rows)
	{
		int x = 0;
		while (x < game->map->cols)
		{
			if (game->map->grid[y][x] == PLAYER)
			{
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		y++;
	}
	mlx_key_hook(game->mlx, &key_handler, game);
	render_game(game);
	return (1);
}

int	load_textures(t_game *game)
{
	mlx_texture_t	*texture;
	texture = mlx_load_png("textures/wall.png");
	if (!texture)
		return (0);
	game->img_wall = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!game->img_wall)
		return (0);
	texture = mlx_load_png("textures/floor.png");
	if (!texture)
		return (0);
	game->img_floor = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!game->img_floor)
		return (0);
	texture = mlx_load_png("textures/player.png");
	if (!texture)
		return (0);
	game->img_player = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!game->img_player)
		return (0);
	texture = mlx_load_png("textures/collectible.png");
	if (!texture)
		return (0);
	game->img_collect = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!game->img_collect)
		return (0);
	texture = mlx_load_png("textures/exit.png");
	if (!texture)
		return (0);
	game->img_exit = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!game->img_exit)
		return (0);
	
	return (1);
}

void	render_game(t_game *game)
{
	int	y = 0;
	game->img_wall->enabled = false;
	game->img_floor->enabled = false;
	game->img_player->enabled = false;
	game->img_collect->enabled = false;
	game->img_exit->enabled = false;

	game->img_wall->enabled = true;
	game->img_floor->enabled = true;
	game->img_player->enabled = true;
	game->img_collect->enabled = true;
	game->img_exit->enabled = true;
	for (uint32_t i = 0; i < game->img_wall->count; i++)
		game->img_wall->instances[i].enabled = false;
	for (uint32_t i = 0; i < game->img_floor->count; i++)
		game->img_floor->instances[i].enabled = false;
	for (uint32_t i = 0; i < game->img_player->count; i++)
		game->img_player->instances[i].enabled = false;
	for (uint32_t i = 0; i < game->img_collect->count; i++)
		game->img_collect->instances[i].enabled = false;
	for (uint32_t i = 0; i < game->img_exit->count; i++)
		game->img_exit->instances[i].enabled = false;
	
	while (y < game->map->rows)
	{
		int x = 0;
		while (x < game->map->cols)
		{
			mlx_image_to_window(game->mlx, game->img_floor, 
				x * TILE_SIZE, y * TILE_SIZE);
			if (game->map->grid[y][x] == WALL)
				mlx_image_to_window(game->mlx, game->img_wall, 
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map->grid[y][x] == COLLECTIBLE)
				mlx_image_to_window(game->mlx, game->img_collect, 
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map->grid[y][x] == EXIT)
				mlx_image_to_window(game->mlx, game->img_exit, 
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map->grid[y][x] == PLAYER)
				mlx_image_to_window(game->mlx, game->img_player, 
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game = (t_game *)param;
	int		new_x = game->player_x;
	int		new_y = game->player_y;
	
	if (keydata.action != MLX_PRESS)
		return;
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
		new_x--;
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		new_x++;
	if (new_x != game->player_x || new_y != game->player_y)
		move_player(game, new_x, new_y);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map->cols || 
		new_y < 0 || new_y >= game->map->rows)
		return (0);
	if (game->map->grid[new_y][new_x] == WALL)
		return (0);
	if (game->map->grid[new_y][new_x] == EXIT && 
		game->collected < game->map->n_collect)
		return (0);
	game->map->grid[game->player_y][game->player_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	game->move_count++;
	if (game->map->grid[new_y][new_x] == COLLECTIBLE)
	{
		game->collected++;
		game->map->grid[new_y][new_x] = FLOOR;
	}
	if (game->map->grid[new_y][new_x] == EXIT && 
		game->collected == game->map->n_collect)
	{
		ft_printf("Congratulations! You won in %d moves!\n", game->move_count);
		cleanup_game(game);
		exit(0);
	}
	game->map->grid[new_y][new_x] = PLAYER;
	ft_printf("Moves: %d\n", game->move_count);
	render_game(game);
	return (1);
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
	ft_printf("Error\n%s\n", msg);
	exit(1);
}
