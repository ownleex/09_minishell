/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:08:38 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:09:53 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	len;

	if (*str2 == '\0')
		return ((char *)str1);
	i = 0;
	len = ft_strlen(str2);
	while (str1[i] && i + len <= n)
	{
		if (ft_strncmp(str1 + i, str2, len) == 0)
			return ((char *)str1 + i);
		i++;
	}
	return (NULL);
}

/*
int main(void)
{
    const char *haystack = "Hello, World!";
    const char *needle = "World!";
    size_t len = 40;

    char *result = ft_strnstr(haystack, needle, len);
    if (result != NULL)
    {
	printf("Cherche '%s' dans '%s' dans les %ld 1er caracteres.\n", \
		needle, haystack, len);
	printf("Resultat: %s\n", result);
    }
    else
    {
	printf("Ne trouve pas '%s' dans '%s' dans les %ld 1er caracteres.\n", \
		needle, haystack, len);
    }

    return 0;
}
*/
