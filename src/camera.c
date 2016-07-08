/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:21 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/09 00:04:51 by nbelouni         ###   ########.fr       */
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
	dir = sub_vec(look, ori);
	norm_dir = normalize(dir);

	/*calcul vecteur unitaire horizontal et vertical du plan de la camera*/
	vec_hor = mul_vec(init_vec, norm_dir);
	vec_vert = mul_vec(norm_dir, vec_hor);

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
	norm_dir = mul_vec_val(norm_dir, plane_dist);
	vec_vert = mul_vec_val(vec_vert, (plane_height / 2.0));
	vec_hor = mul_vec_val(vec_hor, (plane_width / 2.0));

	pos_init_plane = add_vec(add_vec(ori, norm_dir), vec_vert);
	pos_init_plane = sub_vec(pos_init_plane, vec_hor);
	
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
	res = mul_vec_val(cam->hor, (x_indent * (double)x));
	tmp = mul_vec_val(cam->vert, (y_indent * (double)y));
	res = add_vec(res, cam->pos_init_plane);
	res = sub_vec(res, tmp);
	res = sub_vec(res, cam->ori);

	return (res);
}
