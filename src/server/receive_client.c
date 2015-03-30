/*
** receive_client.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 22:12:40 2015 chapui_s
** Last update Sun Mar 22 15:14:41 2015 chapui_s
*/

#include "server.h"

int			init_client(t_user *user, t_server *server)
{
  memset(user, 0, sizeof(t_user));
  close(server->fd);
  user->run = 1;
  user->status = NOT_LOGGED_IN;
  user->fd = server->fd_client;
  user->buffer = (char*)malloc(sizeof(char) * SIZE_MAX_BUFFER);
  if (!(user->buffer))
    return (derror("error: malloc"));
  user->local_ip = server->local_ip;
  sem_init(&g_lock, 0, 1);
  sem_init(&g_lock_finish, 0, 1);
  return (0);
}

static void		manage_sigint(t_user *ptr)
{
  static t_user		*user;

  if (ptr)
  {
    user = ptr;
  }
  else
  {
    sem_destroy(&g_lock);
    sem_destroy(&g_lock_finish);
    free(user->buffer);
    free(user->dir_current);
    close(user->fd);
    puts("Exiting server...");
    exit(0);
  }
}

static void		catch_sigint(int sig)
{
  (void)sig;
  manage_sigint((t_user*)0);
}

int			manage_clients(t_server *server)
{
  t_user		user;

  if (init_client(&user, server))
    return (-1);
  if (send_reply(user.fd, 220, (char*)0) == -1)
    return (-1);
  manage_sigint(&user);
  signal(SIGINT, catch_sigint);
  while (user.run)
  {
    if (get_command(&user))
      return (-1);
    exec_command(&user);
  }
  printf("Client disconnect\n");
  free(user.buffer);
  return (0);
}

int			receive_clients(t_server *server)
{
  int			fd_client;
  int			pid;

  while (1)
  {
    if ((fd_client = accept_client(server)) == -1)
      return (-1);
    if ((pid = fork()) == 0)
    {
      server->fd_client = fd_client;
      manage_clients(server);
      close(fd_client);
      return (0);
    }
    else if (pid > 0)
      close(fd_client);
    else
      derror("warning: fork failed");
  }
  return (0);
}
