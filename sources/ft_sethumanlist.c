/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sethumanlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:06:38 by hbruvry           #+#    #+#             */
/*   Updated: 2020/03/02 16:17:20 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/humangl.h"

t_bone  ft_setbone(char *name, t_vec3 vpos, t_vec3 vrot, t_vec3 vsize)
{
	t_bone  b;
	
	b.name = ft_strdup(name);
	b.vpos = ft_vec3cpy(&(b.vpos), vpos);
	b.vabspos = ft_vec3cpy(&(b.vabspos), vpos);
	b.vrot = ft_vec3cpy(&(b.vrot), vrot);
	b.vabsrot = ft_vec3cpy(&(b.vabsrot), vrot);
	b.vsize = ft_vec3cpy(&(b.vsize), vsize);
	return (b);
}

/*
** TODO
*/

void	ft_sethumanlist(t_list  **lhuman)
{
	t_bone  bone;

	bone = ft_setbone("leftThigh",
				ft_vec3set(0.f, 0.f, 0.f),
				ft_vec3set(M_PI * 0.5f, 0.f, 0.f),
				ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(lhuman, &bone, sizeof(bone));
	bone = ft_setbone("torso",
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(M_PI * 0.5f, 0.f, 0.f),
					ft_vec3set(1.5f, 3.f, 0.75f));
	ft_lfill(lhuman, &bone, sizeof(bone));
	bone = ft_setbone("head",
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(1.f, 2.f, 1.f));
	ft_lfill(lhuman, &bone, sizeof(bone));
	ft_printhumanlist(*lhuman);
	return ;
}

/*
	bone = ft_setbone("leftCalf",
					ft_vec3set(-0.5f, -1.5f - offset, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	bone = ft_setbone("leftThigh",
					ft_vec3set(-0.5f, -3.5f - 2.f * offset, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	ft_lfill(lhuman, list, sizeof(*list));

	// Right leg

	list = NULL;
	bone = ft_setbone("rightCalf",
					ft_vec3set(0.5f, -1.5f - offset, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	bone = ft_setbone("rightThigh",
					ft_vec3set(0.5f, -3.5f - 2.f * offset, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	ft_lfill(lhuman, list, sizeof(*list));

	// Left arm

	list = NULL;
	bone = ft_setbone("leftForeArm",
					ft_vec3set(-1.f - offset, 1.5f, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	bone = ft_setbone("leftArm",
					ft_vec3set(-1.f - offset, -0.5f - offset, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	ft_lfill(lhuman, list, sizeof(*list));

	// Right arm

	list = NULL;
	bone = ft_setbone("rightForeArm",
					ft_vec3set(1.f + offset, 1.5f, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	bone = ft_setbone("rightArm",
					ft_vec3set(1.f + offset, -0.5f - offset, 0.f),
					ft_vec3set(0.f, 0.f, 0.f),
					ft_vec3set(0.5f, 2.f, 0.5f));
	ft_lfill(&list, &bone, sizeof(bone));
	ft_lfill(lhuman, list, sizeof(*list));
*/