/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:17:25 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/10 17:17:26 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) <= len)
		len = ft_strlen(s) - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	while (len > 0)
	{
		result[i] = s[i + start];
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

// int main()
// {
// 	char str[] = "0123456789";
// 	printf("%s", ft_substr(str, 9, 10));
// }