/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 02:08:38 by bhenne            #+#    #+#             */
/*   Updated: 2016/07/07 23:42:55 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int	key_hook(int keycode, t_env *e)
{
	(void)e;
	// si appuie sur "echp" on quitte le programme
	if (keycode == ESCAPE)
		exit(0);
	//mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int	expose_hook(t_env *e)
{
	// appel fonction ray-tracing ICI
	
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}
