/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:32:42 by ytoumi            #+#    #+#             */
/*   Updated: 2023/02/11 16:34:17 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	main2(t_vars vars, int i)
{
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
					write(2, "Error no path to exit!\n", 23);
					free_arr(vars.matrice);
					free_arr(vars.matrice2);
					exit(1);
				}
				vars.row = -1;
				break ;
			}
			vars.col++;
			if (vars.row == -1)
				break ;
		}
		vars.row++;
	}
}

void	main1(t_vars *vars)
{
	while (vars->matrice[vars->row_len])
		vars->row_len++;
	vars->row = 0;
	vars->cols_len = ft_strlen(vars->matrice[0]);
	chars_count(vars);
	vars->matrice2 = copy_matrice(*vars);
	if (!vars->matrice2)
	{
		free_arr(vars->matrice);
		write(2, "Error Malloc failed\n", 20);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		i;

	i = 0;
	vars.matrice = check_map(av[1]);
	if (!vars.matrice || ac != 2 || ft_check_ber(av[1]))
	{
		write(2, "Error invalid map!\n", 19);
		return (0);
	}
	vars.row_len = 0;
	main1(&vars);
	main2(vars, i);
	free_arr(vars.matrice);
	if ((vars.cols_len + 1) * 50 > 2500 || (vars.row_len + 1) * 50 > 1400)
	{
		free_arr(vars.matrice2);
		write(2, "Error map is too big\n", 21);
		exit(1);
	}
	mlx_helper(&vars);
	return (0);
}
