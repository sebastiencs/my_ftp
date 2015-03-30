/*
** my_ls.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Nov 25 22:15:56 2013 chapui_s
** Last update Tue Mar 17 19:37:44 2015 chapui_s
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_ls.h"

void	get_max(t_max_size *max, t_infos_file *info)
{
  (info->size_nb_links > (signed)max->nb_links) ?
    (max->nb_links = info->size_nb_links) : (0);
  (info->size_user > (signed)max->user) ? (max->user = info->size_user) : (0);
  (info->size_group > (signed)max->grp) ? (max->grp = info->size_group) : (0);
  (info->size_file > (signed)max->size_file)
    ? (max->size_file = info->size_file) : (0);
}

void	disp_error(char *file_or_dir, int error)
{
  if (error == 1)
    my_putstr_error("my_ls: cannot access ");
  else if (error == 2)
    my_putstr_error("my_ls: cannot open directory ");
  else if (error == 3)
    my_putstr_error("my_ls: cannot read symbolic link ");
  my_putstr_error(file_or_dir);
  my_putstr_error(": ");
  perror("");
}

t_max_size	*init_max(t_max_size *max)
{
  if ((max = (t_max_size*)my_malloc(sizeof(*max))) == NULL)
    return (NULL);
  max->nb_links = 0;
  max->user = 0;
  max->grp = 0;
  max->size_file = 0;
  return (max);
}

char	*str_cat(char *s1, char *s2)
{
  char	*dest;
  int	i;
  int	j;

  if ((dest = (char*)my_malloc(sizeof(char)
			       * (strlen(s1) + strlen(s2) + 3))) == NULL)
    return (NULL);
  memset(dest, 0, strlen(s1) + strlen(s2) + 3);
  i = 0;
  j = 0;
  while (s1[i])
  {
    dest[i] = s1[i];
    i += 1;
  }
  if (dest[i - 1] != '/')
    dest[i++] = '/';
  while (s2[j])
  {
    dest[i + j] = s2[j];
    j += 1;
  }
  dest[i + j] = 0;
  return (dest);
}

int		my_ls(t_options *options, t_list_file *list_file)
{
  t_list_file	*tmp;
  int		test;
  int		is_first;
  int		nb_args;

  is_first = 1;
  if (list_file == NULL)
    if (push_file(options, &list_file, ".", 0) == -1)
      return (-1);
  if (options->d == 1)
    return (disp_the_directory(options, list_file));
  if ((test = ls_files_in_args(options, list_file)) == -1)
    return (-1);
  tmp = list_file;
  if (test > 0 && is_good_dir_in_arg(list_file) > 0)
    my_putchar('\n');
  nb_args = nb_arg(list_file);
  while (tmp)
  {
    if ((test =  ls_directory(options, tmp->name, is_first, nb_args)) == -2)
      return (-1);
    (test != -1) ? (is_first = is_first + 1) : (0);
    tmp = tmp->next;
  }
  return (0);
}
