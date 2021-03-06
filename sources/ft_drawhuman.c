/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawshuman.c                                       :+:      :+:    :+:   */
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
** glVertexAttribPointer(0, size, type, normalizedn stride, arraybufferoffset);
*/

void	ft_drawvertexbuffer(int fcount)
{
	t_ogl	*o;

	o = ft_getopengl();
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, o->vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, o->normalbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, o->uvbuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->elementbuffer);
	glDrawElements(GL_TRIANGLES, fcount, GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	return ;
}

/*
** TODO
*/

t_vec3	ft_vec3getbonetranslation(t_vec3 vrot, t_vec3 vpos)
{
	t_vec3	vcos;
	t_vec3	vsin;
	t_vec3	vleft;
	t_vec3	vup;
	t_vec3	vforward;
	t_vec3	vtrans;

	vcos = ft_vec3set(cos(vrot.v[0]), cos(vrot.v[1]), cos(vrot.v[2]));
	vsin = ft_vec3set(sin(vrot.v[0]), sin(vrot.v[1]), sin(vrot.v[2]));
	vleft = ft_vec3norm(ft_vec3set(vcos.v[1] * vcos.v[2],
					vsin.v[0] * vsin.v[1] * vcos.v[2] + vcos.v[0] * vsin.v[2],
					-vcos.v[0] * vsin.v[1] * vcos.v[2] + vsin.v[0] * vsin.v[2]));
	vup = ft_vec3norm(ft_vec3set(-vcos.v[1] * vsin.v[2],
					-vsin.v[0] * vsin.v[1] * vsin.v[2] + vcos.v[0] * vcos.v[2],
					vcos.v[0] * vsin.v[1] * vsin.v[2] + vsin.v[0] * vcos.v[2]));
	vforward = ft_vec3norm(ft_vec3set(vsin.v[2],
					-vsin.v[0] * vcos.v[1],
					vcos.v[0] * vcos.v[1]));
	vtrans = ft_vec3cpy(&vtrans, ft_vec3scalar(vleft, vpos.v[0]));
	vtrans = ft_vec3add(vtrans, ft_vec3scalar(vup, vpos.v[1]));
	vtrans = ft_vec3add(vtrans, ft_vec3scalar(vforward, vpos.v[2]));
	return (vtrans);
}

/*
** TODO
*/

t_vec3	ft_vec3getboneoffset(t_vec3 vrot, float height)
{
	t_vec3	vcos;
	t_vec3	vsin;
	t_vec3	vup;
	t_vec3	voffset;

	vcos = ft_vec3set(cos(vrot.v[0]), cos(vrot.v[1]), cos(vrot.v[2]));
	vsin = ft_vec3set(sin(vrot.v[0]), sin(vrot.v[1]), sin(vrot.v[2]));
	vup = ft_vec3norm(ft_vec3set(-vcos.v[1] * vsin.v[2],
					-vsin.v[0] * vsin.v[1] * vsin.v[2] + vcos.v[0] * vcos.v[2],
					vcos.v[0] * vsin.v[1] * vsin.v[2] + vsin.v[0] * vcos.v[2]));
	voffset = ft_vec3cpy(&voffset, ft_vec3scalar(vup, height));
	return (voffset);
}

/*
** TODO
*/

t_mat4	ft_mat4boneset(t_vec3 *vlrot, t_vec3 *vlpos, t_bone *bone)
{
	t_mat4	mat;
	t_vec3	vrot;
	t_vec3	vtrans;
	t_vec3	voffset;
	t_vec3	vpos;

	vrot = ft_vec3cpy(&vrot, *vlrot);
	vrot = ft_vec3add(vrot, bone->vrot);
	vtrans = ft_vec3getbonetranslation(*vlrot, bone->vpos);
	voffset = ft_vec3getboneoffset(vrot, bone->vsize.v[1] * 0.5f);
	vpos = ft_vec3cpy(&vpos, *vlpos);
	vpos = ft_vec3add(vpos, vtrans);
	vpos = ft_vec3add(vpos, voffset);
	ft_mat4set(&mat, IDENTITY);
	mat = ft_mat4transform(mat,
		bone->vsize,
		vrot,
		vpos);
	bone->vabsrot = ft_vec3cpy(&bone->vabsrot, vrot);
	bone->vabspos = ft_vec3cpy(&bone->vabsrot, vpos);
	*vlrot = ft_vec3add(*vlrot, bone->vrot);
	*vlpos = ft_vec3add(*vlpos, vtrans);
	*vlpos = ft_vec3add(*vlpos, ft_vec3scalar(voffset, 2.f));
	return (mat);
}

void	ft_drawhumanlist(t_ogl *o, t_env *e, t_vec3 vlrot, t_vec3 vlpos, t_list *l)
{
	t_list	*ltmp;
	t_mat4	mbone;

	ltmp = l;
	while (ltmp)
	{
		if (ltmp->content_size == sizeof(t_bone))
		{
			mbone = ft_mat4boneset(&vlrot, &vlpos, &(*((t_bone*)ltmp->content)));
			ft_setpvmmatrices(e->cam, &(o->shaderprogramid), mbone);
			glUseProgram(o->shaderprogramid);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, o->texturebuffer);
			glUniform1i(o->textureid, 0);
			glUniform1f(o->texturealphaid, e->obj.texturealpha);
			ft_drawvertexbuffer(e->obj.fcount);
		}
		else
			ft_drawhumanlist(o, e, vlrot, vlpos, (t_list*)ltmp->content);
		ltmp = ltmp->next;
	}
	return ;
}

/*
** TODO
*/

void	ft_drawhuman(t_ogl *o, t_env *e)
{
	t_vec3	vlrot;
	t_vec3	vlpos;

	vlrot = ft_vec3set(0.f, 0.f, 0.f);
	vlpos = ft_vec3set(0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ft_processinput(o->window);
	ft_updatecamera(&(e->cam));
	ft_drawhumanlist(o, e, vlrot, vlpos, e->lhuman);
	ft_printhumanlist(e->lhuman);
	glfwSwapBuffers(o->window);
	glfwPollEvents();
	return ;
}
