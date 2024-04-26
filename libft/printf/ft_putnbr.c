/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:15:50 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/20 11:36:59 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <limits.h>

int	ft_putnbr(int n)
{
	int	len;

	len = 0;
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (n >= 0 && n <= 9)
		len += ft_putchar(n + 48);
	else if (n < 0)
	{
		len += ft_putchar('-');
		len += ft_putnbr(-n);
	}
	else
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	return (len);
}
