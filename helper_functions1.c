/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:36:37 by ytoumi            #+#    #+#             */
/*   Updated: 2023/02/11 16:38:16 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	set_parsing_struct(t_pars *pars)
{
	int	len;
	int	i;

	len = ft_strlen(pars->line) - 1;
	i = 0;
	if (pars->line[0] != '1'
		|| pars->line[len - 1] != '1' || len + 1 != pars->line_len)
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

void	set_initial_values(t_pars *list)
{
	list->c_char = 0;
	list->e_char = 0;
	list->p_char = 0;
}

int	check_last_line(t_pars *list, char *line)
{
	int	i;
	int	len;

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

int	lines_counter(char *path)
{
	int		i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	return (i);
}
