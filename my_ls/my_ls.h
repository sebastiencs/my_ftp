/*
** my_ls.h for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Nov 25 18:49:09 2013 chapui_s
** Last update Tue Mar 17 19:32:10 2015 chapui_s
*/

#ifndef MY_LS_H_
# define MY_LS_H_

# include <time.h>
# include <sys/stat.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>

typedef struct	s_options
{
  int		l;
  int		R;
  int		d;
  int		r;
  int		t;
  int		g;
  int		F;
}		t_options;

typedef struct		s_infos_file
{
  mode_t		permissions;
  int			size_nb_links;
  int			size_user;
  int			size_group;
  int			size_file;
  char			*modif_date;
}			t_infos_file;

typedef struct		s_list_file
{
  char			*name;
  mode_t		time;
  t_infos_file		*infos;
  struct s_list_file	*next;
}			t_list_file;

typedef struct		s_max_size
{
  unsigned int		nb_links;
  unsigned int		user;
  unsigned int		grp;
  unsigned int		size_file;
}			t_max_size;

unsigned int	print_block_allocated(char *dir_name);
void		*my_malloc(size_t size);
void		my_putchar(char c);
void		my_putnbr(int nb);
void		my_putstr(char *str);
void		my_putchar_error(char c);
void		my_putstr_error(char *str);
int		get_options(char *str, t_options **options);
int		push_file(t_options *options, t_list_file **pile_file,
			  char *name, time_t time);
int		size_nb(unsigned long long nb);
int		my_printf(const char *format, ...);
char		*print_year(time_t *time_arg);
void		print_permissions(mode_t st_mode);
int		print_device(t_max_size *max, struct stat *res_stat,
			     char *file_name, int g);
int		print_file(t_max_size *max, struct stat *res_stat,
			   char *file_name, int g);
char		*str_cat(char *s1, char *s2);
int		write_lnk(struct stat *res_stat, char *file_name);
int		ls_files_in_args(t_options *options, t_list_file *list_file);
int		ls_regulars_files(t_options *options, t_list_file *list_file,
				  int is_cut);
int		disp_infos_file(t_options *options, t_list_file *file,
				t_max_size *max);
int		prepare_info_file(t_options *options, t_list_file *tmp,
				  t_max_size *max);
char		*cut_name(char *name);
t_max_size	*init_max(t_max_size *max);
void		disp_error(char *file_or_dir, int error);
void		print_dir_name(char *dir_name);
int		finish_ls_directory(t_options *options,
				    t_list_file *list_files_dir,
				    char *dir_name);
int		gere_options_dir(t_options *options, int is_first,
				 char *dir_name, int test_args);
int		ls_directory(t_options *options, char *dir_name,
			     int is_first, int test_args);
int		disp_the_directory(t_options *options,
				   t_list_file *list_file);
char		*cut_time(time_t *time_arg);
int		recurs_ls(t_options *options, char *dir_name,
			  t_list_file *list_files_dir);
int		is_good_dir_in_arg(t_list_file *list_file);
int		nb_arg(t_list_file *list_file);
void		get_max(t_max_size *max, t_infos_file *info);
char		to_lower(char c);
int		my_strcmp(char *s1, char *s2);
int		push_sort_file(t_list_file **pile_file, char *name);
int		push_rsort_file(t_list_file **pile_file, char *name);
t_list_file	*create_elem(char *name);
int		push_time_file(t_list_file **pile_file, char *name,
			       time_t time);
int		push_rtime_file(t_list_file **pile_file, char *name,
				time_t time);
void		free_list_file(t_list_file **pile);
int		init_options(t_options **options);
int		get_option(char *str, t_options **options);
int		my_ls(t_options *options, t_list_file *list_file);
unsigned int	my_strlen(char *s);
int		print_directories(t_max_size *max,
				  struct stat *res_stat,
				  char *file_name, int g);

#endif /* !MY_LS_H_ */
