/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:27:44 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/26 13:43:02 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	validate_file_extension(const char *filename)
// {
// 	const char	*extension;
// 	int			len;

// 	len = ft_strlen(filename);
// 	if (len < 4)
// 	{
// 		ft_printf("Map file must have .ber extension");
// 		return (1);
// 	}
// 	extension = filename + (len - 4);
// 	if (ft_strncmp(extension, ".ber", 4) != 0)
// 	{
// 		ft_printf("Map file must have .ber extension");
// 		return (1);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map_file.ber\n");
		return (0);
	}
	// if (validate_file_extension(argv[1]))
	// 	return (1);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		return (1);
	}
	ft_bzero(game, sizeof(t_game));
	if (!init_game(game, argv[1]))
	{
		cleanup_game(game);
		return (1);
	}
	mlx_loop(game->mlx);
	cleanup_game(game);
	free(game);
	return (0);
}
