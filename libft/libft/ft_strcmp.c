/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:06:47 by rmohamma          #+#    #+#             */
/*   Updated: 2024/05/19 16:32:14 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
