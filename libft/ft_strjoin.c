/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:49:46 by jiyawang          #+#    #+#             */
/*   Updated: 2025/07/21 09:49:40 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s1s2_r;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s1s2_r = (char *)malloc(s1_len + s2_len + 1);
	if (!s1s2_r)
		return (NULL);
	ft_strlcpy(s1s2_r, s1, s1_len + 1);
	ft_strlcat(s1s2_r, s2, s1_len + s2_len + 1);
	return (s1s2_r);
}
