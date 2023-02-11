/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:02:57 by ytoumi            #+#    #+#             */
/*   Updated: 2023/02/11 17:15:51 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	char_check(char c, int c_char, t_vars *vars)
{
	if (c != '1' && c != 'E' && c_char)
		return (1);
	if ((c == '0' || c == 'P') && !c_char)
		return (1);
	if (c == 'E' && !c_char)
	{
		free_arr(vars->matrice2);
		exit(0);
	}
	return (0);
}

void	ft_helper(char c, t_vars *vars, int x, int y)
{
	vars->n_moves += 1;
	ft_printf("number of moves == %i\n", vars->n_moves);
	if (c == 'C')
	{
		vars->matrice2[vars->player_y + y][vars->player_x + x] = '0';
		vars->c_char -= 1;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
		vars->empty_img, vars->player_x * 50, vars->player_y * 50);
	vars->player_x += x;
	vars->player_y += y;
}

int	key_hook(int keycode, t_vars *vars)
{
	key_hook_helper(keycode, vars);
	if (keycode == 0
		&& char_check(vars->matrice2[vars->player_y][vars->player_x - 1]
		, vars->c_char, vars))
		ft_helper(vars->matrice2[vars->player_y][vars->player_x - 1],
			vars, -1, 0);
	else if (keycode == 2
		&& char_check(vars->matrice2[vars->player_y][vars->player_x + 1]
		, vars->c_char, vars))
		ft_helper(vars->matrice2[vars->player_y][vars->player_x + 1],
			vars, 1, 0);
	else if (keycode == 13
		&& char_check(vars->matrice2[vars->player_y - 1][vars->player_x]
		, vars->c_char, vars))
		ft_helper(vars->matrice2[vars->player_y - 1][vars->player_x],
			vars, 0, -1);
	else if (keycode == 1
		&& char_check(vars->matrice2[vars->player_y + 1][vars->player_x]
		, vars->c_char, vars))
		ft_helper(vars->matrice2[vars->player_y + 1][vars->player_x],
			vars, 0, 1);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
		vars->img, vars->player_x * 50, vars->player_y * 50);
	return (0);
}

int	close_window(t_vars *vars)
{
	free_arr(vars->matrice2);
	exit(0);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
