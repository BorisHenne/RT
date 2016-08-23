#include <rtv1.h>
#include <cone.h>

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

double		find_cone_det(double a, double b, double c)
{
		return (b * b - 4 * a * c);
}

double		find_cone_limit(t_ray *ray, t_cone *cone, double t, t_vec aa, t_vec ab, double ab2, t_hit *hit)
{
	t_vec	inter;
	t_vec	proj;
	double	time;
	double	tmp;

	time = t;
	if (time < 0)
		return (0.0f);
	inter = scalar_product(ray->dir, time);
	inter = vec_add(inter, ray->pos);
	proj = vec_sub(aa, inter);
	tmp = dot_product(ab, proj) / ab2;
	ab = scalar_product(ab, tmp);
	ab = vec_add(ab, aa);
	//
	proj.x = ab.x;
	proj.y = ab.y;
	proj.z = ab.z;
	//
	proj = vec_sub(cone->pos, proj);
	tmp = get_length(proj);
	if (tmp > cone->len)
		return (0.0f);
	hit->dist_from_center = tmp;
	(*hit).point_norm = inter;
	(*hit).point_norm = vec_sub(cone->pos, inter);
	proj = scalar_product(normalize(proj), get_length(hit->point_norm) / cos(cone->r));
	(*hit).point_norm = normalize(vec_sub(proj, hit->point_norm));

	//(*hit).point_norm = scalar_product(hit->point_norm, -1);
	return (time);
}

#include <stdio.h>
t_hit		is_cone_hit(t_ray *ray, t_cone *cone)
{
	t_hit	hit;
	t_vec	aa;
	t_vec	ab;
	t_vec	oxb;
	t_vec	v;
	t_vec	delta;
	double	x;
	double	y;
	double	a;
	double	b;
	double	c;
	double	ab2;
	//
	double	det;
	//
	double	time1;
	//
	double t;
	double	t_max;
	//
	double t1;
	double t2;


	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.t = 0;
	hit.t_max = 0;

	//
	aa = vec_add(cone->pos, cone->dir);
	ab = vec_sub(cone->pos, aa);
	v = vec_sub(aa, ray->pos);
	oxb = cross_product(v, ab);
	v = cross_product(ray->dir, ab);
	ab2 = dot_product(ab, ab);
	delta = vec_sub(cone->pos, ray->pos);
	//
	x = dot_product(ray->dir, cone->dir);
	y = dot_product(delta, cone->dir);
	//
	a = c2(cone->r) * dot_product(v, v) - s2(cone->r) * x * x;
	b = 2 * c2(cone->r) * dot_product(v, oxb) - 2 * s2(cone->r) * x * y;
	c = c2(cone->r) * dot_product(oxb, oxb) - s2(cone->r) * y * y;
	
	det = find_cone_det(a, b, c);
	if (det >= 0)
	{
		t1 = (-b - sqrt(det)) / (2 * a);
		t2 = (-b + sqrt(det)) / (2 * a);


		t = t1 < t2 ? t1 : t2;
		t_max = t1 < t2 ? t2 : t1;

		double	time2;
		t_hit	hit_max;

		time2 = find_cone_limit(ray, cone, t_max, aa, ab, ab2, &hit);
		hit.point_norm_max = hit.point_norm;
		time1 = find_cone_limit(ray, cone, t, aa, ab, ab2, &hit);
		hit_max.point_norm_max = hit.point_norm;

		if (time1 > (double)(1.0 / PRECISION))
		{
			hit.bool = 1;
			hit.t = time1;
			hit.t_max = t_max;
			hit.color = cone->color;
			hit.opacity = cone->opacity;
			hit.ref_index = cone->ref_index;
		}
		else
		{
			hit = hit_max;
			if (time2 > (double)(1.0 / PRECISION))
			{
	//			hit.point_norm = scalar_product(hit.point_norm, -1);
				hit.bool = 1;
				hit.t = time2;
				hit.t_max = t_max;
				hit.color = cone->color;
				t_vec tmp = hit.point_norm;
				hit.point_norm_max = tmp;
				hit.point_norm = hit.point_norm_max;
				hit.opacity = cone->opacity;
				hit.ref_index = cone->ref_index;
			}
		}
		hit.type = CONE;
		hit.length = cone->len;
		hit.pos = cone->pos;
		hit.radius = cone->r;
		hit.specular = cone->specular;
		hit.reflection = cone->reflection;
		hit.texture = cone->texture;
		hit.is_negativ = cone->is_negativ;
	}
	return (hit);
}
