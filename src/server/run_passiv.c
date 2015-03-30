/*
** run_passiv.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 02:06:23 2015 chapui_s
** Last update Sun Mar 29 04:13:52 2015 chapui_s
*/

#include <errno.h>
#include "server.h"

int			read_data(t_thread_info *info, int fd_client)
{
  char			buffer[4096];
  int			fd_file;
  ssize_t		size;

  fd_file = *((int*)(info->data));
  signal(SIGPIPE, SIG_IGN);
  while ((size = read(fd_client, buffer, 4096)) != -1 && size != 0)
  {
    if (write(fd_file, buffer, size) == -1)
      return (-1);
  }
  if (size != -1)
  {
    g_transfer_completed = 1;
  }
  return (0);
}

void			write_data(t_thread_info *info, int fd)
{
  void			*data;
  ssize_t		size;
  ssize_t		size_cur;

  data = info->data;
  size = info->size_data;
  signal(SIGPIPE, SIG_IGN);
  while (size > 0 && (size_cur = write(fd, data, size)) > 0)
  {
    size -= size_cur;
    data = data + (size_t)size_cur;
  }
  if (size_cur != -1)
  {
    g_transfer_completed = 1;
  }
}

void			*run_passive(t_thread_info *info)
{
  struct sockaddr_in	c_addr;
  size_t		size;
  int			fd;

  sem_wait(&g_lock_finish);
  size = sizeof(c_addr);
  fd = accept(info->fd, (struct sockaddr*)&(c_addr), (socklen_t*)&size);
  sem_wait(&g_lock);
  g_transfer_completed = 0;
  if (info->read_or_write == 1)
  {
    write_data(info, fd);
  }
  else if (info->read_or_write == 0)
  {
    read_data(info, fd);
  }
  close(fd);
  close(info->fd);
  free(info);
  sem_post(&g_lock_finish);
  sem_post(&g_lock);
  return ((void*)0);
}
