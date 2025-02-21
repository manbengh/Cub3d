/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <manbengh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:24:22 by manbengh          #+#    #+#             */
/*   Updated: 2024/05/30 17:46:40 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_conversion(const char *format, va_list *args)
{
	int	len;

	len = 0;
	if (*format == 'c')
		len = ft_putchar(va_arg(*args, int));
	else if (*format == 's')
		len = ft_putstr(va_arg(*args, char *));
	else if (*format == 'd')
		len = ft_putnbr(va_arg(*args, int));
	else if (*format == 'i')
		len = ft_putnbr(va_arg(*args, int));
	else if (*format == 'u')
		len = ft_putunbr(va_arg(*args, unsigned int));
	else if (*format == 'x')
		len = ft_hexa_min(va_arg(*args, unsigned int));
	else if (*format == 'X')
		len = ft_hexa_maj(va_arg(*args, unsigned int));
	else if (*format == 'p')
		len = ft_hexa_ptr(va_arg(*args, uintptr_t));
	else if (*format == '%')
		return ((int)write(1, "%", 1));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	len = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_conversion(&format[i + 1], &args);
			i += 2;
		}
		else
		{
			len += ft_putchar(format[i]);
			i++;
		}
	}
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	int i;
// 	int j;
// 	i = printf("%s", "hello");
// 	j = ft_printf("%s", "hello");
// 	printf("%d %d", i, j);
// }
// int	main(void)
// {
// 	char *test = NULL;
// 	int i = 0;
// 	i = ft_printf("%s%s%s%s", "test", "test", "test", "tetst");
// 	printf("%s%s%s%s", "test", "test", "test", "tetst");
// 	printf("%i", i);
// }