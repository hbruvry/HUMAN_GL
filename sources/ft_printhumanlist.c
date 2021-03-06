/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhumanlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 10:53:18 by hbruvry           #+#    #+#             */
/*   Updated: 2020/02/28 18:21:46 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/humangl.h"

/*
** TODO
*/

void	ft_printhumanlist(t_list *l)
{
	static int	tabLength = 0;
	t_list		*ltmp;


	ltmp = l;
	if (tabLength == 0)
		ft_putstr("\033[31;1mroot\033[0m\n{\n");
	tabLength++;
	while (ltmp)
	{
		if (ltmp->content_size == sizeof(t_bone))
			ft_printbone(*((t_bone*)ltmp->content), tabLength);
		else
		{
			ft_putnchar('\t', tabLength);
			ft_putendl("\033[33;1mlist\033[0m");
			ft_putnchar('\t', tabLength);
			ft_putendl("{");
			ft_printhumanlist((t_list*)ltmp->content);
			ft_putnchar('\t', tabLength);
			ft_putendl("}");
		}
		ltmp = ltmp->next;
	}
	tabLength--;
	if (tabLength == 0)
		ft_putendl("}");
	return ;
}