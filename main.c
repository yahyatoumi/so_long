#include "so_long.h"
#include <stdio.h>
#include "mlx.h"
#include <math.h>
#include "get_next_line.h"

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

	if (ft_strlen(line) != (size_t)list->line_len)
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

	pars.i = lines_counter(path);
	pars.map = NULL;
	pars.fd = open(path, O_RDONLY);
	pars.line = get_next_line(pars.fd);
	pars.line_len = ft_strlen(pars.line);
	if (!pars.line || !check_last_line(&pars, pars.line))
		return (0);
	set_initial_values(&pars);
	while (pars.i > 1)
	{
		pars.map = ft_strjoin(pars.map, pars.line);
		pars.line = get_next_line(pars.fd);
		if (!pars.line || !pars.map || !set_parsing_struct(&pars))
			return (0);
		pars.i--;
	}
	if (!check_last_line(&pars, pars.line) || !is_map_valid(pars) || !(pars.map = ft_strjoin(pars.map, pars.line)))
		return (0);
	pars.matrice = ft_split(pars.map, '\n');
	return (pars.matrice);
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

char **copy_matrice(t_vars m)
{
	int i;
	char **copy;

	copy = (char **)malloc(sizeof(char *) * (m.row_len + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < m.row_len)
	{
		copy[i] = ft_strdup(m.matrice[i]);
		if (!copy[i])
			return (0);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int find_exit(int _row, int _col, t_vars *m, int *i)
{
	printf("%i, %i\n", _row, _col);
	if (_row < 0 || _row > m->row_len || _col < 0 || _col > m->cols_len || m->matrice[_row][_col] == '1')
		return 0;
	if (m->matrice[_row][_col] == 'E')
	{
		*i = *i + 1;
		if (m->c_char + m->e_char == *i)
			return (1);
		return (0);
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

int char_check(char c, int c_char)
{
	if (c != '1' && c != 'E' && c_char)
		return (1);
	if ((c == '0' || c == 'P') && !c_char)
		return (1);
	if (c == 'E' && !c_char)
		exit(0);
	return (0);
}

void ft_helper(char c, t_vars *vars, int x, int y)
{
	if (c == 'C')
	{
		vars->matrice2[vars->playerY + y][vars->playerX + x] = '0';
		vars->c_char -= 1;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->empty_img, vars->playerX * 50, vars->playerY * 50);
	vars->playerX += x;
	vars->playerY += y;
}

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 0 && char_check(vars->matrice2[vars->playerY][vars->playerX - 1], vars->c_char))
		ft_helper(vars->matrice2[vars->playerY][vars->playerX - 1], vars, -1, 0);
	else if (keycode == 2 && char_check(vars->matrice2[vars->playerY][vars->playerX + 1], vars->c_char))
		ft_helper(vars->matrice2[vars->playerY][vars->playerX + 1], vars, 1, 0);
	else if (keycode == 13 && char_check(vars->matrice2[vars->playerY - 1][vars->playerX], vars->c_char))
		ft_helper(vars->matrice2[vars->playerY - 1][vars->playerX], vars, 0, -1);
	else if (keycode == 1 && char_check(vars->matrice2[vars->playerY + 1][vars->playerX], vars->c_char))
		ft_helper(vars->matrice2[vars->playerY + 1][vars->playerX], vars, 0, 1);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img, vars->playerX * 50, vars->playerY * 50);
	printf("c_chars == %i\n", vars->c_char);
	printf("key code == %i\n", keycode);
	print_matrice(vars->matrice2);
	return (0);
}

int close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int ft_check_ber(char *path)
{
	int len;
	int i;

	len = ft_strlen(path);
	i = len - 4;
	printf("%s\n", path + i);
	return (ft_strcmp(path + i, ".ber"));
}

int mlx_helper4(t_vars vars, int i, int j)
{
	if (vars.matrice2[i][j] == '1')
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.wall_img, j * 50, i * 50);
	else if (vars.matrice2[i][j] == 'C')
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.c_img, j * 50, i * 50);
	else if (vars.matrice2[i][j] == 'P')
	{
		vars.playerX = j;
		vars.playerY = i;
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img, j * 50, i * 50);
	}
	else if (vars.matrice2[i][j] == 'E')
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.e_img, j * 50, i * 50);
	return (1);
}

int mlx_helper3(t_vars vars)
{
	int i;
	int j;

	i = 0;
	while (i < vars.row_len)
	{
		j = 0;
		while (j < vars.cols_len)
		{
			mlx_helper4(vars, i, j);
			j++;
		}
		i++;
	}
	mlx_hook(vars.win_ptr, 2, 0, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, close_window, 0);
	mlx_loop(vars.mlx_ptr);
	return (1);
}

int mlx_helper2(t_vars vars)
{
	if (!vars.img || !vars.empty_img || !vars.c_img || !vars.e_img || !vars.wall_img)
	{
		write(2, "eroor mlx_xpm_file_to_image failed!!\n", 37);
		exit(1);
	}
	mlx_helper3(vars);
	return (1);
}

int mlx_helper(t_vars vars)
{
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
	{
		printf("!!!init\n");
		exit(1);
	}
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.cols_len * 50, vars.row_len * 50, "My Game");
	if (!vars.win_ptr)
	{
		printf("!!!winn\n");
		exit(1);
	}
	vars.img = mlx_xpm_file_to_image(vars.mlx_ptr, "./guko.xpm", &vars.img_width, &vars.img_height);
	vars.empty_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./empty.xpm", &vars.empty_width, &vars.empty_height);
	vars.c_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./ball.xpm", &vars.c_width, &vars.c_height);
	vars.e_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./exit.xpm", &vars.e_width, &vars.e_height);
	vars.wall_img = mlx_xpm_file_to_image(vars.mlx_ptr, "./wall.xpm", &vars.wall_width, &vars.wall_height);
	mlx_helper2(vars);
	return (1);
}

int main(int ac, char **av)
{
	t_vars vars;
	int i;

	if (ac != 2 || ft_check_ber(av[1]) || !(vars.matrice = check_map(av[1])))
	{
		write(2, "Error1\n", 7);
		return (0);
	}
	vars.row_len = 0;
	while (vars.matrice[vars.row_len])
		vars.row_len++;
	vars.row = 0;
	vars.cols_len = ft_strlen(vars.matrice[0]);
	chars_count(&vars);
	vars.matrice2 = copy_matrice(vars);
	if (!vars.matrice2)
	{
		write(2, "Error Malloc failed\n", 20);
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
					write(2, "ERROR Cant't exit\n", 18);
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
	if ((vars.cols_len + 1) * 50 > 2500 || (vars.row_len + 1) * 50 > 1400)
	{
		write(2, "ERROR3\n", 7);
		return (0);
	}
	mlx_helper(vars);
	return 0;
}
