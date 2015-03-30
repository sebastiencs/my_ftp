/*
** set_user.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 09:35:27 2015 chapui_s
** Last update Sun Mar 22 14:12:29 2015 chapui_s
*/

#include "server.h"

char		*get_attribut(char *s, char *delim)
{
  char		*attr;

  attr = (char*)0;
  s = s + 1 + strlen(delim);
  while (*s && (*s == ' ' || *s == '\t'))
    s += 1;
  if (*s)
  {
    attr = strdup(s);
  }
  return (attr);
}

void		get_new_user(int fd, t_user_list *tmp)
{
  char		*s;

  s = (char*)0;
  while ((s = get_next_line(fd)) && (strcmp(s, "end")))
  {
    if (strncmp(s, "\t", 1))
      derrorn("Warning: parsing users.config error 1");
    else
    {
      if (!strncmp(s + 1, "name:", 5))
	tmp->name = get_attribut(s, "name:");
      else if (!strncmp(s + 1, "password:", 5))
	tmp->password = get_attribut(s, "password:");
      else if (!strncmp(s + 1, "directory:", 5))
	tmp->directory = get_attribut(s, "directory:");
      else
	derrorn("Warning: parsing users.config error 2");
    }
    free(s);
    s = (char*)0;
  }
  free(s);
}

t_user_list	*find_name(t_user_list *list, int nb, char *param)
{
  int		i;

  i = 0;
  while (i < nb)
  {
    if (!strcmp(list[i].name, param))
    {
      return (&list[i]);
    }
    i += 1;
  }
  return ((t_user_list*)0);
}

int		load_user(t_user *user, t_user_list *user_found)
{
  char		buffer[1024];

  memset(&(user->user), 0, sizeof(t_user_list));
  user->user.name = strdup(user_found->name);
  if (user_found->password)
    user->user.password = strdup(user_found->password);
  if (user_found->directory && !chdir(user_found->directory))
  {
    user->user.directory = strdup(user_found->directory);
    user->dir_current = strdup(user->user.directory);
  }
  else
  {
    getcwd(buffer, 1023);
    buffer[strlen(buffer)] = '/';
    user->user.directory = strdup(buffer);
    user->dir_current = strdup(buffer);
    chdir(user->dir_current);
  }
  return (0);
}

int		set_user(t_user *user, char *param)
{
  t_user_list	*user_found;
  t_user_list	*list;
  int		nb_users;

  if (user->status == LOGGED_IN)
  {
    send_reply(user->fd, 550, (char*)0);
    return (0);
  }
  list = get_list_users(&nb_users);
  user_found = find_name(list, nb_users, param);
  if (user_found)
  {
    load_user(user, user_found);
    send_reply(user->fd, (user->user.password) ? (331) : (230), (char*)0);
  }
  else
    send_reply(user->fd, 331, (char*)0);
  user->status = (user_found && user->user.password) ?
    (NOT_LOGGED_IN) : (LOGGED_IN);
  free_list_users(list, nb_users);
  return (0);
}
