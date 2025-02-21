/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:56:33 by manbengh          #+#    #+#             */
/*   Updated: 2024/04/25 20:57:12 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill_line_buffer(int fd, char *char_left, char *buffer)
{
	char	*tempo;
	int		read_f;

	read_f = 1;
	while (read_f > 0)
	{
		read_f = read(fd, buffer, BUFFER_SIZE);
		if (read_f == -1)
		{
			free(char_left);
			free(buffer);
			return (NULL);
		}
		else if (read_f == 0)
			break ;
		buffer[read_f] = 0;
		if (!char_left)
			char_left = ft_strdup("");
		tempo = char_left;
		char_left = ft_strjoin(tempo, buffer);
		free(tempo);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (char_left);
}

char	*set_end_line(char *line_buffer)
{
	size_t	i;
	char	*char_left;

	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[1] == '\0')
		return (NULL);
	char_left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*char_left == 0)
	{
		free(char_left);
		return (NULL);
	}
	line_buffer[i + 1] = '\0';
	return (char_left);
}

char	*get_next_line(int fd)
{
	static char	*char_left;
	char		*line;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(char_left);
		free(buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, char_left, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	char_left = set_end_line(line);
	return (line);
}

// int	main(void)
// {
// 	int i;
// 	int fd;
// 	char *str;

// 	i = 0;
// 	fd = open("test", O_RDONLY);
// 	while (i < 1)
// 	{
// 		str = (get_next_line(fd));
// 		printf("%s", str);
// 		free(str);
// 		i++;
// 	}
// }
