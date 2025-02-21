/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:09:05 by manbengh          #+#    #+#             */
/*   Updated: 2024/05/30 17:46:28 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_hexa_min(unsigned int n)
{
	if (n >= 16)
		return (ft_hexa_min(n / 16) + ft_hexa_min(n % 16));
	else if ((n <= 9) && (n >= 0))
		ft_putchar(n + '0');
	else
		ft_putchar((char)n - 10 + 'a');
	return (1);
}

int	ft_hexa_maj(unsigned int n)
{
	if (n >= 16)
		return (ft_hexa_maj(n / 16) + ft_hexa_maj(n % 16));
	else if ((n <= 9) && (n >= 0))
		ft_putchar(n + '0');
	else
		ft_putchar((char)n - 10 + 'A');
	return (1);
}

int	ft_hexa_min_ptr(unsigned long long n)
{
	if (n >= 16)
		return (ft_hexa_min_ptr(n / 16) + ft_hexa_min_ptr(n % 16));
	else if ((n <= 9) && (n >= 0))
		ft_putchar(n + '0');
	else
		ft_putchar((char)n - 10 + 'a');
	return (1);
}

int	ft_hexa_ptr(uintptr_t n)
{
	if (n == 0)
		return (ft_putstr("(nil)"));
	else
	{
		return (ft_putstr("0x") + ft_hexa_min_ptr(n));
	}
}

// int	main(void)
// {
// 	printf("%X\n", ft_hexa_maj('Z'));
// 	printf("%X\n", 'Z');
// }