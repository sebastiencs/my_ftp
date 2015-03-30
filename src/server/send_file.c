/*
** send_file.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 17:06:19 2015 chapui_s
** Last update Sun Mar 22 15:24:19 2015 chapui_s
*/

#include "server.h"

int		is_regular_file(char *file)
{
  struct stat	st;

  if (!stat(file, &st) && S_ISREG(st.st_mode))
    return (0);
  else
    return (-1);
}

void		give_file_to_thread(t_user *user, void *data, size_t size)
{
  user->thread_info->data = data;
  user->thread_info->size_data = size;
  user->thread_info->read_or_write = 1;
  sem_post(&g_lock);
  send_reply(user->fd, 150, (char*)0);
  sem_wait(&g_lock_finish);
  munmap(data, size);
  user->thread_info = (t_thread_info*)0;
  user->mode = NONE;
  send_reply(user->fd, (g_transfer_completed) ? (226) : (550) , (char*)0);
  sem_post(&g_lock_finish);
}

int		send_failed(t_user *user, int fd)
{
  (void)fd;
  user->thread_info->data = (void*)0;
  user->thread_info->size_data = 0;
  user->thread_info->read_or_write = -1;
  sem_post(&g_lock);
  user->thread_info = (t_thread_info*)0;
  send_reply(user->fd, 553, (char*)0);
  return (-1);
}

int		send_file(t_user *user, char *param)
{
  char		buffer[PATH_MAX];
  char		tmp[PATH_MAX];
  void		*data;
  int		fd;
  size_t	size;

  memset(buffer, 0, PATH_MAX);
  memset(tmp, 0, PATH_MAX);
  if (param[0] == '/')
    param = manage_from_root(user, buffer, param);
  realpath(param, tmp);
  if (strncmp(tmp, user->user.directory, strlen(user->user.directory)))
  {
    param = user->user.directory;
    strcpy(tmp, param);
  }
  if (is_regular_file(tmp) == -1
      || (fd = open(tmp, O_RDONLY)) == -1)
    return (send_failed(user, fd));
  size = get_size_file(tmp);
  if (!(data = mmap((void*)0, size, PROT_READ, MAP_PRIVATE, fd, 0)))
    return (send_failed(user, fd));
  close(fd);
  give_file_to_thread(user, data, size);
  return (0);
}
