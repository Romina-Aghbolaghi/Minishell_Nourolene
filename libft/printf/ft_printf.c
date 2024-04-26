/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:18:04 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/20 11:36:51 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdarg.h>

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		res;

	len = 0;
	res = 0;
	va_start(args, format);
	while (format[len])
	{
		if (format[len] == '%' && ft_strchr("cspdiuxX%", format[len + 1]))
		{
			res += ft_printbase(format, len, args);
			len++;
		}
		else
			res += ft_putchar(format[len]);
		len++;
	}
	va_end(args);
	return (res);
}
