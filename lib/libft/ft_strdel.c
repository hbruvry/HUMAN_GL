/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:41:51 by hbruvry           #+#    #+#             */
/*   Updated: 2017/11/26 16:04:42 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/*
** Free string memory
*/

void	ft_strdel(char **as)
{
	void	**pas;

	pas = (void**)as;
	ft_memdel(pas);
	return ;
}