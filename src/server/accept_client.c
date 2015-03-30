/*
** accept_client.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 07:48:51 2015 chapui_s
** Last update Sat Mar 21 23:46:25 2015 chapui_s
*/

#include "server.h"

int			accept_client(t_server *server)
{
  struct sockaddr_in	c_addr;
  size_t		size;
  int			value;

  size = sizeof(c_addr);
  value = accept(server->fd, (struct sockaddr*)&(c_addr), (socklen_t*)&size);
  if (value >= 0)
  {
    printf("Connection from %s:%d\n",
	   inet_ntoa(c_addr.sin_addr),
	   (int)ntohs(c_addr.sin_port));
  }
  else
  {
    derror("error: accept");
  }
  return (value);
}
