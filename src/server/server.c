/*
** server.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 06:33:58 2015 chapui_s
** Last update Sun Mar 22 15:08:55 2015 chapui_s
*/

#include "server.h"

static void		manage_sigint(t_server *ptr)
{
  static t_server	*server;

  if (ptr)
  {
    server = ptr;
  }
  else
  {
    close(server->fd);
    free(server->local_ip);
    puts("Exit server...");
    exit(0);
  }
}

static void	catch_sigint(int sig)
{
  (void)sig;
  manage_sigint((t_server*)0);
}

int		main(int argc, char **argv)
{
  t_server	server;

  (void)argc;
  manage_sigint(&server);
  signal(SIGINT, catch_sigint);
  memset(&server, 0, sizeof(t_server));
  if (argc < 2
      || get_port(&server, argv[1])
      || create_server(&server)
      || receive_clients(&server))
    return (-1);
  return (0);
}
