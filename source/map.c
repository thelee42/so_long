/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:52:08 by thelee            #+#    #+#             */
/*   Updated: 2024/08/30 11:57:40 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_map(char *str)
{
	int		fd;
	char	*line;
	char	*lines;

	line = NULL;
	lines = NULL;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		lines = add_line(lines, line);
		free(line);
	}
	close(fd);
	return (lines);
}

int	check_map(t_map *map, char *str)
{
	int	i;

	i = 0;
	while (map->data[i])
	{
		if (map->width != ft_strlen(map->data[i]))
			return (1);
		if (map->data[i][0] != '1')
			return (1);
		if (map->data[i][map->width - 1] != '1')
			return (1);
		i++;
	}
	if (ft_count_word(map->data[0], '1') != map->width)
		return (1);
	if (ft_count_word(map->data[map->height - 1], '1') != map->width)
		return (1);
	if (ft_count_word(str, 'P') != 1 || ft_count_word(str, 'E') != 1
		|| ft_count_word(str, 'C') < 1)
		return (1);
	if (ft_count_word(str, '1') + ft_count_word(str, '0')
		+ ft_count_word(str, 'P') + ft_count_word(str, 'C')
		+ ft_count_word(str, 'E') != map->width * map->height)
		return (1);
	return (0);
}

int	trop_grand_map(t_game *game)
{
	int	x;
	int	y;

	mlx_get_screen_size(game->mlx, &x, &y);
	if (game->map->width * 32 > x || game->map->height * 32 > y)
		return (1);
	return (0);
}

int	dfs_map(char **map, int x, int y, char bloc)
{
	int	count;

	count = 0;
	if (x < 0 || x >= ft_strlen(map[0]) || y < 0 || y >= map_height(map))
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (bloc == 'C' && map[y][x] == 'E')
		return (0);
	if (map[y][x] == bloc)
		count += 1;
	map[y][x] = 'V';
	count += dfs_map(map, x + 1, y, bloc);
	count += dfs_map(map, x - 1, y, bloc);
	count += dfs_map(map, x, y + 1, bloc);
	count += dfs_map(map, x, y - 1, bloc);
	return (count);
}

int	path_valid(t_game *game)
{
	char	**map_dup_item;
	char	**map_dup_exit;
	int		count;
	int		player_x;
	int		player_y;

	position_xy(game, &player_x, &player_y);
	map_dup_item = map_duplicat(game->map->data, game->map->height);
	count = dfs_map(map_dup_item, player_x, player_y, 'C');
	ft_free_split(map_dup_item);
	if (count != game->collect)
		return (1);
	map_dup_exit = map_duplicat(game->map->data, game->map->height);
	count = dfs_map(map_dup_exit, player_x, player_y, 'E');
	ft_free_split(map_dup_exit);
	if (count == 0)
		return (1);
	return (0);
}
