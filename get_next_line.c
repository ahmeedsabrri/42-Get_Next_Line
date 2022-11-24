/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:09:38 by asabri            #+#    #+#             */
/*   Updated: 2022/11/23 22:09:39 by asabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char    *ft_update_buffer(char *buffer)
{
    char    *res;
    int     i;
    int     j;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    res = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
    i++;
    j = 0;
    while (buffer[i])
        res[j++] = buffer[i++];
    free(buffer);
    return (res);
}

char    *ft_line(char *buffer)
{
    char *line;
    int i;

    i = 0;
    if (!buffer[i])
		return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    line = ft_calloc((i + 2), sizeof(char));
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer [i] && buffer[i] == '\n')
        line[i++] = '\n';
    return (line);
}

char    *ft_free_buffer(char *buffer, char *buf)
{
    char    *tmp;

    tmp = ft_strjoin(buffer, buf);
    free(buffer);
    return (tmp);
}

char    *ft_read(int fd, char *buffer)
{
    char    *buf;
    int     byte_read;

    if (!buffer)
		buffer = ft_calloc(1 ,sizeof(char));
    buf = ft_calloc((BUFFER_SIZE + 1) ,sizeof(char));
    byte_read = 1;
    while (byte_read > 0)
    {
        byte_read = read(fd, buf, BUFFER_SIZE);
        if (byte_read == -1)
        {
            free(buf);
            return (NULL);
        }
        buf[byte_read] = 0;       
        buffer = ft_free_buffer(buffer, buf);
        if (ft_strchr(buf, '\n'))
            break;
    }
    free(buf);
    return (buffer);
}

char	*get_next_line(int fd)
{
    static char *buffer;
    char        *line;

    if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (free(buffer), buffer = NULL);
    buffer = ft_read(fd, buffer);
    if (!buffer)
        return (NULL);
    line = ft_line(buffer);
    buffer = ft_update_buffer(buffer);
    return (line);
}