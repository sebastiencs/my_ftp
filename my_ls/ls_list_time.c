/*
** ls_list_time.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 23:49:41 2013 chapui_s
** Last update Tue Mar 17 22:28:17 2015 chapui_s
*/

#include <stdlib.h>
#include "my_ls.h"

int	time_cmp(time_t t1, time_t t2, char *name, char *next_name)
{
  int	str_cmp_res;

  if (t1 < t2)
    return (-1);
  if (t1 > t2)
    return (1);
  str_cmp_res = my_strcmp(name, next_name);
  return (str_cmp_res);
}

int	push_time_file(t_list_file **pile_file,
		       char *name,
		       time_t time)
{
  t_list_file	*new;
  t_list_file	*tmp;
  t_list_file	*swap;

  tmp = *pile_file;
  if ((new = create_elem(name)) == NULL)
    return (-1);
  while (tmp->next
         && time_cmp(tmp->next->time, time, name, tmp->next->name) > 0)
    tmp = tmp->next;
  if (time_cmp(tmp->time, time, name, tmp->name) > 0)
  {
    swap = tmp->next;
    tmp->next = new;
    new->next = swap;
    new->time = time;
    return (0);
  }
  new->next = *pile_file;
  new->time = time;
  *pile_file = new;
  return (0);
}

int		push_rtime_file(t_list_file **pile_file,
				char *name,
				time_t time)
{
  t_list_file	*new;
  t_list_file	*tmp;
  t_list_file	*swap;

  tmp = *pile_file;
  if ((new = create_elem(name)) == NULL)
    return (-1);
  while (tmp->next
         && time_cmp(tmp->next->time, time, name, tmp->next->name) < 0)
    tmp = tmp->next;
  if (time_cmp(tmp->time, time, name, tmp->name) < 0)
  {
    swap = tmp->next;
    tmp->next = new;
    new->next = swap;
    new->time = time;
    return (0);
  }
  new->next = *pile_file;
  new->time = time;
  *pile_file = new;
  return (0);
}
