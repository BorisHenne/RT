/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sduprey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 06:31:18 by sduprey           #+#    #+#             */
/*   Updated: 2016/08/09 23:54:11 by sduprey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

typedef struct	s_bmpih
{
	char		id[2]; // "BM" bmp format
	long		filesize;
	int			reserved[2];
	long		headersize;
	long		infosize;
	long		width;
	long		depth;
	short		plane;
	short		bits;
	long		compr;
	long		sizeimg;
	long		xppm;
	long		yppm;
	long		clrused;
	long		clrimpor;
	//int			bpl;
}				t_bmpih;

t_bmpih		init_bmp_info_header(void)
{
	t_bmpih	bih;
	int		bpl; // bytes per line

	memset((char *)&bih, 0, sizeof(t_bmpih));
	ft_memcpy(&bih.id, "BM", 2);
	bih.filesize = 0;
	memset(&bih.reserved, 0, 2); // reserved 2 zero bytes
	bih.headersize = 0x36;
	bih.infosize = 0x28;
	bih.width = WIDTH;
	bih.depth = HEIGHT;
	bih.plane = 1;
	bih.bits = 24;
	bih.compr = 0;

	bpl = bih.width * 3;
	if (bpl & 0x0003)
	{
		bpl |= 0x0003;
		++bpl;
	}
	//bih.bpl = bpl;
	bih.filesize = bih.headersize + (long)bpl * bih.depth;
	return (bih);
}

/*
   void		save_bmp(void *img)
   {
   t_bmpih	bih;
   FILE	*file;
   int		x;
   int		y;
   t_color	c;

   bih = init_bmp_info_header();
   file = fopen("test_img.bmp", "a");
   if (file != NULL)
   {
   fwrite(&bih, 1, sizeof(bih), file);
   y = 0;
   while (y < HEIGHT)
   {
   x = 0;
   while (x < WIDTH)
   {
   int	n;

   c = get_pixel_color(img, x, y);
   n = (int)c.b;
   fwrite(&n, 1, 8, file);
   n = (int)c.g;
   fwrite(&n, 1, 8, file);
   n = (int)c.r;
   fwrite(&n, 1, 8, file);
   x++;
   }
   y++;
   }
   fclose(file);
   }
   }
   */


void		save_bmp(void *img)
{
	int		i;
	int		j;
	int		x;
	t_color	c;
	int		fd;
	//char	*str;


	int w = 1920;
	int h = 1080;
	//int	bpp = 

	fd = open("test_img.bmp", O_RDWR | O_CREAT);
	printf("fd: %d\n", fd);
	if (fd > 0)
	{
		x = 0x42;
		write(fd, &x, 1);
		x = 0x4D;
		write(fd, &x, 1);
		x = w * h * 24 + 54;
		write(fd, &x, 4);
		x = 0x00000000;
		write(fd, &x, 4);
		x = 54; // pixel offset
		write(fd, &x, 4);
		x = 40;
		write(fd, &x, 4);
		x = w;
		write(fd, &x, 4);
		x = h;
		write(fd, &x, 4);
		x = 1;
		write(fd, &x, 2);
		x = 24;
		write(fd, &x, 2);
		x = 0;
		write(fd, &x, 4);
		write(fd, &x, 4); // size of raw pixel data
		x = 0;
		write(fd, &x, 4);
		write(fd, &x, 4);
		x = 0x00000000;
		write(fd, &x, 4);
		write(fd, &x, 4);
		//
		j = h;
		while (j)
		{
			i = 0;
			while (i < w)
			{
				int xr, xg, xb;

				char data[3];

				c = get_pixel_color(img ,i, j);

				data[2] = (int)c.r;
				data[1] = (int)c.g;
				data[0] = (int)c.b;

				xr = (int)c.r | 0x00000000;
				xg = (int)c.g | xr << 8;
				xb = (int)c.b | xg << 8;
				write(fd, &data, sizeof(data));
				i++;
			}
			j--;
		}
		close(fd);
	}
}
