/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:04:23 by ytoumi            #+#    #+#             */
/*   Updated: 2023/02/11 17:04:24 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_ber(char *path)
{
	int	len;
	int	i;

	len = ft_strlen(path);
	i = len - 4;
	return (ft_strcmp(path + i, ".ber"));
}

void	chars_count(t_vars *m)
{
	int	i;
	int	j;

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

void	key_hook_helper(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		free_arr(vars->matrice2);
		exit(0);
	}
}
