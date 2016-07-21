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

double		find_cone_limit(t_ray ray, t_cone cone, double t, t_vec aa, t_vec ab, double ab2, t_hit *hit)
{
	t_vec	inter;
	t_vec	proj;
	double	time;
	double	tmp;

	time = t;
	if (time < 0)
		return (0.0f);
	inter = scalar_product(ray.dir, time);
	inter = vec_add(inter, ray.pos);
	proj = vec_sub(aa, inter);
	tmp = dot_product(ab, proj) / ab2;
	ab = scalar_product(ab, tmp);
	ab = vec_add(ab, aa);
	//
	proj.x = ab.x;
	proj.y = ab.y;
	proj.z = ab.z;
	//
	proj = vec_sub(cone.pos, proj);
	tmp = get_length(proj);
	if (tmp > cone.len)
		return (0.0f);
	(*hit).point_norm = inter;
	(*hit).point_norm = vec_sub(cone.pos, inter);
	proj = scalar_product(normalize(proj), get_length(hit->point_norm) / cos(cone.r));
	(*hit).point_norm = normalize(vec_sub(proj, hit->point_norm));

	//(*hit).point_norm = scalar_product(hit->point_norm, -1);
	return (time);
}

#include <stdio.h>
t_hit		is_cone_hit(t_ray ray, t_cone cone)
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
	double	time2;
	//
	double t1;
	double t2;


	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.t = 0;

	//
	aa = vec_add(cone.pos, cone.dir);
	ab = vec_sub(cone.pos, aa);
	//ab = cone.dir;
	v = vec_sub(aa, ray.pos);
	oxb = cross_product(v, ab);
	v = cross_product(ray.dir, ab);
	ab2 = dot_product(ab, ab);
	delta = vec_sub(cone.pos, ray.pos);
	//
	x = dot_product(ray.dir, cone.dir);
	y = dot_product(delta, cone.dir);
	//
	a = c2(cone.r) * dot_product(v, v) - s2(cone.r) * x * x;
	b = 2 * c2(cone.r) * dot_product(v, oxb) - 2 * s2(cone.r) * x * y;
	c = c2(cone.r) * dot_product(oxb, oxb) - s2(cone.r) * y * y;
	
	det = find_cone_det(a, b, c);
	if (det < 0)
		hit.bool = 0;
	else
	{
		t1 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
		t1 /= (double)PRECISION;
		t2 = (int)((-b + sqrt(det)) / (2 * a) * PRECISION);
		t2 /= (double)PRECISION;
		time1 = find_cone_limit(ray, cone, t1, aa, ab, ab2, &hit);
		if (time1 > 0.0f)
		{
			hit.bool = 1;
			hit.t = time1;
			hit.color.r = cone.color.r;
			hit.color.g = cone.color.g;
			hit.color.b = cone.color.b;
		}
		else
		{
			time2 = find_cone_limit(ray, cone, t2, aa, ab, ab2, &hit);
			if (time2 > 0.0f)
			{
				hit.point_norm = scalar_product(hit.point_norm, -1);
				hit.bool = 1;
				hit.t = time2;
				hit.color.r = cone.color.r;
				hit.color.g = cone.color.g;
				hit.color.b = cone.color.b;
			}
			else
			{
				time1 = find_cone_limit(ray, cone, t1, aa, ab, ab2, &hit);
				if (time1 > 0.0f)
				{
					hit.bool = 1;
					hit.t = time1;
					hit.color.r = cone.color.r;
					hit.color.g = cone.color.g;
					hit.color.b = cone.color.b;
				}
			}
		}
	}
	//hit.point_norm = vec_sub(cone.pos, vec_add(ray.pos, scalar_product(ray.dir, hit.t)));
	return (hit);
}
