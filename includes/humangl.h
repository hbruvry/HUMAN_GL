/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   humangl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbruvry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:13:30 by hbruvry           #+#    #+#             */
/*   Updated: 2020/02/28 18:22:00 by hbruvry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCOP_H
# define __SCOP_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdint.h>
# include "lib/libft/libft.h"
# include "lib/libmath/libmath.h"

# define WIDTH	480
# define HEIGHT	360
# define FRAGPATH "./shaders/fragmentshadercolor.fs"
# define VERTPATH "./shaders/vertexshadermodel.vs"

# define FOV	90
# define NEAR	0.1
# define FAR	100
# define SPEED	5
# define SENSI	0.025

typedef int bool;

#define false 0
#define true 1

typedef struct	s_ogl
{
	GLFWwindow	*window;
	GLuint		vertexarrayid;
	GLuint		texturebuffer;
	GLuint		textureid;
	GLuint		texturealphaid;
	GLuint		shaderprogramid;
	GLuint		vertexbuffer;
	GLuint		normalbuffer;
	GLuint		uvbuffer;
	GLuint		elementbuffer;
}				t_ogl;

typedef struct	s_bone
{
	char		*name;
	t_vec3		vpos;
	t_vec3		vabspos;
	t_vec3		vrot;
	t_vec3		vabsrot;
	t_vec3		vsize;
	uint8_t		flags;
	uint8_t		childcount;
}				t_bone;

typedef struct	s_cam
{
	t_vec3		vpos;
	t_vec3		vfront;
	t_vec3		vup;
	t_vec3		vright;
	t_vec3		vdir;
	t_vec3		vtarget;
	bool		target;
	bool		turnaround;
	float		fov;
	float		yaw;
	float		pitch;
	bool		firstmouse;
	float		lastx;
	float		lasty;
}				t_cam;

typedef struct	s_time
{
	float		currentframe;
	float		lastframe;
	float		delta;
}				t_time;

typedef struct	s_obj
{
	GLfloat		*vertexbufferdata;
	GLfloat		*normalbufferdata;
	GLfloat		*uvbufferdata;
	GLuint		*indicebufferdata;
	bool		istextured;
	float		texturealpha;	
	int			vcount;
	int			fcount;
	int			elementlength;
}				t_obj;

typedef struct	s_env
{
	t_cam		cam;
	t_cam		camreset;
	t_obj		obj;
	t_list		*lhuman;
	t_time		time;
}				t_env;

t_ogl			*ft_getopengl(void);
t_env			*ft_getenvironment(void);
char			*ft_filecpy(char *path);
char			**ft_filecpytab(char *path);
int				ft_setshaderprogram(GLuint *shaderprogramid);
int				ft_setbmptexture(GLuint *texturebuffer);
void			ft_lfill(t_list **alst, void const *c, size_t cs);
void			ft_printbone(t_bone b, int tablength);
void			ft_printhumanlist(t_list *l);
void			ft_sethumanlist(t_list **lhuman);
void			ft_translatevertexbufferdata(GLfloat *vertexbufferdata, int vcount, t_vec3 vtrans);
void			ft_setvertexbufferdata(GLfloat *vertexbufferdata, char *objdata);
void			ft_setuvbufferdata(GLfloat *uvbufferdata, t_vec3 vertex);
void			ft_setindicebufferdata(GLuint *indicebufferdata, char *objdata);
void			ft_printobjectdata(t_obj obj);
int				ft_parseobject(char *path, t_obj *obj);
void			ft_mousecallback(GLFWwindow *window, double posx, double posy);
void			ft_scrollcallback(GLFWwindow *window, double offsetx, double offsety);
void			ft_processinput(GLFWwindow *window);
void			ft_updatecamera(t_cam *cam);
void			ft_setpvmmatrices(t_cam cam, GLuint *shaderprogramid, t_mat4 bonemat);
void			ft_drawhuman(t_ogl *o, t_env *e);

#endif