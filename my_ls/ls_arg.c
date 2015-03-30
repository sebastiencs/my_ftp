/*
** ls_arg.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 23:08:48 2013 chapui_s
** Last update Tue Mar 17 04:04:25 2015 chapui_s
*/

#include "my_ls.h"

int		recurs_ls(t_options *options, char *dir_name,
			  t_list_file *list_files_dir)
{
  char		*name_without_path;
  t_list_file	*tmp;

  (void)dir_name;
  tmp = list_files_dir;
  while (tmp)
  {
    name_without_path = cut_name(tmp->name);
    if (name_without_path[0] != '.')
      if ((ls_directory(options, tmp->name, 2, 5)) == -2)
        return (-1);
    tmp = tmp->next;
  }
  return (0);
}

int		is_good_dir_in_arg(t_list_file *list_file)
{
  t_list_file	*tmp;
  struct stat	res_stat;
  int		nb_good_dir;

  tmp = list_file;
  nb_good_dir = 0;
  while (tmp)
  {
    if (lstat(tmp->name, &res_stat) != -1 && (S_ISDIR(res_stat.st_mode)))
      nb_good_dir = nb_good_dir + 1;
    tmp = tmp->next;
  }
  return (nb_good_dir);
}

int		nb_arg(t_list_file *list_file)
{
  t_list_file	*tmp;
  int		nb_arg;

  tmp = list_file;
  nb_arg = 0;
  while (tmp)
  {
    nb_arg = nb_arg + 1;
    tmp = tmp->next;
  }
  return (nb_arg);
}
