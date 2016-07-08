/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:21 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/08 02:56:08 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h" 

void		calc_pos_plan(t_env *e)
{
	t_vec		up_vec;
	t_vec		right_vec;
	t_vec		res;
	t_vec		dir;

	mul_vec_val(&right_vec, &e->cam.right, 0.5 / 2.0);
	mul_vec_val(&up_vec, &e->cam.down, 0.35 / 2.0);
	mul_vec_val(&dir, &e->cam.dir, 1.0);
	sub_vec(&res, &up_vec, &right_vec);
	add_vec(&res, &res, &dir);
	add_vec(&e->pos_plan, &res, &e->cam.ori);
}

t_cam	*init_camera(t_vec *pos, t_vec *dir)
{
	t_cam	*cam;

	cam = (t_cam*)malloc(sizeof(t_cam));
	cam->camPos = pos;
	cam->upVec = dir;
	cam->viewplaneWidth = 0.35f;
	cam->viewplaneHeight = 0.5f;
	cam->viewplaneDist = 1.0f;
	cam->viewPlaneUpLeft = cam->camPos + ((cam->vecDir * cam->viewplaneDist) +
			(cam->upVec *(cam->viewplaneHeight/2.0f))) - (cam->rightVec *(cam->viewplaneWidth/2.0f));
	return (cam);
}

t_vec	*calcPos(t_cam *cam, int x, int y)
{
	double	xIndent;
	double	yIndent;

	xIndent = cam->viewplaneWidth / cam->xRes;
	yIndent = cam->viewplaneHeight / cam->yRes;

	return(cam->viewPlaneUpLeft + cam->rightVec*xIndent*x - cam->upVec*yIndent*y);
}

