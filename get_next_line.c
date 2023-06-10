/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:26:06 by aulicna           #+#    #+#             */
/*   Updated: 2023/01/28 17:11:21 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *s)
{
	char	*buff;
	int		pst_fd;

	pst_fd = 1;
	buff = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (ft_strchr(s, '\n') == NULL && pst_fd != 0)
	{
		pst_fd = read(fd, buff, BUFFER_SIZE);
		if (pst_fd == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[pst_fd] = '\0';
		s = ft_strjoin(s, buff);
	}
	free(buff);
	return (s);
}

char	*process_current_line(char *s)
{
	char			*line;
	unsigned int	i;

	if (!s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	line = (char *) malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*save_remainder_of_line(char *s)
{
	char			*rem;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	i++;
	rem = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1 - i));
	if (!rem)
		return (NULL);
	j = 0;
	while (s[i])
		rem[j++] = s[i++];
	rem[j] = '\0';
	free(s);
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = read_fd(fd, s);
	if (!s)
		return (NULL);
	line = process_current_line(s);
	s = save_remainder_of_line(s);
	return (line);
}
