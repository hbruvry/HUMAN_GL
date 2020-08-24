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

void	ft_mat4rotupdate(t_mat4 *mat, t_bone bone)
{
	t_mat4	mrot;

	ft_mat4set(&mrot, IDENTITY);
	mrot = ft_mat4rotate(mrot, bone.vrot);
	*mat = ft_mat4mul(mrot, *mat);
	return ;
}

/*
** TODO
*/

void	ft_mat4transupdate(t_mat4 *mat, t_mat4 mlrot, t_bone bone)
{
	t_vec3	vtrans;
	t_mat4	mrot;
	t_mat4	mtrans;

	vtrans = ft_vec3set(0.f, bone.vsize.v[1], 0.f);
	ft_mat4set(&mrot, IDENTITY);
	mrot = ft_mat4rotate(mrot, ft_vec3appmat4(bone.vrot, mlrot));
	vtrans = ft_vec3appmat4(vtrans, mrot);
	ft_mat4set(&mtrans, IDENTITY);
	mtrans = ft_mat4translate(mtrans, vtrans);
	*mat = ft_mat4mul(mtrans, *mat);
	return ;
}

/*
** TODO
*/

void	ft_mat4boneset(t_mat4 *mat, t_mat4 mlrot, t_mat4 mltrans, t_bone *bone)
{
	t_vec3	vtrans;
	t_mat4	mrot;
	t_mat4	mtrans;

	ft_mat4set(mat, IDENTITY);
	*mat = ft_mat4transform(*mat,
		ft_vec3set(bone->vsize.v[0], bone->vsize.v[1], bone->vsize.v[2]),
		ft_vec3appmat4(bone->vrot, mlrot),
		ft_vec3appmat4(bone->vpos, mltrans));
	bone->vabspos = ft_vec3appmat4(bone->vpos, mltrans);
	vtrans = ft_vec3set(0.f, bone->vsize.v[1] * 0.5f, 0.f);
	bone->vabsrot = ft_vec3appmat4(bone->vrot, mlrot);
	ft_mat4set(&mrot, IDENTITY);
	mrot = ft_mat4rotate(mrot, ft_vec3appmat4(bone->vrot, mlrot));
	vtrans = ft_vec3appmat4(vtrans, mrot);
	ft_mat4set(&mtrans, IDENTITY);
	mtrans = ft_mat4translate(mtrans, vtrans);
	*mat = ft_mat4mul(mtrans, *mat);
	return ;
}

void	ft_drawhumanlist(t_ogl *o, t_env *e,
						t_mat4 mlrot, t_mat4 mltrans, t_list *l)
{
	t_list	*ltmp;
	t_mat4	mbone;
	t_mat4	mlprevrot;
	t_mat4	mlprevtrans;

	ltmp = l;
	ft_mat4cpy(&mlprevrot, mlrot);
	ft_mat4cpy(&mlprevtrans, mltrans);
	while (ltmp)
	{
		if (ltmp->content_size == sizeof(t_bone))
		{
			ft_mat4boneset(&mbone, mlrot, mltrans, &(*((t_bone*)ltmp->content)));
			ft_mat4rotupdate(&mlrot, *((t_bone*)ltmp->content));
			//ft_mat4transupdate(&mltrans, mlrot, *((t_bone*)ltmp->content));
			ft_setpvmmatrices(e->cam, &(o->shaderprogramid), mbone);
			glUseProgram(o->shaderprogramid);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, o->texturebuffer);
			glUniform1i(o->textureid, 0);
			glUniform1f(o->texturealphaid, e->obj.texturealpha);
			ft_drawvertexbuffer(e->obj.fcount);
		}
		else
			ft_drawhumanlist(o, e, mlrot, mltrans, (t_list*)ltmp->content);
		ltmp = ltmp->next;
	}
	ft_mat4cpy(&mlrot, mlprevrot);
	ft_mat4cpy(&mltrans, mlprevtrans);
	return ;
}

/*
** TODO
*/

void	ft_drawhuman(t_ogl *o, t_env *e)
{
	t_mat4	mlrot;
	t_mat4	mltrans;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ft_processinput(o->window);
	ft_updatecamera(&(e->cam));
	ft_mat4set(&mlrot, IDENTITY);
	ft_mat4set(&mltrans, IDENTITY);
	ft_drawhumanlist(o, e, mlrot, mltrans, e->lhuman);
	ft_printhumanlist(e->lhuman);
	glfwSwapBuffers(o->window);
	glfwPollEvents();
	return ;
}
