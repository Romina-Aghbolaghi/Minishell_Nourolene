/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:21:40 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/20 11:36:43 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	ft_point(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	else if (nb > 0)
	{
		len += ft_putstr("0x") + ft_lowerhex(nb);
	}
	return (len);
}
