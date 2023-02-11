/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:16:58 by ytoumi            #+#    #+#             */
/*   Updated: 2023/02/11 17:16:59 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mlx_helper4(t_vars *vars, int i, int j)
{
	if (vars->matrice2[i][j] == '1')
		mlx_put_image_to_window(vars->mlx_ptr,
			vars->win_ptr, vars->wall_img, j * 50, i * 50);
	else if (vars->matrice2[i][j] == 'C')
		mlx_put_image_to_window(vars->mlx_ptr,
			vars->win_ptr, vars->c_img, j * 50, i * 50);
	else if (vars->matrice2[i][j] == 'P')
	{
		vars->player_x = j;
		vars->player_y = i;
		mlx_put_image_to_window(vars->mlx_ptr,
			vars->win_ptr, vars->img, j * 50, i * 50);
	}
	else if (vars->matrice2[i][j] == 'E')
		mlx_put_image_to_window(vars->mlx_ptr,
			vars->win_ptr, vars->e_img, j * 50, i * 50);
	return (1);
}

int	mlx_helper3(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->row_len)
	{
		j = 0;
		while (j < vars->cols_len)
		{
			mlx_helper4(vars, i, j);
			j++;
		}
		i++;
	}
	vars->n_moves = 0;
	mlx_hook(vars->win_ptr, 2, 0, key_hook, vars);
	mlx_hook(vars->win_ptr, 17, 0, close_window, vars);
	mlx_loop(vars->mlx_ptr);
	return (1);
}

int	mlx_helper2(t_vars *vars)
{
	vars->img = mlx_xpm_file_to_image(vars->mlx_ptr,
			"./pics/guko.xpm", &vars->img_width, &vars->img_height);
	vars->empty_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			"./pics/empty.xpm", &vars->empty_width, &vars->empty_height);
	vars->c_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			"./pics/ball.xpm", &vars->c_width, &vars->c_height);
	vars->e_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			"./pics/exit.xpm", &vars->e_width, &vars->e_height);
	vars->wall_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			"./pics/wall.xpm", &vars->wall_width, &vars->wall_height);
	if (!vars->img || !vars->empty_img || !vars->c_img
		|| !vars->e_img || !vars->wall_img)
	{
		free_arr(vars->matrice2);
		write(2, "eroor mlx_xpm_file_to_image failed!!\n", 37);
		exit(1);
	}
	mlx_helper3(vars);
	return (1);
}

int	mlx_helper(t_vars *vars)
{
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
	{
		free_arr(vars->matrice2);
		write(2, "Error init failed\n", 18);
		exit(1);
	}
	vars->win_ptr = mlx_new_window(vars->mlx_ptr,
			vars->cols_len * 50, vars->row_len * 50, "My Game");
	if (!vars->win_ptr)
	{
		free_arr(vars->matrice2);
		write(2, "Error win failed\n", 17);
		exit(1);
	}
	mlx_helper2(vars);
	return (1);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	double_free(s1, s2);
	return (str);
}
