/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelee <thelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:51:05 by thelee            #+#    #+#             */
/*   Updated: 2024/09/10 19:44:33 by thelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_ground)
		mlx_destroy_image(game->mlx, game->img_ground);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_item)
		mlx_destroy_image(game->mlx, game->img_item);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
}

int	map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height] != NULL)
		height++;
	return (height);
}

void	free_error(t_game *game)
{
	ft_printf("Error\nOops ! Some map got wrong\n");
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->map);
	free(game);
	exit(0);
}

char	**map_duplicat(char **map, int height)
{
	int		i;
	char	**dup;

	i = 0;
	dup = (char **)malloc(sizeof(char *) * (height + 1));
	if (!dup)
		return (NULL);
	while (i < height)
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[height] = NULL;
	return (dup);
}

int	vide_check(char *line)
{
	int	end;
	int	i;

	i = 0;
	end = ft_strlen(line);
	if (line[0] == '\n' || line[end - 1] == '\n')
		return (1);
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
