/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lowerhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:53:19 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/20 11:36:34 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_lowerhex(unsigned long n)
{
	char	*hex;
	int		len;

	hex = "0123456789abcdef";
	len = 0;
	if (n >= 16)
	{
		len += ft_lowerhex(n / 16);
	}
	len += ft_putchar(hex[n % 16]);
	return (len);
}
