/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:50:44 by thelee            #+#    #+#             */
/*   Updated: 2024/09/10 19:44:47 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../libmlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int		width;
	int		height;
	char	**data;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_ground;
	void	*img_item;
	void	*img_player;
	void	*img_exit;
	t_map	*map;
	int		player_x;
	int		player_y;
	int		collect;
	int		move;
	int		over;
}			t_game;

/* * * graphic * * */
void		game_image(t_game *game);
void		game_graphic_background(t_game *game);
void		game_graphic_play(t_game *game);
void		message_graphic(t_game *game);

/* * * map * * */
char		*read_map(char *str);
int			check_map(t_map *map, char *str);
int			trop_grand_map(t_game *game);
int			dfs_map(char **map, int x, int y, char bloc);
int			path_valid(t_game *game);

/* * * play * * */
int			key_hook(int key, t_game *game);
void		position_xy(t_game *game, int *player_x, int *player_y);
void		game_player(t_game *game, int new_x, int new_y);
void		game_over(t_game *game, int x, int y);

/* * * so long * * */
int			close_x(t_game *game);
void		close_game(t_game *game);
void		init_game(t_game *game);
void		init_map(t_game *game, char *str);
int			main(int argc, char **argv);

/* * * utils * * */
int			map_height(char **map);
void		free_error(t_game *game);
char		**map_duplicat(char **map, int height);
void		free_images(t_game *game);
int			vide_check(char *line);

#endif