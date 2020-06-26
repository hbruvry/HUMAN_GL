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

void	ft_printbone(t_bone b, int tablength)
{
	ft_putnchar('\t', tablength);
	ft_putstr("\033[32;1m");
	ft_putstr(b.name);
	ft_putstr("\033[0m\n");
	ft_putnchar('\t', tablength);
	ft_putendl("{");
	ft_putnchar('\t', tablength + 1);
	printf("vpos = [%.3f, %.3f, %.3f];\n", b.vpos.v[0], b.vpos.v[1], b.vpos.v[2]);
	ft_putnchar('\t', tablength + 1);
    printf("vabspos = [%.3f, %.3f, %.3f];\n", b.vabspos.v[0], b.vabspos.v[1], b.vabspos.v[2]);
	ft_putnchar('\t', tablength + 1);
	printf("vrot = [%.3f, %.3f, %.3f];\n", b.vrot.v[0], b.vrot.v[1], b.vrot.v[2]);
    ft_putnchar('\t', tablength + 1);
	printf("vabsrot = [%.3f, %.3f, %.3f];\n", b.vabsrot.v[0], b.vabsrot.v[1], b.vabsrot.v[2]);
	ft_putnchar('\t', tablength + 1);
	printf("vsize = [%.3f, %.3f, %.3f];\n", b.vsize.v[0], b.vsize.v[1], b.vsize.v[2]);
	ft_putnchar('\t', tablength);
	ft_putendl("}");
	return ;
}

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