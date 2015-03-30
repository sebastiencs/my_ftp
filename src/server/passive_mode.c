/*
** passive_mode.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 20:58:14 2015 chapui_s
** Last update Sat Mar 21 23:07:38 2015 chapui_s
*/

#include "server.h"

int		loop_try_port(struct sockaddr_in *s_addr,
			      int fd)
{
  int		unused;
  int		i;

  unused = 1;
  i = PORT_PASSIVE_MIN;
  while (i < PORT_PASSIVE_MAX)
  {
    memset(s_addr, 0, sizeof(*s_addr));
    s_addr->sin_family = AF_INET;
    s_addr->sin_addr.s_addr = INADDR_ANY;
    s_addr->sin_port = htons(i);
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
		   &unused, sizeof(int)) != -1)

      if ((bind(fd, (struct sockaddr*)s_addr,
		sizeof((*s_addr)))) != -1)
	if ((listen(fd, CLIENTS_MAX)) != -1)
	  return (i);
    i += 1;
  }
  return (-1);
}

int		passive_failed(t_user *user)
{
  free(user->thread_info);
  user->thread_info = (t_thread_info*)0;
  user->mode = NONE;
  send_reply(user->fd, 553, (char*)0);
  return (-1);
}

int			start_listen(t_user *user, int *fd, int *port)
{
  struct sockaddr_in	server_addr;

  if (sem_trywait(&g_lock) != 0)
    return (passive_failed(user));
  if ((*fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (derror("error: socket"));
  if ((*port = loop_try_port(&server_addr, *fd)) == -1)
    return (-1);
  return (0);
}

char		*format_addr(char *ip, int port)
{
  char		*s;
  int		i;

  if ((s = (char*)malloc(sizeof(char) * 50)) == (char*)0)
    return ((char*)0);
  sprintf(s, "%s,%d,%d", ip, port >> 8, port & 0xFF);
  i = 0;
  while (s[i])
  {
    if (s[i] == '.')
      s[i] = ',';
    i += 1;
  }
  return (s);
}

int		enter_passive_mode(t_user *user, char *param)
{
  t_thread_info	*info;
  int		port;
  int		fd;
  char		*s;

  (void)param;
  if (start_listen(user, &fd, &port) == -1
      || (info = (t_thread_info*)malloc(sizeof(*info))) == (void*)0)
    return (passive_failed(user));
  memset(info, 0, sizeof(*info));
  info->fd = fd;
  user->thread_info = info;
  if (create_thread_detach(info, user) == -1)
    return (passive_failed(user));
  usleep(500);
  if ((s = format_addr(user->local_ip, port)) == (char*)0)
    return (passive_failed(user));
  send_reply(user->fd, 227, s);
  user->mode = PASSIVE;
  return (0);
}
