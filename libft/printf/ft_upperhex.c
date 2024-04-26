/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upperhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:52:35 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/20 11:37:15 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_upperhex(unsigned int n)
{
	char	*hex;
	int		len;

	hex = "0123456789ABCDEF";
	len = 0;
	if (n >= 16)
	{
		len += ft_upperhex(n / 16);
	}
	len += ft_putchar(hex[n % 16]);
	return (len);
}
