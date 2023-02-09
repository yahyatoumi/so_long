#include <stdio.h>
#include "mlx.h"
#include "so_long.h"
#include <math.h>
#include "get_next_line.h"

static int count_words(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int get_word(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char *ft_word(char const *str, char c)
{
	int i;
	int len;
	char *word;

	i = 0;
	len = get_word(str, c);
	word = (char *)malloc(len + 1);
	if (!word)
		return (0);
	while (str[i] && i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

void ft_split2(char **strings, char const *s, char c, int leak)
{
	int i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			strings[i] = ft_word(s, c);
			if (!strings[i])
			{
				// leaks
				return;
			}
			i++;
			s++;
		}
		while (*s && *s != c)
			s++;
	}
}

char **ft_split(char const *s, char c)
{
	int i;
	char **strings;
	int leak;

	if (!s)
		return (0);
	i = 0;
	leak = 0;
	strings = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strings)
		return (0);
	ft_split2(strings, s, c, leak);
	if (leak)
		return (0);
	strings[count_words(s, c)] = 0;
	return (strings);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int encode_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

int mouse_move_callback(int x, int y, void *param)
{
	printf("Mouse moved to: (%d, %d)\n", x, y);
	return 0;
}

int mouse_press_callback(int button, int x, int y, void *param)
{
	double angle = atan2(y, x) * 180 / M_PI;
	printf("Mouse pressed at :(%d, %d)\n", x, y);
	return 0;
}

void free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int set_parsing_struct(t_pars *pars)
{
	int len;
	int i;

	len = ft_strlen(pars->line) - 1;
	i = 0;
	if (pars->line[0] != '1' || pars->line[len - 1] != '1' || len + 1 != pars->line_len)
		return (0);
	while (i < len)
	{
		if (pars->line[i] == 'C')
			(pars->c_char) += 1;
		else if (pars->line[i] == 'P')
			(pars->p_char) += 1;
		else if (pars->line[i] == 'E')
			(pars->e_char) += 1;
		else if (pars->line[i] != '1' && pars->line[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

void set_initial_values(t_pars *list)
{
	list->c_char = 0;
	list->e_char = 0;
	list->p_char = 0;
}

int check_last_line(t_pars *list, char *line)
{
	int i;
	int len;

	if (ft_strlen(line) != list->line_len)
		return (0);
	i = 0;
	len = ft_strlen(line) - 1;
	while (i < len)
	{
		if (line[i] != '1')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int lines_counter(char *path)
{
	int i;
	char *line;
	int fd;

	i = 0;
	fd = open(path, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		i++;
		free(line);
	}
	free(line);
	close(fd);
	return (i);
}

int is_map_valid(t_pars list)
{
	if (list.c_char <= 0)
		return (0);
	if (list.e_char != 1)
		return (0);
	if (list.p_char != 1)
		return (0);
	return (1);
}

char **check_map(char *path)
{
	t_pars pars;
	char *map;
	int i;
	char **matrice;

	i = lines_counter(path);
	map = NULL;
	pars.fd = open(path, O_RDONLY);
	pars.line = get_next_line(pars.fd);
	pars.line_len = ft_strlen(pars.line);
	if (!check_last_line(&pars, pars.line))
		return (0);
	set_initial_values(&pars);
	while (i > 1)
	{
		map = ft_strjoin(map, pars.line);
		if (!set_parsing_struct(&pars))
			return (0);
		pars.line = get_next_line(pars.fd);
		i--;
	}
	if (!check_last_line(&pars, pars.line) || !is_map_valid(pars))
		return (0);
	map = ft_strjoin(map, pars.line);
	matrice = ft_split(map, '\n');
	return (matrice);
}

int no_c_left(char **matrice)
{
	int i;
	int j;

	i = 0;
	while (matrice[i])
	{
		j = 0;
		while (matrice[i][j])
		{
			if (matrice[i][j] == 'C')
			{
				printf("i == %i j == %i\n", i + 1, j + 1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char **copy_matrice(t_vars m)
{
	int i;
	char **copy;

	copy = (char **)malloc(sizeof(m.row_len + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < m.row_len)
	{
		copy[i] = strdup(m.matrice[i]);
		if (!copy[i])
			return (0);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

void print_matrice(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("--------------------------------------\n");
}

int find_exit(int _row, int _col, t_vars *m, int *i)
{
	if (_row < 0 || _row > m->row_len || _col < 0 || _col > m->cols_len || m->matrice[_row][_col] == '1')
		return 0;
	if (m->matrice[_row][_col] == 'E')
	{
		*i = *i + 1;
		if (m->c_char + m->e_char == *i)
			return (1);
	}
	else if (m->matrice[_row][_col] == 'C')
	{
		*i = *i + 1;
		if (m->c_char + m->e_char == *i)
			return (1);
	}
	m->matrice[_row][_col] = '1';
	if (find_exit(_row - 1, _col, m, i) || find_exit(_row + 1, _col, m, i) || find_exit(_row, _col - 1, m, i) || find_exit(_row, _col + 1, m, i))
		return 1;
	return 0;
}

void chars_count(t_vars *m)
{
	int i;
	int j;

	i = 0;
	m->c_char = 0;
	m->e_char = 0;
	while (i < m->row_len)
	{
		j = 0;
		while (j < m->cols_len)
		{
			if (m->matrice[i][j] == 'C')
				m->c_char++;
			else if (m->matrice[i][j] == 'E')
				m->e_char++;
			j++;
		}
		i++;
	}
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 0 && vars->matrice[vars->playerY][vars->playerX - 1] != '1')
	{
		if (vars->matrice[vars->playerY][vars->playerX - 1] == 'C')
		{
			vars->matrice[vars->playerY][vars->playerX + 1] = 0;
			vars->c_char -= 1;
		}
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->empty_img, vars->playerX * 50, vars->playerY * 50);
		vars->playerX -= 1;
	}
	else if (keycode == 2 && vars->matrice[vars->playerY][vars->playerX + 1] != '1')
	{
		if (vars->matrice[vars->playerY][vars->playerX + 1] == 'C')
		{
			vars->matrice[vars->playerY][vars->playerX + 1] = 0;
			vars->c_char -= 1;
		}
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->empty_img, vars->playerX * 50, vars->playerY * 50);
		vars->playerX += 1;
	}
	else if (keycode == 13 && vars->matrice[vars->playerY - 1][vars->playerX] != '1')
	{
		if (vars->matrice[vars->playerY - 1][vars->playerX] == 'C')
		{
			vars->matrice[vars->playerY][vars->playerX + 1] = 0;
			vars->c_char -= 1;
		}
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->empty_img, vars->playerX * 50, vars->playerY * 50);
		vars->playerY -= 1;
	}
	else if (keycode == 1 && vars->matrice[vars->playerY + 1][vars->playerX] != '1')
	{
		if (vars->matrice[vars->playerY + 1][vars->playerX] == 'C')
		{
			vars->matrice[vars->playerY][vars->playerX + 1] = 0;
			vars->c_char -= 1;
		}
		mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->empty_img, vars->playerX * 50, vars->playerY * 50);
		vars->playerY += 1;
	}
	int img_width;
	int img_height;
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img, vars->playerX * 50, vars->playerY * 50);
	printf("c_chars == %i\n", vars->c_char);
	printf("key code == %i\n", keycode);
	return (0);
}

int main(void)
{
	t_vars vars;
	int i;

	if (!(vars.matrice = check_map("map.ber")))
	{
		write(2, "Error1\n", 7);
		return (0);
	}
	vars.row_len = 0;
	while (vars.matrice[vars.row_len])
		vars.row_len++;
	vars.row = 0;
	vars.cols_len = ft_strlen(vars.matrice[0]);
	if (!vars.cols_len)
	{
		printf("!strlen \n");
		print_matrice(vars.matrice);
		exit(1);
	}
	chars_count(&vars);
	vars.matrice2 = copy_matrice(vars);
	if (!vars.matrice2)
	{
		printf("heeere\n");
		exit(1);
	}
	while (vars.row < vars.row_len)
	{
		vars.col = 0;
		while (vars.col < vars.cols_len)
		{
			if (vars.matrice[vars.row][vars.col] == 'P')
			{
				i = 0;
				if (!find_exit(vars.row, vars.col, &vars, &i))
				{
					write(2, "ERROR2\n", 7);
					return (0);
				}
				vars.row = -1;
				break;
			}
			vars.col++;
			if (vars.row == -1)
				break;
		}
		vars.row++;
	}
	printf("can exit\n");
	printf("%i\n", vars.cols_len);
	printf("%i\n", vars.row_len);
	printf("matrie ----- \n\n\n\n");
	if ((vars.cols_len + 1) * 50 > 2500 || (vars.row_len + 1) * 50 > 1400)
	{
		write(2, "ERROR3\n", 7);
		return (0);
	}
	printf("ccccccccccccccccccccc\n");
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
	{
		printf("!!!init\n");
		exit(1);
	}
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.cols_len * 50, vars.row_len * 50, "My Game");
	if (!vars.win_ptr)
	{
		printf("!!!winnn\n");
		exit(1);
	}
	vars.img = mlx_xpm_file_to_image(vars.mlx_ptr, "./guko.xpm", &vars.img_width, &vars.img_height);
	vars.empty_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./empty.xpm", &vars.empty_width, &vars.empty_height);
	vars.c_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./ball.xpm", &vars.c_width, &vars.c_height);
	vars.e_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./exit.xpm", &vars.e_width, &vars.e_height);
	vars.wall_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./wall.xpm", &vars.wall_width, &vars.wall_height);
	if (!vars.img || !vars.empty_img || !vars.c_img || !vars.e_img || !vars.wall_img)
	{
		printf("erooooooor\n");
		exit(1);
	}
	i = 0;
	int j;
	printf("matrice ---- j == %i, i == %i\n", vars.cols_len, vars.row_len);
	while (i < vars.row_len)
	{
		j = 0;
		while (j < vars.cols_len)
		{
			if (!vars.matrice2)
			{
				printf("hohohoho\n");
				exit(1);
			}
			if (vars.matrice2[i][j] == '1')
			{
				printf("1");
				mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.wall_img, j * 50, i * 50);
			}
			else if (vars.matrice2[i][j] == 'P')
			{
				printf("p");
				vars.playerX = j;
				vars.playerY = i;
				mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img, j * 50, i * 50);
			}
			else if (vars.matrice2[i][j] == 'C')
			{
				printf("c");
				mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.c_img, j * 50, i * 50);
			}
			else if (vars.matrice2[i][j] == 'E')
			{
				printf("e");
				mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.e_img, j * 50, i * 50);
			}
			else if (vars.matrice2[i][j] == '0')
			{
				printf("0");
			}
			j++;
		}
		printf("i == %i , j == %i\n", i, j);
		printf("\n");
		i++;
	}
	printf("ccccccccccccccccccccc\n");
	printf("%i, %i\n", vars.playerX, vars.playerY);
	mlx_key_hook(vars.win_ptr, key_hook, &vars);
	mlx_loop(vars.mlx_ptr);
	return 0;
}
