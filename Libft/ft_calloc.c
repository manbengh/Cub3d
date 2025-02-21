/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manbengh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:30:29 by manbengh          #+#    #+#             */
/*   Updated: 2023/11/09 14:30:31 by manbengh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count * size > 65535 || (count > 65535
			&& size > 65535))
		return (NULL);
	str = malloc(count * size);
	if (str != NULL)
	{
		ft_bzero(str, count * size);
		return (str);
	}
	return (NULL);
}
