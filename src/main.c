/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/13 23:38:24 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "rtv1.h"

#include <stdio.h>
//int		expose_hook(t_env *e)
//{
//	RAYTRACER
//}

int	main(int ac, char** av)
{
	t_env	e;
	t_scene	*scene;

	scene = NULL;
	if (ac != 2)
	{
		ft_putendl("No file");
		return (0);
	}
	e.mlx = mlx_init();
	if (e.mlx != NULL)
	{
		e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "RTv1");
		if (!(e.img = mlx_new_image(e.mlx, WIDTH, HEIGHT)))
			return (0);
  		if (!(scene = parse(av[1])))
			return (0);
		draw_scene(&e, scene);
		mlx_hook(e.win, 2, 3, key_hook, &e);
//		mlx_expose_hook(e.win, expose_hook, &e);
		mlx_loop(e.mlx);
	}
	free_node_list(&(scene->objects));
	free_node_list(&(scene->lights));
	free(scene);
	(void)av;
	return (0);
}
