/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:20:29 by hbruvry           #+#    #+#             */
/*   Updated: 2020/02/28 18:38:09 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libmath.h"

/*
** TODO
*/

t_vec3	ft_vec3sub(t_vec3 vdst, t_vec3 vsrc)
{
	int i;

	i = -1;
	while (++i < 3)
		vdst.v[i] -= vsrc.v[i];
	return (vdst);
}