/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:21 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/08 07:44:54 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h" 

void init_cam(t_vec ori, t_vec look, t_vec init_vec, t_cam *cam)
{
	cam->ori = ori;
	t_vec *dir;
	t_vec *norm_dir;
	t_vec *vec_hor;
	t_vec *vec_vert;
	t_vec pos_init_plane;

	vec_hor = (t_vec*)malloc(sizeof(t_vec));
	vec_vert = (t_vec*)malloc(sizeof(t_vec));
	dir = (t_vec*)malloc(sizeof(t_vec));
	norm_dir = (t_vec*)malloc(sizeof(t_vec));
	pos_init_plane = (t_vec*)malloc(sizeof(t_vec));

	/*calcul et normalisation du vecteur directeur de la camera */
	vec_sub(dir, look, ori);
	norm_dir = normalize(dir);

	/*calcul vecteur unitaire horizontal et vertical du plan de la camera*/
	mul_vec(vec_hor, init_vec, norm_dir);
	mul_vec(vec_vert, norm_dir, vec_hor);

	cam->hor = vec_hor;
	cam->vert = vec_vert;

	/* calcul du vecteur de position initial (m_viewPlaneUpLeft dans le .cpp) */
	double plane_dist;
	double plane_height;
	double plane_width;

	plane_dist = 1.0;
	plane_height = 0.35;
	plane_width = 0.5;

	/* correspond a :
	 **  camPos + ((m_vecDir*m_viewplaneDist) + (m_upVec*(m_viewplaneHeight/2.0f)))
	 ** -(m_rightVec*(m_viewplaneWidth/2.0f))
	 */
	mul_vec_val(norm_dir, norm_dir, plane_dist);
	mul_vec_val(vec_vert. vec_vert, (plane_height / 2.0));
	mul_vec_val(vec_hor. vec_hor, (plane_width / 2.0));

	add_vec(pos_init_plane, ori, norm_dir);
	add_vec(pos_init_plane, pos_init_plane, vec_vert);
	sub_vec(pos_init_plane, pos_init_plane, vec_hor);
	
	cam->pos_init_plane = pos_init_plane;
}

t_vec	*calcul_vect_dir(int x, int y, t_cam *cam)
{
	/*
	 ** calcul du vecteur directeur du nouveau vecteur lance au pixel [x,y]
	 ** (fonction CalcDirVec dans le .cpp)
	 */
	double x_indent;
	double y_indent;
	double plane_height;
	double plane_width;
	t_vec *res;
	t_vec *tmp;

	res = (t_vec*)malloc(sizeof(t_vec));
	tmp = (t_vec*)malloc(sizeof(t_vec));
	plane_height = 0.35;
	plane_width = 0.5;

	x_indent = 	plane_width / (double)WIDTH;
	y_indent = 	plane_height / (double)HEIGHT;
	
	/* correspond a : 
	 ** m_viewPlaneUpLeft + m_rightVec*xIndent*x -  m_upVec*yIndent*y - GetPosition();
	 */
	mul_vec_val(res, cam->hor, (x_indent * (double)x));
	mul_vec_val(tmp, cam->vert, (y_indent * (double)y));
	add_vec(res, res, cam->pos_init_plane);
	sub_vec(res, res, tmp);
	sub_vec(res, res, cam->ori);

	return (res);
}
