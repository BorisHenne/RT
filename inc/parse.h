/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:27:54 by nbelouni          #+#    #+#             */
/*   Updated: 2016/08/22 16:54:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <scene.h>
# include <fcntl.h>
# include <quad.h>

typedef struct		s_elem
{
	char			*name;
	int				n_values;
	char			**values;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_part
{
	int				type;
	int				n_elems;
	t_elem			*elems;
	struct s_part	*sub_parts;
	struct s_part	*next;
}					t_part;

t_part				*create_part(void);
void				free_part(t_part **part);
t_elem				*create_elem(void);
void				free_elem(t_elem **elem);

int					arr_len(char **array);
char				**cpy_carray(char **array);

int					is_number(char *s);
int					is_valid(char *s);
int					is_initialized(int *is_init, t_scene *scene);

t_vec				*get_vec(char **values, char *name);
float				get_num(char **values);
int					get_bool(char **values);
int					get_enum(char **values);
t_color				*get_color(char **values, int ref);
t_quad				*get_quad(char **values);

int					get_unsigned_double(t_elem *elem, double *radius);
int					get_new_vec(t_elem *elem, t_vec **pos);
int					get_new_quad(t_elem *elem, t_quad **quad);
int					get_new_color(t_elem *elem, t_color **color, int type);

t_scene				*get_scene(t_scene *scene, t_part *part);
t_cam				*get_cam(t_scene *scene, t_part *part);
t_scene				*get_lights(t_scene *scene, t_part *part);
t_scene				*get_objects(t_scene *scene, t_part *part);

char				*get_file_content(char *file_name);
int					find_type(char *s);
char				*find_scop(char *s, int ref_level);
t_part				*parse_scop(char *scop);

t_scene				*parse(char *file_name);

#endif
