/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 02:04:04 by bhenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "rtv1.h"

int	main(int ac, char** av)
{
	void	*mlx;
	void	*win;


	mlx = mlx_init();
	if (mlx != NULL)
	{
		win = mlx_new_window(mlx, 640, 480, "RTv1");
		mlx_loop(mlx);
	}
	(void)ac;
	(void)av;
	return (0);
}
