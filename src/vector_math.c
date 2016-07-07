// HEADER 42 /!\

#include <vector.h>

t_vector	*vec_add(t_vector *a, t_vector *b)
{
	double	x;
	double	y;
	double	z;

	x = a->x + b->x;
	y = a->y + b->y;
	z = a->z + b->z;
	return (init_vector(x, y, z));
}

t_vector	*vec_sub(t_vector *a, t_vector b)
{
	double	x;
	double	y;
	double	z;

	x = b->x - a->x;
	y = b->y - a->y;
	z = b->z - a->z;
	return (init_vector(x, y, z));
}

t_vector	cross_product(t_vector *a, t_vector *b)
{
	double	x;
	double	y;
	double	z;

	x = (a->y * b->z) - (a->z * b->y);
	y = (a->z * b->x) - (a->x * b->z);
	z = (a->x * b->y) - (a->y * b->x);
	return (init_vector(x, y, z));
}

t_vector	*scalar_product(t_vector *vec, double n)
{
	double	x;
	double	y;
	double	z;

	x = vec->x * n;
	y = vec->y * n;
	z = vec->z * n;
	return (init_vector(x, y, z));
}

double		dot_product(t_vector *a, t_vector *b)
{
	double	dot;

	dot = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	// Verifier le cas du "dot <= 1" et remplacer par "dot < 1" si necessaire
	if (dot > 0.0f && dot <= 1.0f)
		return acos(dot);
	return acos(0.0f);
}
