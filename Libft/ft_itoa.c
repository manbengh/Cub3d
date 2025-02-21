/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:51:03 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/20 14:51:05 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_numb(long int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_zero(char *str)
{
	str = malloc(2 * (sizeof(char)));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	nb;
	char		*str;

	nb = n;
	i = len_numb(nb);
	str = NULL;
	if (nb == 0)
		return (ft_zero(str));
	str = malloc((len_numb(nb) + 1) * sizeof(char));
	if (!str)
		return (0);
	str[i--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	return (str);
}

/*int main(){
	int s = -21;
	char *str = ft_itoa(s);
	printf("%s", str);
	free(str);
}*/