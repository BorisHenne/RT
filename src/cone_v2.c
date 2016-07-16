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

double		find_closest_hit(double a, double b, double det)
{
	double	t1;
	double	t2;

	t1 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
	t1 /= (double)PRECISION;

	t2 = (int)((-b + sqrt(det)) / (2 * a) * PRECISION);
	t2 /= (double)PRECISION;
	//return (t1 > t2 ? t2 : t1);
	return (t1);
}

double		find_cone_limit(t_ray ray, t_cone cone, double t, t_vec aa, t_vec ab, double ab2)
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
	else
		return (time);
}

#include <stdio.h>
t_coord		is_cone_hit(t_ray ray, t_cone cone)
{
	t_coord	hit;
	//
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
	double	r;
	//
	double	det;
	//
	double	time;
	//
	double t1, t2;


	hit.bool = 0;
	hit.color.r = 0;
	hit.color.g = 0;
	hit.color.b = 0;
	hit.t = 0;

	r = 3.0f;
	//
	aa = vec_add(cone.pos, cone.dir);
	ab = cone.dir;//vec_sub(cone.pos, aa);
	v = vec_sub(aa, ray.pos);
	oxb = cross_product(v, ab);
	v = cross_product(ray.dir, ab);
	ab2 = dot_product(ab, ab);
	delta = vec_sub(cone.pos, ray.pos);
	//
	x = dot_product(ray.dir, cone.dir);
	y = dot_product(delta, cone.dir);
	//
	a = c2(r) * dot_product(v, v) - s2(r) * x * x;
	b = 2 * c2(r) * dot_product(v, oxb) - 2 * s2(r) * x * y;
	c = c2(r) * dot_product(oxb, oxb) - s2(r) * y * y;
	det = find_cone_det(a, b, c);
	if (det < 0)
	{
		hit.bool = 0;
	}
	else
	{
		t1 = (int)((-b - sqrt(det)) / (2 * a) * PRECISION);
		t1 /= (double)PRECISION;
		t2 = (int)((-b + sqrt(det)) / (2 * a) * PRECISION);
		t2 /= (double)PRECISION;
		time = find_cone_limit(ray, cone, t1, aa, ab, ab2);
		/*
		time = find_closest_hit(a, b, det);
		time = (-b - sqrt(det))/ (2 * a);
		*/
		if (time > 0.0f)
		{
			hit.bool = 1;
			hit.t = time;
			hit.color.r = cone.color.r;
			hit.color.g = cone.color.g;
			hit.color.b = cone.color.b;
		}
		else
		{
			time = find_cone_limit(ray, cone, t2, aa, ab, ab2);
			if (time > 0.0f)
			{
				hit.bool = 1;
				hit.t = time;
				hit.color.r = cone.color.r + 25;
				hit.color.g = cone.color.g + 25;
				hit.color.b = cone.color.b + 25;
			}
		}
	}
//	printf("hit.t = %f\n", hit.t);
	return (hit);
}
