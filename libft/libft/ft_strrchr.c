/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:29:10 by rmohamma          #+#    #+#             */
/*   Updated: 2022/11/22 16:23:52 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*to_find;

	to_find = NULL;
	while (*s)
	{
		if (*s == (char)c)
			to_find = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (to_find);
}
/*
#include <stdio.h>

int	main(void)
{
	int	c;

	c = 'w';
	char s[] = "hello world";
	printf("%s\n", ft_strrchr(s, c));
}
*/
