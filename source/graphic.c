/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:25 by thelee            #+#    #+#             */
/*   Updated: 2024/09/10 19:33:08 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_image(t_game *game)
{
	int	w;
	int	h;

	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"image/wall.xpm", &w, &h);
	game->img_ground = mlx_xpm_file_to_image(game->mlx,
			"image/ground.xpm", &w, &h);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"image/player.xpm", &w, &h);
	game->img_item = mlx_xpm_file_to_image(game->mlx,
			"image/item.xpm", &w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"image/exit.xpm", &w, &h);
	if (!game->img_wall || !game->img_ground || !game->img_player
		|| !game->img_item || !game->img_exit)
	{
		ft_printf("Error\nSome image got wrong...");
		close_game(game);
		exit(EXIT_FAILURE);
	}
}

void	game_graphic_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->data[y][x] == '1')
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_wall, x * 32, y * 32);
			else if (game->map->data[y][x] == 'E')
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_exit, x * 32, y * 32);
			else
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_ground, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

void	game_graphic_play(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->data[y][x] == 'P')
			{
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_player, x * 32, y * 32);
				game->player_x = x;
				game->player_y = y;
			}
			else if (game->map->data[y][x] == 'C')
				mlx_put_image_to_window(game->mlx,
					game->win, game->img_item, x * 32 + 8, y * 32 + 8);
			x++;
		}
		y++;
	}
	message_graphic(game);
}

void	message_graphic(t_game *game)
{
	char	*message;

	message = ft_itoa(game->collect);
	mlx_string_put(game->mlx, game->win,
		20, 20, 0xFFFFFFFF, "To collect ");
	mlx_string_put(game->mlx, game->win,
		20 + ft_strlen("To collect ") * 8, 20, 0xFFFFFFFF, message);
	free(message);
	message = ft_itoa(game->move);
	mlx_string_put(game->mlx, game->win, game->map->width
		* 32 - 20 - (ft_strlen(" move") * 8), 20, 0xFFFFFFFF, "move ");
	mlx_string_put(game->mlx, game->win, game->map->width * 32
		- 20 - (ft_strlen(" move") * 8) - (3 * 8), 20, 0xFFFFFFFF, message);
	free(message);
}
