/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:48:01 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/02/05 17:10:06 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

int	ft_next(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i++])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*ft_print_line(char **str)
{
	size_t	back_n;
	char	*line;
	char	*temp_str;

	if (!*str)
		return (NULL);
	temp_str = *str;
	back_n = 0;
	while (temp_str[back_n] && temp_str[back_n] != '\n')
		back_n++;
	if (temp_str[back_n] == '\n')
		back_n++;
	line = ft_strndup(temp_str, back_n);
	*str = ft_strndup(temp_str + back_n, gnl_strlen(temp_str + back_n));
	free(temp_str);
	temp_str = NULL;
	return (line);
}

void	*ft_cleanup(char **str, char **buffer)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*buffer;
	int			n_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!ft_next(str))
	{
		n_read = 1;
		while (n_read > 0)
		{
			n_read = read(fd, buffer, BUFFER_SIZE);
			if (n_read < 0)
				return (ft_cleanup(&str, &buffer));
			buffer[n_read] = '\0';
			str = gnl_strjoin(str, buffer);
			if (ft_next(str))
				break ;
		}
	}
	free(buffer);
	return (ft_print_line(&str));
}

/*
int	main()
{
	int		fd;
	char	*line;

	// Ouverture du fichier en lecture seule
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return 1;
	}

	// Lecture et affichage de chaque ligne du fichier
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	// Fermeture du fichier
	close(fd);
	return 0;
}
*/
