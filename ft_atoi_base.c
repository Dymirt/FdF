/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:02:40 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/13 16:31:55 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		j = 0;
		while (base[j] && base[j] != str[i])
			j++;
		if (base[j] == str[i])
			res = res * ft_strlen(base) + j;
		i++;
	}
	return (res);
}
