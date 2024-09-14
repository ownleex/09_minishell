/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:38:10 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/13 20:11:43 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirecion(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 2)
		return (0);
	if (str[0] != '<' && str[0] != '>')
		return (0);
	if (len == 1)
		return (1);
	else if (str[0] == str[1])
		return (1);
	return (0);
}

int	is_quote(int c)
{
	return (c == '"' || c == '\'');
}

int	is_single_pipe(char *line, int p)
{
	int	line_length;

	line_length = ft_strlen(line);
	if ((p + 1 < line_length && line[p + 1] == '|') || \
	(p > 0 && line[p - 1] == '|'))
		return (0);
	if ((p + 1 < line_length && line[p + 1] == ' ') && \
	(p > 0 && line[p - 1] == ' '))
		return (0);
	return (1);
}

int	is_single_redirection(char *line, int p)
{
	int	line_length;

	line_length = ft_strlen(line);
	if (p > 0 && ((line[p - 1] == '<') || (line[p - 1] == '>')))
		return (0);
	if (p + 1 < line_length)
	{
		if ((p > 0 && line[p - 1] == ' ') && (line[p + 1] == ' '))
			return (0);
	}
	return (1);
}

int	is_separator(int character, int space)
{
	if (is_quote(character))
		return (1);
	if (character == ' ' && space)
		return (1);
	return (0);
}

void	copy_inner_content(char *dest, char *src, int start, int end)
{
	int		index;
	int		cursor;
	char	quote_type;

	index = start;
	cursor = 0;
	while (index <= end && src[index] != '\0')
	{
		if (is_quote(src[index]))
		{
			quote_type = src[index++];
			while (index <= end && src[index] != quote_type)
				dest[cursor++] = src[index++];
		}
		else
			dest[cursor++] = src[index];
		index++;
	}
	dest[cursor] = '\0';
}
