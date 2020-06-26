/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3namedprint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:15:32 by hbruvry           #+#    #+#             */
/*   Updated: 2020/02/28 18:15:35 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libmath.h"

/*
** TODO
*/

void	ft_vec3namedprint(char *name, t_vec3 vec)
{
	int i;

	i = -1;
	while (++i < 3)
		printf("%s[%d] = %f;\n", name, i, vec.v[i]);
	return ;
}
