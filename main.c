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
				while (i >= 0)
					free(strings[i--]);
				leak = 1;
				free(strings);
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

int key_hook(int keycode, t_vars *vars)
{
	printf("key code == %i\n", keycode);
	return (0);
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

void	free_arr(char **arr)
{
	int	i;

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
	free(line);
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

char **copy_matrice(t_matrice m)
{
	int i;
	char **copy;

	copy = (char **)malloc(sizeof(m.row_len + 1));
	i = 0;
	while (m.row_len > 0)
	{
		copy[i] = ft_strdup(m.matrice[i]);
		i++;
		m.row_len--;
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

int find_exit(int _row, int _col, t_matrice *m, int *i)
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

void chars_count(t_matrice *m)
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

int main(void)
{
	// t_vars vars;
	// t_data data;

	t_matrice m;
	int i;
	char **copy;

	if (!(m.matrice = check_map("map.ber")))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	m.row_len = 0;
	while (m.matrice[m.row_len])
		m.row_len++;
	m.row = 0;
	m.cols_len = ft_strlen(m.matrice[0]);
	chars_count(&m);
	copy = copy_matrice(m);
	while (m.row < m.row_len)
	{
		m.col = 0;
		while (m.col < m.cols_len)
		{
			if (m.matrice[m.row][m.col] == 'P')
			{
				i = 0;
				if (!find_exit(m.row, m.col, &m, &i))
				{
					write(2, "ERROR\n", 6);
					return (0);
				}
				m.row = -1;
				break;
			}
			m.col++;
			if (m.row == -1)
				break;
		}
		m.row++;
	}
	m.matrice = copy;
	printf("can exit\n");
	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, 1920, 1080, "so_long");
	// data.img = mlx_new_image(vars.mlx, 1920, 1080);
	// data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
	// 							  &data.endian);
	// my_mlx_pixel_put(&data, 5, 5, encode_rgb(255, 0, 0));
	// mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	// mlx_hook(vars.win, 4, 0, mouse_press_callback, NULL);
	// mlx_loop(vars.mlx);
	return 0;
}
