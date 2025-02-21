/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:31:57 by manbengh          #+#    #+#             */
/*   Updated: 2024/05/30 17:54:10 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	if (s)
		write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putn(unsigned int nb)
{
	if (nb / 10)
		return (ft_putn(nb / 10) + ft_putn(nb % 10));
	else
		return (ft_putchar(nb + '0'));
}

int	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb = -nb;
		return (ft_putchar('-') + ft_putn(nb));
	}
	else
		return (ft_putn(nb));
}
