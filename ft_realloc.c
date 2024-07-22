/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:14:23 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/07 22:24:07 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	min_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else
	{
		new_ptr = malloc(new_size);
		if (new_ptr)
		{
			if (old_size < new_size)
				min_size = old_size;
			else
				min_size = new_size;
			ft_memcpy(new_ptr, ptr, min_size);
			free(ptr);
		}
		return (new_ptr);
	}
}
