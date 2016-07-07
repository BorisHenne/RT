/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 05:31:40 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 05:37:33 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector.h>

t_vector	*init_vector(double x, double y, double z)
{
	t_vector	*vec;

	vec = (t_vector *)malloc(sizeof(t_vector));
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
