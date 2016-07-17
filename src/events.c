/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 02:08:38 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/08 07:12:46 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int	key_hook(int keycode, t_env *e)
{
	(void)e;
	if (keycode == 53) //esc
		exit(0);
	if (keycode == 123) //leftarrow
	if (keycode == 124) //rightarrow
	if (keycode == 125) // downarrow
	if (keycode == 126) // uparrow
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int	expose_hook(t_env *e)
{
	// appel fonction ray-tracing ICI
	
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
