/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:40:28 by ytoumi            #+#    #+#             */
/*   Updated: 2023/02/11 16:50:14 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_map_valid(t_pars list)
{
	if (list.c_char <= 0)
		return (0);
	if (list.e_char != 1)
		return (0);
	if (list.p_char != 1)
		return (0);
	return (1);
}

int	check_map0(t_pars *pars, char *path)
{
	pars->i = lines_counter(path);
	pars->map = NULL;
	pars->fd = open(path, O_RDONLY);
	pars->line = get_next_line(pars->fd);
	pars->line_len = ft_strlen(pars->line);
	if (!pars->line || !check_last_line(pars, pars->line))
	{
		free(pars->line);
		return (0);
	}
	set_initial_values(pars);
	return (1);
}

char	**check_map(char *path)
{
	t_pars	pars;

	if (!check_map0(&pars, path))
		return (0);
	while (pars.i > 1)
	{
		pars.map = ft_strjoin2(pars.map, pars.line);
		pars.line = get_next_line(pars.fd);
		if (!pars.line || !pars.map || !set_parsing_struct(&pars))
			return (0);
		pars.i--;
	}
	pars.map = ft_strjoin(pars.map, pars.line);
	if (!check_last_line(&pars, pars.line) || !is_map_valid(pars) || !pars.map)
		return (0);
	pars.matrice = ft_split(pars.map, '\n', pars);
	return (pars.matrice);
}

char	**copy_matrice(t_vars m)
{
	int		i;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (m.row_len + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < m.row_len)
	{
		copy[i] = ft_strdup(m.matrice[i]);
		if (!copy[i])
		{
			free_arr(copy);
			return (0);
		}
		i++;
	}
	copy[i] = 0;
	return (copy);
}

int	find_exit(int _row, int _col, t_vars *m, int *i)
{
	if (_row < 0 || _row > m->row_len || _col < 0
		|| _col > m->cols_len || m->matrice[_row][_col] == '1')
		return (0);
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
	if (find_exit(_row - 1, _col, m, i) || find_exit(_row + 1, _col, m, i)
		|| find_exit(_row, _col - 1, m, i) || find_exit(_row, _col + 1, m, i))
		return (1);
	return (0);
}
