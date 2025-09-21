/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:55:19 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/21 13:55:22 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 32

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

# define WALL '1'
# define FLOOR '0'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'

typedef struct s_map
{
	char		**grid;
	int			rows;
	int			cols;
	int			n_player;
	int			n_exit;
	int			n_collect;
}				t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	int			player_x;
	int			player_y;
	int			move_count;
	int			collected;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_floor;
	mlx_image_t	*img_player;
	mlx_image_t	*img_collect;
	mlx_image_t	*img_exit;
}				t_game;

t_map			*parse_map(const char *filename);
int				validate_map(t_map *map);
void			free_map(t_map *map);
int				init_game(t_game *game, const char *map_file);
int				load_textures(t_game *game);
void			render_game(t_game *game);
void			key_handler(mlx_key_data_t keydata, void *param);
int				move_player(t_game *game, int new_x, int new_y);
void			cleanup_game(t_game *game);
void			error_exit(const char *msg);

#endif
