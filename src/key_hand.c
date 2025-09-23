/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:35:25 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/23 11:53:30 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_movement_keys(mlx_key_data_t keydata, t_game *game,
		int *new_x, int *new_y)
{
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		(*new_y)--;
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		(*new_y)++;
	else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
	{
		(*new_x)--;
		game->player_dir = 1;
	}
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
	{
		(*new_x)++;
		game->player_dir = 0;
	}
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
	handle_movement_keys(keydata, game, &new_x, &new_y);
	if (new_x != game->player_x || new_y != game->player_y)
		move_player(game, new_x, new_y);
}
