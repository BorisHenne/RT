/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 03:49:13 by nbelouni          #+#    #+#             */
/*   Updated: 2016/07/25 16:10:15 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
/*
   float Get2DPerlinNoiseValue(float x, float y, float res)
   {
   float tempX,tempY;
   int x0,y0,ii,jj,gi0,gi1,gi2,gi3;
   float unit = 1.0f/sqrt(2);
   float tmp,s,t,u,v,Cx,Cy,Li1,Li2;
   float gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};

   unsigned int perm[] =
   {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
   142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
   203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
   74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
   105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
   187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
   64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
   47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
   153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
   112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
   235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
   127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
   156,180};

//Adapter pour la résolution
x /= res;
y /= res;

//On récupère les positions de la grille associée à (x,y)
x0 = (int)(x);
y0 = (int)(y);

//Masquage
ii = x0 & 255;
jj = y0 & 255;

//Pour récupérer les vecteurs
gi0 = perm[ii + perm[jj]] % 8;
gi1 = perm[ii + 1 + perm[jj]] % 8;
gi2 = perm[ii + perm[jj + 1]] % 8;
gi3 = perm[ii + 1 + perm[jj + 1]] % 8;

//on récupère les vecteurs et on pondère
tempX = x-x0;
tempY = y-y0;
s = gradient2[gi0][0]*tempX + gradient2[gi0][1]*tempY;

tempX = x-(x0+1);
tempY = y-y0;
t = gradient2[gi1][0]*tempX + gradient2[gi1][1]*tempY;

tempX = x-x0;
tempY = y-(y0+1);
u = gradient2[gi2][0]*tempX + gradient2[gi2][1]*tempY;

tempX = x-(x0+1);
tempY = y-(y0+1);
v = gradient2[gi3][0]*tempX + gradient2[gi3][1]*tempY;


//Lissage
tmp = x-x0;
Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

Li1 = s + Cx*(t-s);
Li2 = u + Cx*(v-u);

tmp = y - y0;
Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;

return Li1 + Cy*(Li2-Li1);
}*/

double		deg_to_rad(double angle)
{
	double res;

	res = angle * M_PI / 180;
	return res;
}

int         put_pixel_on_image(void *img, int x, int y, t_color color)
{
	char    *data;
	int     i;
	int     bpp;
	int     sl;
	int     endian;

	data = mlx_get_data_addr(img, &bpp, &sl, &endian);
	bpp /= 8;
	i = x * bpp + y * sl;
	if (x >= WIDTH || y >= HEIGHT)
		return (0);
	data[i] = color.b;
	data[i + 1] = color.g;
	data[i + 2] = color.r;
	return (0);
}

double	define_color(double color)
{
	if (color < 62)
		color = 0;
	if (color <= 124 && color > 62)
		color = 62;
	if (color <= 186 && color > 124)
		color = 124;
	else if (color > 186)
		color = 255;
	return (color);
}

//
//	Pour les contours noirs, checker dist entre 2 pt du meme object 
//	-> si 0 ou < 0.2 == noir
//
//	on se branle du plan pour l'instant
//

t_color	cartoon(t_color color)
{
	color.r = define_color(color.r);
	color.g = define_color(color.g);
	color.b = define_color(color.b);
	return (color);
}

int		is_black_edge(t_hit *hit)
{
	double	dist_min_max;
	double	edge_scale;

	if (hit->radius > 0.0)
		edge_scale = hit->radius / 2;
	else
		edge_scale = 0;

	dist_min_max = hit->t_max - hit->t;
	if (dist_min_max < edge_scale && dist_min_max > 0.0)
		return (1);
	return (0);
}

#include <stdio.h>
int		draw_scene(t_env *env, t_scene scene)
{
	int		x;
	int		y;
	int		r;
	t_ray	start;
	t_color final_color;
	double	reflet;
	t_hit	drawn_pixel;
	t_color white;

	///////////////////////
	double	**tab_noise;

	y = 0;
	tab_noise = (double **)malloc(sizeof(double *) * HEIGHT);
	while (y < HEIGHT)
	{
		x = 0;
		tab_noise[y] = (double *)malloc(sizeof(double) * WIDTH);
		while (x < WIDTH)
		{
			tab_noise[y][x] = (rand() % 32768) / 32768.0;
			x++;
		}
		y++;
	}
	////////////////////////////

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			final_color = init_color(0, 0, 0);
			r = 0;
			start.pos = scene.cam.ray.pos;
			start.dir = normalize(calc_vec_dir(x, y, scene.cam, scene.cam.look_at));
			while (r < 1)
			{
				reflet = pow(drawn_pixel.reflection, r);
				drawn_pixel = find_closest_object(scene.objects, start);
				if (drawn_pixel.bool == 1)
				{
					if (scene.is_real == CARTOON && is_black_edge(&drawn_pixel))
						drawn_pixel.color = init_color(0, 0, 0);
					else
					{
						drawn_pixel.color = apply_light(scene, drawn_pixel, start);
						drawn_pixel.color = mult_color(drawn_pixel.color, reflet);
						drawn_pixel.color = add_color(drawn_pixel.color, apply_refraction(start, scene, drawn_pixel, reflet));
					}
				}
				else
					break;
				start.pos = vec_add(start.pos, scalar_product(start.dir, drawn_pixel.t)); 
				reflet = dot_product(start.dir, drawn_pixel.point_norm) * 2.0;
				start.dir = vec_sub(scalar_product(drawn_pixel.point_norm, reflet), start.dir);
				final_color = add_color(final_color, drawn_pixel.color);
				if (scene.is_real == CARTOON)
				{
				//	printf("CARTOON\n");
					final_color = cartoon(final_color);
//					printf("r = %f, g = %f, b = %f\n", final_color.r, final_color.g, final_color.b);
				}
				r++;
			}
			if (drawn_pixel.texture != NONE)
			{
				double test = apply_marble_noise(x, y, 90, tab_noise);
				final_color = mult_color(final_color, test / 255);
			}
			if (drawn_pixel.is_negativ == 1)
			{
				white = init_color(255, 255, 255);
				final_color = sub_color(white, final_color);
			}

			put_pixel_on_image(env->img, x, y, final_color);
		}

	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
