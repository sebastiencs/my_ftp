/*
** receive_file.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 18:30:15 2015 chapui_s
** Last update Tue Mar 17 21:49:33 2015 chapui_s
*/

#include "server.h"

int		receive_file(t_user *user, char *param)
{
  int		fd;

  if ((fd = open(param, O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (-1);
  user->thread_info->data = (void*)(&fd);
  user->thread_info->size_data = 0;
  user->thread_info->read_or_write = 0;
  sem_post(&g_lock);
  send_reply(user->fd, 150, (char*)0);
  sem_wait(&g_lock_finish);
  user->thread_info =(t_thread_info*)0;
  user->mode = NONE;
  close(fd);
  send_reply(user->fd, (g_transfer_completed) ? (226) : (550) , (char*)0);
  sem_post(&g_lock_finish);
  return (0);
}
