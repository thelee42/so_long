#include    <stdlib.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    "libmlx/mlx.h"
#include    "../get_next_line/get_next_line.h"

// cc so_long.c -Llibmlx -lmlx -lX11 -lXext 
// cc so_long.c -Llibmlx -lmlx -framework OpenGL -framework AppKit

typedef struct s_map
{
    int width;
    int height;
    char    **map;
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

int close(int keycode, t_game *game)
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
            if (game->map->map[x][y] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->img_ground, x * 20, y * 20);
            if (game->map->map[x][y] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * 20, y * 20);
            if (game->map->map[x][y] == 'P') // ground + player
            {
                mlx_put_image_to_window(game->mlx, game->win, game->img_ground, x * 20, y * 20);
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * 20, y * 20);
            }
            if (game->map->map[x][y] == 'C') // ground + item
            {
                mlx_put_image_to_window(game->mlx, game->win, game->img_ground, x * 20, y * 20);
                mlx_put_image_to_window(game->mlx, game->win, game->img_item, x * 20, y * 20);
            }
            if (game->map->map[x][y] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x * 20, y * 20);
            x++;
        }
        y++;
    }
}

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
        return (perror("You've got the wrong map"));
    while (line = get_next_line(fd))
    {

    }
}

void    read_map(t_game *game, char *str)
{
    int fd;
    char *line;
    
    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (perror("You've got the wrong map"));
    game->map->height = 0;
    while (line = get_next_line(fd) != NULL)
    {
        game->map->map = (char **)realloc()
        game->map->map[game->map->height] = line;
        game->map->height++;
    }
}

int main(int agrc, char **argv)
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    if (!game)
        return (perror("Oops ! Something got wrong.."), 1);
    //init game 
    //map parsing
    game->mlx = mlx_init();
    game_image(game);
    game->win = mlx_new_window(game->mlx, game->map->width * 20, game->map->height * 20, "so fast");
    //render map
    mlx_hook(game->win, 2, 1L<<0, close, game);
    mlx_hook(game->win, 17, 1L<<5, close_x, game);
    mlx_loop(game->mlx);
    // free game, map, game data
    free(game->map);
    free(game);

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



