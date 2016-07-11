#ifndef _SPHERE_H
# define _SPHERE_H

#include <color.h>
#include <camera.h>

typedef struct	s_sphere
{
	double	radius;
	t_vec	center;
	t_color	color;
}		t_sphere;

typedef struct	s_coord
{
	double	t;
	t_color	*color;
	int	bool;
}		t_coord;

double		find_sphere_det(t_cam cam, t_sphere s, double *a, double *b);
double		find_sphere_closest_hit(double a, double b, double det);
t_coord		is_sphere_hit(t_cam *cam, t_sphere *sphere);

#endif
