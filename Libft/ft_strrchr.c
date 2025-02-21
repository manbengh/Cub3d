/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:26:55 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/13 14:26:57 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (unsigned char )c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}

/*int main()
{
	char str[] = "hellooword";
	printf("vrai : %s \n", strrchr(str, 'o'));
	printf("%s \n", ft_strrchr(str, 'o'));
}*/