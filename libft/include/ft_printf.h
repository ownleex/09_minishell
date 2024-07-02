/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:02:09 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/01/18 05:07:53 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *input, ...);
int		ft_printstr(char *str);
int		ft_printptr(void *value);
int		ft_printint(int n);
int		ft_printuint(unsigned int n);
int		ft_printhex(unsigned long long n, char c);
int		ft_printchar(char c);

#endif
