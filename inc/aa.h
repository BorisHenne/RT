/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 00:11:00 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/13 02:02:00 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _AA_H
#define _AA_H

# include <objects.h>

void	*aa(void *mlx, void *img, int mode);
t_color	get_pixel_color(void *img, int x, int y);
void	*sepia_filter(void *, void *);
int		put_pixel_on_image(void *img, int x, int y, t_color color);

# endif
