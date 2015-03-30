/*
** list_user.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 08:45:29 2015 chapui_s
** Last update Sat Mar 21 23:02:23 2015 chapui_s
*/

#include "server.h"

t_user_list	*init_user_list()
{
  t_user_list	*list;

  list = malloc(sizeof(t_user_list));
  if (list)
  {
    memset(list, 0, sizeof(t_user_list));
    list->name = strdup("Anonymous");
  }
  else
  {
    derror("error: malloc");
  }
  return (list);
}

t_user_list	*add_user_to_list(t_user_list *list,
				 t_user_list *tmp,
				 int n)
{
  t_user_list	*new;
  int		i;

  if ((new = malloc(sizeof(*list) * n)))
  {
    i = 0;
    while (i < n - 1)
    {
      if (list)
	memcpy(&(new[i]), &(list[i]), sizeof(*list));
      i += 1;
    }
    free(list);
    new[i].name = tmp->name;
    new[i].password = tmp->password;
    new[i].directory = tmp->directory;
  }
  return (new);
}

t_user_list	*get_users(int fd, t_user_list *list, int *nb)
{
  t_user_list	tmp;
  char		*s;
  int		i;

  i = 1;
  while ((s = get_next_line(fd)))
  {
    memset(&tmp, 0, sizeof(tmp));
    if (!strcmp(s, "user"))
    {
      get_new_user(fd, &tmp);
      if (tmp.name)
      	list = add_user_to_list(list, &tmp, ++i);
    }
    else if (strlen(s) > 0)
    {
      derrorn("Warning: parsing users.config error");
    }
    free(s);
  }
  *nb = i;
  return (list);
}

t_user_list	*get_list_users(int *nb_users)
{
  t_user_list	*list;
  int		fd;

  list = init_user_list();
  if ((fd = open("users.config", O_RDONLY)) == -1)
    return (list);
  list = get_users(fd, list, nb_users);
  close(fd);
  return (list);
}

void		free_list_users(t_user_list *list, int nb)
{
  int		i;

  i = 0;
  while (i < nb)
  {
    free(list[i].name);
    free(list[i].password);
    free(list[i].directory);
    i += 1;
  }
  free(list);
}
