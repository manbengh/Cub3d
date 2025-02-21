/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autres.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:20:36 by manbengh          #+#    #+#             */
/*   Updated: 2024/05/30 17:46:53 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

// int	ft_putchar_percent(char c)
// {
// 	c = '%';
// 	return (write(1, &c, 1));
// }

int	ft_count(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_putunbr(unsigned int nb)
{
	if (nb >= 0)
		return (ft_putn(nb));
	else
	{
		nb += 4294967295;
		return (ft_putn(nb));
	}
}
