/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romina <romina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:17:27 by rmohamma          #+#    #+#             */
/*   Updated: 2024/04/20 11:36:13 by romina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	size_t	len;
	char	*ret;

	if (s1)
		len = ft_strlen(s1);
	if (s2)
		len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (free(ret), NULL);
	len = 0;
	while (s1 && s1[len])
	{
		ret[len] = s1[len];
		len++;
	}
	i = -1;
	while (s2 && s2[++i])
		ret[len++] = s2[i];
	ret[len] = '\0';
	return (ret);
}
