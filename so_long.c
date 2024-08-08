#include    <stdlib.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    "libmlx/mlx.h"
#include    "get_next_line/get_next_line.h"
#include    "get_next_line/get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*add_line(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*stash;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	stash = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!stash)
		return (NULL);
	i = -1;
	while (s1[++i])
		stash[i] = s1[i];
	j = -1;
	while (s2[++j])
		stash[i + j] = s2[j];
	stash[i + j] = '\0';
	free(s1);
	return (stash);
}


char	*read_line(int fd, char *stash)
{
	char	*temp;
	int		len;

	len = 1;
	while (!ft_strchr(stash, '\n') && len > 0)
	{
		temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!temp)
			return (NULL);
		len = (int)read(fd, temp, BUFFER_SIZE);
		if (len == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[len] = '\0';
		stash = add_line(stash, temp);
		free(temp);
	}
	return (stash);
}

char	*get_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!*stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*next_line(char *stash)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	i++;
	temp = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!temp)
		return (NULL);
	while (stash[i + j])
	{
		temp[j] = stash[i + j];
		j++;
	}
	temp[j] = '\0';
	free(stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = next_line(stash);
	return (line);
}


int	count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count += 1;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**copy(int countword, char **dest, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[j] && i < countword)
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		dest[i] = ft_substr(s, start, j - start);
		if (!dest[i])
		{
			while (i-- >= 0)
				free(dest[i]);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		countword;

	if (s == NULL)
		return (NULL);
	countword = count(s, c);
	dest = malloc(sizeof (char *) * (countword + 1));
	if (!dest)
		return (NULL);
	dest = copy(countword, dest, s, c);
	return (dest);
}


// cc so_long.c -Llibmlx -lmlx -lX11 -lXext
// cc so_long.c -Llibmlx -lmlx -framework OpenGL -framework AppKit

typedef struct s_map
{
    int width;
    int height;
    char    **data;
}   t_map;

// struct pour game
typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img_wall;
    void    *img_ground;
    void    *img_item;
    void    *img_player;
    void    *img_exit;
    t_map   *map;
    int     player_x;
    int     player_y;
}   t_game;

int close_window(int keycode, t_game *game)
{
    if (keycode == 65307)
        mlx_destroy_window(game->mlx, game->win);
    return 0;
}

int close_x(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    return 0;
}

void    game_image(t_game *game)
{
    int w;
    int h;

    game->img_wall = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &w, &h);
    game->img_ground = mlx_xpm_file_to_image(game->mlx, "ground.xpm", &w, &h);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "player.xpm", &w, &h);
    game->img_item = mlx_xpm_file_to_image(game->mlx, "item.xpm", &w, &h);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "exit.xpm", &w, &h);
}

void    game_graphic(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < game->map->height)
    {
        while (x < game->map->width)
        {
            if (game->map->data[x][y] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->img_ground, x * 20, y * 20);
            if (game->map->data[x][y] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * 20, y * 20);
            if (game->map->data[x][y] == 'P') // ground + player
            {
                mlx_put_image_to_window(game->mlx, game->win, game->img_ground, x * 20, y * 20);
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * 20, y * 20);
            }
            if (game->map->data[x][y] == 'C') // ground + item
            {
                mlx_put_image_to_window(game->mlx, game->win, game->img_ground, x * 20, y * 20);
                mlx_put_image_to_window(game->mlx, game->win, game->img_item, x * 20, y * 20);
            }
            if (game->map->data[x][y] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x * 20, y * 20);
            x++;
        }
        y++;
    }
}

/*
void    game_map(t_game *game)
{
    char    *line;

}

char    **read_map(t_game *game, char *str)
{
    int fd;
    char *line;
    char **map;
    int height;
    
    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (perror("You've got the wrong map"), 0);
    while (line = get_next_line(fd))
    {

    }
}

void   check_map(char *str, t_map *map)
{
    int fd;

    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (perror("You've got the wrong map"));
    map->width = 0;
    map->height = 0;


    if (map->width < 3 || map->height < 3)
        return (perror("You've got the wrong map"));
}

*/

// void    read_map(t_game *game, char *str)
// {
//     int fd;
    
//     fd = open(str, O_RDONLY);
//     if (fd == -1)
//         return (perror("You've got the wrong map"));
//     game->map->height = 0;
//     while (get_next_line(fd) != NULL)
//     {
//         game->map->map = (char **)realloc(&game->map->map, game->map->height + 1);
//         game->map->map[game->map->height] = get_next_line(fd);
//         game->map->height++;
//     }
//     game->map->map[game->map->height] = NULL;
//     game->map->width = ft_strlen(game->map->map[0]);
//     close (fd);
// }

// void    read_map(t_game *game, char *str)
// {
//     int fd;
//     char *line;
    
//     fd = open(str, O_RDONLY);
//     if (fd == -1)
//         return (perror("You've got the wrong map"));
//     game->map = malloc(sizeof(t_map));
//     game->map->width = 0;
//     game->map->height = 0;
//     line = get_next_line(fd);
//     while (line != NULL)
//     {
//         game->map->data = realloc(game->map->data, sizeof(char *) * game->map->height + 1);
//         game->map->data[game->map->height] = line;
//         game->map->height++;
//         line = get_next_line(fd);
//     }
//     free(line);
//     game->map->data[game->map->height] = NULL;
//     game->map->width = ft_strlen(game->map->data[0]);
//     close (fd);
// }


// char	**read_map(t_map *map, char *str)
// {
//     int fd;
// 	int	height;
//     char *line;
// 	char **data;
    
//     fd = open(str, O_RDONLY);
//     if (fd == -1)
//         return (perror("Oops ! You've got the wrong map.."), NULL);
//     map->height = 0;
//     line = get_next_line(fd);
//     while (line != NULL)
//     { 
//         data = realloc(data, sizeof(char *) * map->height + 1);
//         data[map->height] = line;
//         map->height++;
//         line = get_next_line(fd);
//     }
//     free(line);
//     data[height] = NULL;
//     close (fd);
// 	return (data);
// }

char	*read_map(char *str)
{
	int		fd;
	char	*line;
	char	*lines;

    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (perror("Oops ! You've got the wrong map.."), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines = add_line(lines, line);
		line = get_next_line(fd);
	}
	return (lines);
}


void	init_map(t_map *map, char *str)
{
	map = malloc(sizeof(t_map));
	if (!map)
        return (perror("Oops ! You've got the wrong map.."), NULL);
	map->data = ft_split(read_map(str), '\n');
	map->height = count(read_map(str), '\n');
	map->width = ft_strlen(map->data[0]);
}

int main(int agrc, char **argv)
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (1);
    //init game 
    //map parsing
    game->mlx = mlx_init();
    game_image(game);
	    //render map
    init_map(game->map, argv[1]);
	game->win = mlx_new_window(game->mlx, 1920, 1080, "so fast");
//	game->win = mlx_new_window(game->mlx, game->map->width * 20, game->map->height * 20, "so fast");
	game_graphic(game);
    mlx_hook(game->win, 2, 1L<<0, close_window, game);
    mlx_hook(game->win, 17, 1L<<5, close_x, game);
    mlx_loop(game->mlx);
    // free game, map, game data
    free(game->map);
    free(game);

}
