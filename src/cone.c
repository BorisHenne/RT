#include <rtv1.h>
#include <stdio.h>

static void		complete_hit(t_hit *hit, t_cone *cone)
{
	hit->type = CONE;
	hit->length = cone->len;
	hit->pos = cone->pos;
	hit->radius = cone->r;
	hit->specular = cone->specular;
	hit->reflection = cone->reflection;
	hit->texture = cone->texture;
	hit->is_negativ = cone->is_negativ;
	hit->color.r = cone->color.r;
	hit->color.g = cone->color.g;
	hit->color.b = cone->color.b;
	hit->opacity = cone->opacity;
	hit->ref_index = cone->ref_index;
}

double		c2(double x)
{
	double	a;

	a = cos(x);
	return (a * a);
}

double		s2(double x)
{
	double	a;

	a = sin(x);
	return (a * a);
}

static t_hit	create_disk(t_ray *ray, t_cone *cone, double side)
{
	t_hit	hit;
	t_plane	*plane;
	t_vec	new_dir;
	t_vec	inter;

	plane = (t_plane *)malloc(sizeof(t_plane));
	new_dir = scalar_product(cone->dir, side);
	plane->pos = vec_add(cone->pos, scalar_product(new_dir, cone->len));
	plane->normal = scalar_product(new_dir, -1);
	hit.t = find_plane_hit(ray, plane);
	hit.bool = 0;

	if (hit.t > (double)(1.0 / PRECISION))
	{
		inter = vec_add(ray->pos, scalar_product(ray->dir, hit.t));
		if (get_length(vec_sub(plane->pos, inter)) <= cone->r)
		{
			hit.bool = 1;
			hit.point_norm = new_dir;
		}
	}
	free(plane);
	return (hit);
}

double		find_cone_limit(t_ray *ray, t_cone *cone, double t, t_intern intern, t_hit *hit)
{
	t_vec	inter;
	t_vec	proj;
	double	tmp;
	double	angle;

	inter = vec_add(ray->pos, scalar_product(ray->dir, t));
	proj = vec_sub(intern.aa, inter);
	tmp = dot_product(intern.ab, proj) / intern.ab2;
	intern.ab = scalar_product(intern.ab, tmp);
	intern.ab = vec_add(intern.ab, intern.aa);
	proj = intern.ab;
	proj = vec_sub(cone->pos, proj);
	tmp = get_length(proj);
	if (tmp > cone->len)
		return (0.0);
	hit->dist_from_center = tmp;
	(*hit).point_norm = inter;
	(*hit).point_norm = vec_sub(cone->pos, inter);
	angle = atan(cone->r / cone->len);
	proj = scalar_product(normalize(proj), get_length(hit->point_norm) / cos(angle));
	(*hit).point_norm = normalize(vec_sub(proj, hit->point_norm));
	return (t);
}

double		find_cone_det(t_intern intern, double angle, double *t1, double *t2)
{
	double	det;
	double	a;
	double	b;
	double	c;

	a = c2(angle) * dot_product(intern.v, intern.v);
	a -= s2(angle) * intern.x * intern.x;
	b = 2.0 * c2(angle) * dot_product(intern.v, intern.oxb);
	b -= 2.0 * s2(angle) * intern.x * intern.y;
	c = c2(angle) * dot_product(intern.oxb, intern.oxb);
	c -= s2(angle) * intern.y * intern.y;
	det = b * b - 4 * a * c;
	*t1 = (-b - sqrt(det)) / (2 * a);
	*t2 = (-b + sqrt(det)) / (2 * a);
	return (det);
}

t_hit		is_cone_hit(t_ray *ray, t_cone *cone)
{
	t_hit		hit;
	t_hit		hit_max;
	t_hit		hit_size;
	t_intern	intern;
	double		t;
	double		t_max;
	double		t1;
	double		t2;
	double		angle;

	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.t = 0;
	hit.t_max = 0;
	hit_max = hit;

	cone->dir = normalize(cone->dir);
	angle = atan(cone->r / cone->len);
	intern.aa = vec_add(cone->pos, cone->dir);
	intern.ab = vec_sub(cone->pos, intern.aa);
	intern.v = vec_sub(intern.aa, ray->pos);
	intern.oxb = cross_product(intern.v, intern.ab);
	intern.v = cross_product(ray->dir, intern.ab);
	intern.ab2 = dot_product(intern.ab, intern.ab);
	intern.delta = vec_sub(cone->pos, ray->pos);
	intern.x = dot_product(ray->dir, cone->dir);
	intern.y = dot_product(intern.delta, cone->dir);

	if (find_cone_det(intern, angle, &t1, &t2) >= 0)
	{
		if (cone->is_closed == 1)
		{
			hit_size = create_disk(ray, cone, -1);
			hit = create_disk(ray, cone, 1);
			if (hit.bool != 0)
			{
				if (hit_size.bool == 0)
				{
					hit_size.bool = 1;
					hit_size.t = hit.t;
					hit_size.point_norm = hit.point_norm;
				}
				else
				{
					if (hit_size.t < hit.t)
					{
						hit.t_max = hit.t;
						hit.t = hit_size.t;
						hit.point_norm_max = hit.point_norm;
						hit.point_norm = hit_size.point_norm;
					}
					else
					{
						hit.t_max = hit_size.t;
						hit.point_norm_max = hit_size.point_norm;
					}
					complete_hit(&hit, cone);
					return (hit);
				}
			}
		}

		t = t1 < t2 ? t1 : t2;
		t_max = t1 < t2 ? t2 : t1;

		t_max = find_cone_limit(ray, cone, t_max, intern, &hit_max);
		hit.point_norm_max = hit_max.point_norm;
		t = find_cone_limit(ray, cone, t, intern, &hit);
		hit_max.point_norm_max = hit.point_norm;
		if (t > (double)(1.0 / PRECISION))
		{
			hit.bool = 1;
			if (hit_size.bool == 1 && cone->is_closed == 1)
			{
				hit.t = t < hit_size.t ? t : hit_size.t;
				hit.t_max = t < hit_size.t ? hit_size.t : t;
				hit.point_norm_max = t < hit_size.t ? hit_size.point_norm : hit.point_norm;
				hit.point_norm = t < hit_size.t ? hit.point_norm : hit_size.point_norm;
			}
			else
			{
				hit.t = t;
				hit.t_max = t_max;
			}
			complete_hit(&hit, cone);
			return (hit);
		}
		else
		{
			hit = hit_max;
			if (t_max > (double)(1.0 / PRECISION))
			{
				hit.bool = 1;
				if (hit_size.bool == 1 && cone->is_closed == 1)
				{
					hit.t = t_max < hit_size.t ? t_max : hit_size.t;
					hit.t_max = t_max < hit_size.t ? hit_size.t : t_max;
					hit.point_norm = t_max < hit_size.t ? hit.point_norm : hit_size.point_norm;
					hit.point_norm_max = t_max < hit_size.t ? hit_size.point_norm : hit.point_norm;
				}
				else
				{
					hit.t = t_max;
					hit.t_max = t_max;
				}
				complete_hit(&hit, cone);
				return (hit);
			}
		}
		if ((hit_size.t_max < (double)(1.0 / PRECISION) || hit.t_max < (double)(1.0 / PRECISION))
				&& cone->is_closed == 1)
		{
			hit = hit_size;
			hit.t_max = hit.t;
			complete_hit(&hit, cone);
		}
	}
	return (hit);
}
