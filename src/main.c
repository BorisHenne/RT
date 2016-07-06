/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 00:15:41 by sduprey           #+#    #+#             */
/*   Updated: 2016/07/07 01:05:45 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

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
