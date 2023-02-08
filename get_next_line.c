/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytoumi <ytoumi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:24:58 by ytoumi            #+#    #+#             */
/*   Updated: 2023/01/06 21:56:24 by ytoumi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_read(char *str, int fd)
{
	int		rd;
	char	*buff;

	buff = (char *)malloc(1 + 1);
	if (!buff)
		return (0);
	rd = 1;
	while (!ft_strchr(str, '\n') && rd != 0)
	{
		rd = read(fd, buff, 1);
		if (rd == -1)
		{
			free(buff);
			return (0);
		}
		buff[rd] = 0;
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

static	char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*str2;

	if (!str[0])
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	str2 = (char *)malloc(i + 1);
	if (!str2)
		return (0);
	j = 0;
	while (str[j] && j < i)
	{
		str2[j] = str[j];
		j++;
	}
	str2[j] = 0;
	return (str2);
}

static	char	*ft_update(char *str)
{
	int		i;
	char	*str2;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == 0)
	{
		free(str);
		return (0);
	}
	j = 0;
	tmp = ft_strchr(str, '\n');
	str2 = ft_strdup(tmp + 1);
	if (!str2)
	{
		free(str);
		return (0);
	}
	free(str);
	return (str2);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || 1 <= 0)
		return (0);
	str = ft_read(str, fd);
	if (!str)
		return (0);
	line = ft_get_line(str);
	str = ft_update(str);
	return (line);
}
