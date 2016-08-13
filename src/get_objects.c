/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 02:29:09 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/13 00:59:54 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

#include <stdio.h>
t_sphere	*init_sphere(void)
{
	t_sphere	*sphere;

	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		return (NULL);
	sphere->radius = 0;
	sphere->center = init_vector(0, 0, 0);
	sphere->color = init_color(0, 0, 0);
	sphere->specular = 0;
	sphere->reflection = 0;
	sphere->opacity = 1;
	sphere->ref_index = 1;
	sphere->is_negativ = 0;
	sphere->texture = NONE;
	return (sphere);
}

int		get_unsigned_double(t_elem *elem, double *radius)
{
	if (*radius != 0)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined");
		return (0);
	}
	 *radius = get_num(elem->values);
	 if (radius < 0)
	 {
		ft_putendl("'radius' < 0");
		return (0);
	 }
	return (1);
}

int		get_new_vec(t_elem *elem, t_vec **pos)
{
	if (*pos)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined");
		return (0);
	}
	if (!(*pos = get_vec(elem->values, elem->name)))
		return (0);
	return (1);
}

int		get_new_quad(t_elem *elem, t_quad **quad)
{
	if (*quad)
	{
		write(1, "'", 1);
		ft_putstr(elem->name);
		ft_putendl("' redefined");
		return (0);
	}
	if (!(*quad = get_quad(elem->values)))
		return (0);
	return (1);
}

int		get_new_color(t_elem *elem, t_color **color, int type)
{
	if (*color)
	{
		ft_putendl("'color' redefined");
		return (0);
	}
	if (!(*color = get_color(elem->values, type)))
		return (0);
	return (1);
}

int			get_specular(t_elem *elem, int *specular)
{
	if (*specular != 0)
	{
		ft_putendl("'specular' redefined");
		return (0);
	}
	*specular = (int)get_num(elem->values);
	if (*specular < 0 || *specular > 100)
	{
		ft_putendl("'specular' < 0 or > 100");
		return (0);
	}
	return (1);
}

int			get_reflection(t_elem *elem, double *reflection)
{
	if (*reflection != 0)
	{
		ft_putendl("'reflection' redefined");
		return (0);
	}
	*reflection = get_num(elem->values);
	if (*reflection < 0 || *reflection > 1)
	{
		ft_putendl("'reflection' < 0 or > 1");
		return (0);
	}
	return (1);
}

int			get_opacity(t_elem *elem, double *opacity)
{
	if (*opacity != 1)
	{
		ft_putendl("'opacity' redefined");
		return (0);
	}
	*opacity = get_num(elem->values);
	if (*opacity < 0 || *opacity > 1)
	{
		ft_putendl("'opacity' < 0 or > 1");
		return (0);
	}
	return (1);
}

int			get_ref_index(t_elem *elem, double *ref_index)
{
	if (*ref_index != 1)
	{
		ft_putendl("'ref_index' redefined");
		return (0);
	}
	*ref_index = get_num(elem->values);
	if (*ref_index < 1 || *ref_index > 10)
	{
		ft_putendl("'ref_index' < 1 or > 10");
		return (0);
	}
	return (1);
}

int			get_is_negativ(t_elem *elem, int *is_negativ)
{
	if ((*is_negativ = get_bool(elem->values)) == -1)
	{
		ft_putendl("value of 'is_negativ' != 'y' and 'n'");
		return (0);
	}
	return (1);
}

int			get_texture(t_elem *elem, int *texture)
{
	if (*texture != NONE)
	{
		ft_putendl("'texture' redefined");
		return (0);
	}
	*texture = get_enum(elem->values);
	if (*texture == -1)
	{
		ft_putstr("texture '");
		ft_putstr(elem->values[0]);
		ft_putendl("' does not exist");
		return (0);
	}
	return (1);
}

void		return_invalid_arg(char *name)
{
	ft_putstr("'");
	ft_putstr(name);
	ft_putendl("' invalid");
}

t_sphere	*get_sphere(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos;
	t_color		*color;
	t_sphere	*sphere;

	pos = NULL;
	color = NULL;
	if (!(sphere = init_sphere()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "radius"))
		{
			if (!get_unsigned_double(tmp2, &(sphere->radius)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "pos"))
		{
			if (!get_new_vec(tmp2, &pos))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
			if (!get_specular(tmp2, &(sphere->specular)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
			if (!get_reflection(tmp2, &(sphere->reflection)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
			if (!get_opacity(tmp2, &(sphere->opacity)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
			if (!get_ref_index(tmp2, &(sphere->ref_index)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_is_negativ(tmp2, &(sphere->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_texture(tmp2, &(sphere->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos || !color)
	{
		if (!pos)
			ft_putendl("'pos' missing");
		if (!color)
			ft_putendl("'color' missing");
		return (NULL);
	}
	sphere->center = *pos;
	sphere->color = *color;
	free(pos);
	free(color);
	return (sphere);
}

t_plane	*init_plane(void)
{
	t_plane	*plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		return (NULL);
	plane->pos = init_vector(0, 0, 0);
	plane->normal = init_vector(0, 0, 0);
	plane->color = init_color(0, 0, 0);
	plane->specular = 0;
	plane->reflection = 0;
	plane->opacity = 1;
	plane->ref_index = 1;
	plane->is_negativ = 0;
	plane->texture = NONE;
	return (plane);
}


t_plane	*get_plane(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos;
	t_vec		*normal;
	t_color		*color;
	t_plane	*plane;

	pos = NULL;
	normal = NULL;
	color = NULL;
	if (!(plane = init_plane()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "pos"))
		{
			if (!get_new_vec(tmp2, &pos))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "normal"))
		{
			if (!get_new_vec(tmp2, &normal))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
			if (!get_specular(tmp2, &(plane->specular)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
			if (!get_reflection(tmp2, &(plane->reflection)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
			if (!get_opacity(tmp2, &(plane->opacity)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
			if (!get_ref_index(tmp2, &(plane->ref_index)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_is_negativ(tmp2, &(plane->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_texture(tmp2, &(plane->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos || !color || !normal)
	{
		if (!pos)
			ft_putendl("'pos' missing");
		if (!color)
			ft_putendl("'color' missing");
		if (!normal)
			ft_putendl("'normal' missing");
		return (NULL);
	}
	plane->pos = *pos;
	plane->normal = *normal;
	plane->color = *color;
	free(pos);
	free(normal);
	free(color);
	return (plane);
}

t_cylinder	*init_cylinder(void)
{
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cylinder->radius = 0;
	cylinder->pos = init_vector(0, 0, 0);
	cylinder->dir = init_vector(0, 0, 0);
	cylinder->color = init_color(0, 0, 0);
	cylinder->length = 0;
	cylinder->h = 0;
	cylinder->specular = 0;
	cylinder->reflection = 0;
	cylinder->opacity = 1;
	cylinder->ref_index = 1;
	cylinder->is_negativ = 0;
	cylinder->texture = NONE;
	return (cylinder);
}

t_cylinder	*get_cylinder(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos;
	t_vec		*dir;
	t_color		*color;
	t_cylinder	*cylinder;

	pos = NULL;
	dir = NULL;
	color = NULL;
	if (!(cylinder = init_cylinder()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "radius"))
		{
			if (!get_unsigned_double(tmp2, &(cylinder->radius)))
				 return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "pos"))
		{
			if (!get_new_vec(tmp2, &pos))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "dir"))
		{
			if (!get_new_vec(tmp2, &dir))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "length"))
		{
			if (!get_unsigned_double(tmp2, &(cylinder->length)))
				 return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				 return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
			if (!get_specular(tmp2, &(cylinder->specular)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
			if (!get_reflection(tmp2, &(cylinder->reflection)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
			if (!get_opacity(tmp2, &(cylinder->opacity)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
			if (!get_ref_index(tmp2, &(cylinder->ref_index)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_is_negativ(tmp2, &(cylinder->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_texture(tmp2, &(cylinder->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos || !color || !dir)
	{
		if (!pos)
			ft_putendl("'pos' missing");
		if (!color)
			ft_putendl("'color' missing");
		if (!dir)
			ft_putendl("'dir' missing");
		return (NULL);
	}
	cylinder->pos = *pos;
	cylinder->dir = *dir;
	cylinder->color = *color;
	free(pos);
	free(dir);
	free(color);
	return (cylinder);
}


t_cone	*init_cone(void)
{
	t_cone	*cone;

	if (!(cone = (t_cone *)malloc(sizeof(t_cone))))
		return (NULL);
	cone->r = 0;
	cone->pos = init_vector(0, 0, 0);
	cone->dir = init_vector(0, 0, 0);
	cone->color = init_color(0, 0, 0);
	cone->len = 0;
	cone->specular = 0;
	cone->reflection = 0;
	cone->opacity = 1;
	cone->ref_index = 1;
	cone->is_negativ = 0;
	cone->texture = NONE;
	return (cone);
}

t_cone	*get_cone(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos;
	t_vec		*dir;
	t_color		*color;
	t_cone	*cone;

	pos = NULL;
	dir = NULL;
	color = NULL;
	if (!(cone = init_cone()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "radius"))
		{
			if (!get_unsigned_double(tmp2, &(cone->r)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "pos"))
		{
			if (!get_new_vec(tmp2, &pos))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "dir"))
		{
			if (!get_new_vec(tmp2, &dir))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "length"))
		{
			if (!get_unsigned_double(tmp2, &(cone->len)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
			if (!get_specular(tmp2, &(cone->specular)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
			if (!get_reflection(tmp2, &(cone->reflection)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
			if (!get_opacity(tmp2, &(cone->opacity)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
			if (!get_ref_index(tmp2, &(cone->ref_index)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_is_negativ(tmp2, &(cone->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_texture(tmp2, &(cone->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos || !color || !dir)
	{
		if (!pos)
			ft_putendl("'pos' missing");
		if (!color)
			ft_putendl("'color' missing");
		if (!dir)
			ft_putendl("'dir' missing");
		return (NULL);
	}
	cone->pos = *pos;
	cone->dir = *dir;
	cone->color = *color;
	free(pos);
	free(dir);
	free(color);
	return (cone);
}

t_elips	*init_elips(void)
{
	t_elips	*elips;

	if (!(elips = (t_elips *)malloc(sizeof(t_elips))))
		return (NULL);
	elips->radius = 0;
	elips->center = init_vector(0, 0, 0);
	elips->quad.A = 0;
	elips->quad.B = 0;
	elips->quad.C = 0;
	elips->color = init_color(0, 0, 0);
	elips->specular = 0;
	elips->reflection = 0;
	elips->opacity = 1;
	elips->ref_index = 1;
	elips->is_negativ = 0;
	elips->texture = NONE;
	return (elips);
}

t_elips	*get_elips(t_part *part)
{
	t_elem		*tmp2;
	t_vec		*pos;
	t_quad		*quad;
	t_color		*color;
	t_elips	*elips;

	pos = NULL;
	quad = NULL;
	color = NULL;
	if (!(elips = init_elips()))
		return (NULL);
	tmp2 = part->elems;
	while (tmp2)
	{
		if (!ft_strcmp(tmp2->name, "radius"))
		{
			if (!get_unsigned_double(tmp2, &(elips->radius)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "pos"))
		{
			if (!get_new_vec(tmp2, &pos))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "quad"))
		{
			if (!get_new_quad(tmp2, &quad))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "color"))
		{
			if (!get_new_color(tmp2, &color, OBJECT))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "specular"))
		{
			if (!get_specular(tmp2, &(elips->specular)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "reflection"))
		{
			if (!get_reflection(tmp2, &(elips->reflection)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "opacity"))
		{
			if (!get_opacity(tmp2, &(elips->opacity)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "ref_index"))
		{
			if (!get_ref_index(tmp2, &(elips->ref_index)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "is_negativ"))
		{
			if (!get_is_negativ(tmp2, &(elips->is_negativ)))
				return (NULL);
		}
		else if (!ft_strcmp(tmp2->name, "texture"))
		{
			if (!get_texture(tmp2, &(elips->texture)))
				return (NULL);
		}
		else
		{
			return_invalid_arg(tmp2->name);
			return (NULL);
		}
		tmp2 = tmp2->next;
	}
	if (!pos || !quad || !color)
	{
		if (!pos)
			ft_putendl("'pos' missing");
		if (!color)
			ft_putendl("'color' missing");
		if (!quad)
			ft_putendl("'quad' missing");
		return (NULL);
	}
	elips->center = *pos;
	elips->quad = *quad;
	elips->color = *color;
	free(pos);
	free(quad);
	free(color);
	return (elips);
}

t_scene		*get_objects(t_scene *scene, t_part *part)
{
	t_node	*node;
	t_part	*tmp;
	void	*data;

	if (!(tmp = part->sub_parts))
	{
		ft_putendl("Empty Object");
		return (NULL);
	}
	while (tmp)
	{
		data = NULL;
		if (tmp->type == SPHERE)
		{
			if (!(data = get_sphere(tmp)))
			{
				return (NULL);
			}
		}
		else if (tmp->type == CYLINDER)
		{
			if (!(data = get_cylinder(tmp)))
				return (NULL);
		}
		else if (tmp->type == PLANE)
		{
			if (!(data = get_plane(tmp)))
				return (NULL);
		}
		else if (tmp->type == CONE)
		{
			if (!(data = get_cone(tmp)))
				return (NULL);
		}
		else if (tmp->type == ELIPS)
		{
			if (!(data = get_elips(tmp)))
				return (NULL);
		}
		else
			return (NULL);
		if (!(node = init_node(tmp->type, data, "obj", 0)))
			return (NULL);
		node_add(&(scene->objects), node);
		tmp = tmp->next;
	}
	return (scene);
}
