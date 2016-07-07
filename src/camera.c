/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:21 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 06:43:32 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera.h>

t_camera	*init_camera(t_vector *pos, t_vector *dir)
{
	t_camera	*cam;

	cam = (t_camera *)malloc(sizeof(t_camera));
	cam->camPos = pos;
	cam->upVec = dir;
	cam->viewplaneWidth = 1.0f;
	cam->viewplaneHeight = 0.35f;
	cam->viewplaneDist = 1.0f;
	return (cam);
}

t_vector	*calcDirVec(t_camera *cam, double x, double y, int xRes, int yRes)
{
	double	xIndent;
	double	yIndent;

	xIndent = cam->viewplaneWidth / (double)xRes;
	yIndent = cam->viewplaneHeight / (double)yRes;
	return ((cam->viewPlaneUpLeft + cam->rightVec * xIndent * x - cam-upVec * yIndent * y) - cam->camPos);
}
