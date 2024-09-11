/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:50:55 by thelee            #+#    #+#             */
/*   Updated: 2024/09/10 19:25:31 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	if (key == 65307)
		mlx_loop_end(game->mlx);
	new_x = game->player_x;
	new_y = game->player_y;
	if (game->over == 1)
		return (0);
	else if (key == 'w')
		new_y -= 1;
	else if (key == 's')
		new_y += 1;
	else if (key == 'a')
		new_x -= 1;
	else if (key == 'd')
		new_x += 1;
	else
		return (0);
	game_player(game, new_x, new_y);
	return (0);
}

void	position_xy(t_game *game, int *player_x, int *player_y)
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
				*player_x = x;
				*player_y = y;
			}
			x++;
		}
		y++;
	}
}

void	game_player(t_game *game, int new_x, int new_y)
{
	if (new_x >= 0 && new_x < game->map->width && new_y >= 0
		&& new_y < game->map->height)
	{
		if (game->map->data[new_y][new_x] != '1')
		{
			if (game->map->data[new_y][new_x] == 'E' && game->collect != 0)
				return ;
			if (game->map->data[new_y][new_x] == 'E' && game->collect == 0)
			{
				game->map->data[game->player_y][game->player_x] = '0';
				game_over(game, new_x, new_y);
				return ;
			}
			if (game->map->data[new_y][new_x] == 'C')
				game->collect--;
			game->map->data[game->player_y][game->player_x] = '0';
			game->player_x = new_x;
			game->player_y = new_y;
			game->map->data[game->player_y][game->player_x] = 'P';
			game->move++;
			ft_printf("nombre de movement : %d\n", game->move);
		}
	}
	game_graphic_background(game);
	game_graphic_play(game);
}

void	game_over(t_game *game, int x, int y)
{
	game->player_x = x;
	game->player_y = y;
	game->move++;
	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, game->map->width * 32 / 2
		- ft_strlen("Misson succeed !") / 2 * 8, game->map->height * 32 / 2,
		0xFFFFFFFF, "Misson succeed ! Press ESC");
	game->over = 1;
	ft_printf("Game Over : Misson succeed ! \n");
}
