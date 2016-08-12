/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 06:18:17 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/12 05:55:35 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_scene		*get_scene(t_scene *scene, t_part *part)
{
	t_elem	*tmp;
	int		is_init;
	int		is_cartoon;

	tmp = part->elems;
	is_init = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "cartoon"))
		{
			if (is_init > 0)
				return (NULL);
			is_cartoon = get_bool(tmp->values);
			scene->is_real = (is_cartoon == 0) ? REALISTIC : CARTOON;
			is_init = 1;
		}
		tmp = tmp->next;
	}
	return (scene);
}

t_cam		*get_cam(t_scene *scene, t_part *part)
{
	t_cam	cam;
	t_elem	*tmp;
	t_vec	*pos;
	t_vec	*lk;

	pos = NULL;
	lk = NULL;
	tmp = part->elems;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "pos"))
		{
			if (!get_new_vec(tmp, &pos))
				return (NULL);
		}
		else if (!ft_strcmp(tmp->name, "look_at"))
		{
			if (!get_new_vec(tmp, &lk))
				return (NULL);
			lk->x = deg_to_rad(lk->x);
			lk->y = deg_to_rad(lk->y);
			lk->z = deg_to_rad(lk->z);
		}
		else
			return (NULL);
		tmp = tmp->next;
	}
	if (!pos || !lk)
	{
		if (!pos)
			ft_putendl("'pos' missing");
		if (!lk)
			ft_putendl("'lk' missing");
		return (NULL);
	}
	cam = init_camera(*pos, *lk);
	add_camera(scene, cam);
	free(pos);
	free(lk);
	return (&(scene->cam));
}

t_light		*init_light(void)
{
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	light->type = 0;
	light->pos = init_vector(0, 0, 0);
	light->look_at = init_vector(0, 0, 0);
	light->color = init_color(0, 0, 0);
	light->angle = 0;
	return (light);
}

t_scene		*get_lights(t_scene *scene, t_part *part)
{
	t_node	*node;
	t_light	*light;
	t_part	*tmp;
	t_elem	*tmp2;
	t_vec	*pos;
	t_vec	*lk;
	t_color	*color;


	if (!(tmp = part->sub_parts))
		return (NULL);
	while (tmp)
	{
		pos = NULL;
		lk = NULL;
		color = NULL;
		if (!(light = init_light()))
			return (NULL);
		light->type = tmp->type;
		tmp2 = tmp->elems;
		while (tmp2)
		{
			if (!ft_strcmp(tmp2->name, "pos"))
			{
				if (!get_new_vec(tmp2, &pos))
					return (NULL);
			}
			else if (!ft_strcmp(tmp2->name, "dir"))
			{
				if (!get_new_vec(tmp2, &lk))
					return (NULL);
			}
			else if (!ft_strcmp(tmp2->name, "color"))
			{
				if (!get_new_color(tmp2, &color, LIGHT))
					return (NULL);
			}
			else if (!ft_strcmp(tmp2->name, "angle"))
			{
				light->angle = deg_to_rad(get_num(tmp2->values));
			}
			else
				return (NULL);
			tmp2 = tmp2->next;
		}
		if (!light->type || !pos || !lk || !color)
		{
			if (!pos)
				ft_putendl("'pos' missing");
			if (!color)
				ft_putendl("'color' missing");
			if (!lk)
				ft_putendl("'lk' missing");
			return (NULL);
		}
		light->pos = *pos;
		light->look_at = *lk;
		light->color = *color;
		if (!(node = init_node(part->type, light, "light", 0)))
			return (NULL);
		node_add(&(scene->lights), node);
		free(pos);
		free(lk);
		free(color);
		tmp = tmp->next;
	}
	return (scene);
}
