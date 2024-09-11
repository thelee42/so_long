/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:50:33 by thelee            #+#    #+#             */
/*   Updated: 2024/09/10 19:44:38 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_x(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

void	close_game(t_game *game)
{
	free_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_free_split(game->map->data);
	free(game->map);
	free(game);
}

void	init_game(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map->width * 32,
			game->map->height * 32, "So Short");
	game->img_ground = NULL;
	game->img_exit = NULL;
	game->img_wall = NULL;
	game->img_player = NULL;
	game->img_item = NULL;
	game->move = 0;
	game->over = 0;
}

void	init_map(t_game *game, char *str)
{
	char	*line;

	if (ft_strncmp(&str[ft_strlen(str) - 4], ".ber", 4) != 0)
		free_error(game);
	line = read_map(str);
	if (line == NULL)
		free_error(game);
	game->map->data = ft_split(line, '\n');
	game->map->width = ft_strlen(game->map->data[0]);
	game->map->height = map_height(game->map->data);
	game->collect = ft_count_word(line, 'C');
	if (check_map(game->map, line) == 1 || path_valid(game) == 1
		|| trop_grand_map(game) == 1 || vide_check(line) == 1)
	{
		ft_free_split(game->map->data);
		free(line);
		free_error(game);
	}
	free(line);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (ft_printf("Error\nOops.. Something got wrong..\n"), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	game->mlx = mlx_init();
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		free(game);
		return (ft_printf("Error\nOops.. Something got wrong..\n"), 1);
	}
	init_map(game, argv[1]);
	init_game(game);
	game_image(game);
	game_graphic_background(game);
	game_graphic_play(game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 17, 1L << 5, close_x, game);
	mlx_loop(game->mlx);
	close_game(game);
	return (0);
}
