/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbertazz <fbertazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:19:27 by fbertazz          #+#    #+#             */
/*   Updated: 2019/10/17 19:54:54 by fbertazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_line(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\n')
	{
		*line = ft_strsub(*str, 0, i);
		tmp = ft_strdup((*str) + i + 1);
		free(*str);
		*str = tmp;
		if (**str == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int			ft_ret_handler(int fd, int ret, char **str, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && *(str + fd) == NULL)
		return (0);
	else
		return (ft_read_line((str + fd), line));
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	char		buff[BUFF_SIZE + 1];
	static char	*str[4864];
	char		*aux;

	if (!line || fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!*(str + fd))
			*(str + fd) = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(*(str + fd), buff);
			free(*(str + fd));
			str[fd] = aux;
		}
		if (ft_strchr(*(str + fd), '\n'))
			break ;
	}
	return (ft_ret_handler(fd, ret, str, line));
}
