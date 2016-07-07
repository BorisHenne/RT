/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:40 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 06:44:28 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_vector		*init_vector(double x, double y, double z)
{
	t_vector	*vec;

	vec = (t_vector *)malloc(sizeof(t_vector));
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double			get_length(t_vector *vec)
{
	double		x;
	double		y;
	double		z;

	x = pow(vec->x, 2);
	y = pow(vec->y, 2);
	z = pow(vec->z, 2);
	return (sqrt(x + y + z));
}

// La fonction pourrait egalement retourner un nouveau veteur noralise, a voir ...
void			normalize(t_vector *vec)
{
	double		len;

	len = get_length(vec);
	if (len == 0.0f)
	{
		len = 1; //!\ HELP !!!
	}
	vec->x /= len; // a verifier si existe en C le /=, j'ai un doute ...
	vec->y /= len;
	vec->z /= len;
	return ;
}
