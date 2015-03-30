##
## Makefile for epitech in /home/chapuis_s/rendu/
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Mon Mar 16 06:29:23 2015 chapui_s
## Last update Sun Mar 29 04:58:54 2015 chapui_s
##

server		= serveur

client		= client

my_ls_lib	= my_ls.a

SRC_DIR		= ./src

NAME		=

MY_LS_DIR	= my_ls

SERVER_DIR	= $(SRC_DIR)/server

CLIENT_DIR	= $(SRC_DIR)/client

COMMON_DIR	= $(SRC_DIR)/common

SRC_COMMON	= $(COMMON_DIR)/derror.c		\
		  $(COMMON_DIR)/get_next_line.c		\
		  $(COMMON_DIR)/is_nb.c			\
		  $(COMMON_DIR)/free_get_next_line.c

OBJ_COMMON	= $(SRC_COMMON:.c=.o)

SRC_SERVER	= $(SERVER_DIR)/server.c		\
		  $(SERVER_DIR)/usage.c			\
		  $(SERVER_DIR)/set_user.c		\
		  $(SERVER_DIR)/passive_mode.c		\
		  $(SERVER_DIR)/list_user.c		\
		  $(SERVER_DIR)/get_command.c		\
		  $(SERVER_DIR)/quit.c			\
		  $(SERVER_DIR)/receive_file.c		\
		  $(SERVER_DIR)/help.c			\
		  $(SERVER_DIR)/exec_command.c		\
		  $(SERVER_DIR)/send_reply.c		\
		  $(SERVER_DIR)/receive_client.c	\
		  $(SERVER_DIR)/send_file.c		\
		  $(SERVER_DIR)/get_dir.c		\
		  $(SERVER_DIR)/delete.c		\
		  $(SERVER_DIR)/get_type.c		\
		  $(SERVER_DIR)/create_thread_detach.c	\
		  $(SERVER_DIR)/change_dir.c		\
		  $(SERVER_DIR)/convert_telnet_dir.c	\
		  $(SERVER_DIR)/run_passiv.c		\
		  $(SERVER_DIR)/password.c		\
		  $(SERVER_DIR)/noop.c			\
		  $(SERVER_DIR)/list_directory.c	\
		  $(SERVER_DIR)/send_syst.c		\
		  $(SERVER_DIR)/accept_client.c		\
		  $(SERVER_DIR)/create_server.c		\
		  $(SERVER_DIR)/get_port.c

OBJ_SERVER	= $(SRC_SERVER:.c=.o)

SRC_CLIENT	= $(CLIENT_DIR)/client.c		\
		  $(CLIENT_DIR)/my_str_to_wordtab.c	\
		  $(CLIENT_DIR)/send_user.c		\
		  $(CLIENT_DIR)/send_password.c		\
		  $(CLIENT_DIR)/change_dir.c		\
		  $(CLIENT_DIR)/quit_client.c		\
		  $(CLIENT_DIR)/identification.c	\
		  $(CLIENT_DIR)/delete.c		\
		  $(CLIENT_DIR)/pwd.c			\
		  $(CLIENT_DIR)/help.c			\
		  $(CLIENT_DIR)/put_file.c		\
		  $(CLIENT_DIR)/noop.c			\
		  $(CLIENT_DIR)/usage.c			\
		  $(CLIENT_DIR)/connect_to_server.c	\
		  $(CLIENT_DIR)/get_reply.c		\
		  $(CLIENT_DIR)/send_request.c		\
		  $(CLIENT_DIR)/get_command.c		\
		  $(CLIENT_DIR)/get_info_client.c	\
		  $(CLIENT_DIR)/get_file.c		\
		  $(CLIENT_DIR)/local_cd.c		\
		  $(CLIENT_DIR)/local_ls.c		\
		  $(CLIENT_DIR)/get_signal.c		\
		  $(CLIENT_DIR)/local_pwd.c		\
		  $(CLIENT_DIR)/passive_mode.c		\
		  $(CLIENT_DIR)/list_dir.c

OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

SRC_MY_LS	= $(MY_LS_DIR)/main.c \
		  $(MY_LS_DIR)/ls_arg.c \
		  $(MY_LS_DIR)/ls_cut.c \
		  $(MY_LS_DIR)/ls_dir.c \
		  $(MY_LS_DIR)/ls_files.c \
		  $(MY_LS_DIR)/ls_get_options.c \
		  $(MY_LS_DIR)/ls_list_alpha.c \
		  $(MY_LS_DIR)/ls_list_linked.c \
		  $(MY_LS_DIR)/ls_list_time.c \
		  $(MY_LS_DIR)/ls_print.c \
		  $(MY_LS_DIR)/ls_str.c \
		  $(MY_LS_DIR)/ls_utils.c \
		  $(MY_LS_DIR)/my_ls.c \
		  $(MY_LS_DIR)/my_malloc.c \
		  $(MY_LS_DIR)/ls_perms.c \
		  $(MY_LS_DIR)/my_printf/my_printf.c \
		  $(MY_LS_DIR)/my_printf/calc_size.c \
		  $(MY_LS_DIR)/my_printf/print_int.c \
		  $(MY_LS_DIR)/my_printf/print_str.c \
		  $(MY_LS_DIR)/my_printf/print_large_hexa.c \
		  $(MY_LS_DIR)/my_printf/print_uint.c \
		  $(MY_LS_DIR)/my_printf/check.c \
		  $(MY_LS_DIR)/my_printf/print_all_str.c \
		  $(MY_LS_DIR)/my_printf/print_little_hexa.c \
		  $(MY_LS_DIR)/my_printf/save_chars_written.c \
		  $(MY_LS_DIR)/my_printf/init_struc.c \
		  $(MY_LS_DIR)/my_printf/print_binary.c \
		  $(MY_LS_DIR)/my_printf/print_octal.c \
		  $(MY_LS_DIR)/my_printf/stock_args.c \
		  $(MY_LS_DIR)/my_printf/print_char.c \
		  $(MY_LS_DIR)/my_printf/print_ptr.c \
		  $(MY_LS_DIR)/my_printf/utils.c

OBJ_MY_LS	= $(SRC_MY_LS:.c=.o)

INCLUDE_DIR	= -I ./include -I ./my_ls

CFLAGS		= -Wall -Wextra $(INCLUDE_DIR) -lpthread

CC		= gcc

RM		= rm -f

all:		$(my_ls_lib) $(server) $(client)

$(my_ls_lib):	$(OBJ_MY_LS)
		ar rcs $(my_ls_lib) $(OBJ_MY_LS)

$(server):	$(OBJ_SERVER) $(OBJ_COMMON)
		$(CC) $(CFLAGS) -o $(server) $(OBJ_SERVER) $(OBJ_COMMON) $(my_ls_lib)

$(client):	$(OBJ_CLIENT) $(OBJ_COMMON)
		$(CC) $(CFLAGS) -o $(client) $(OBJ_CLIENT) $(OBJ_COMMON) $(my_ls_lib)

clean:
		$(RM) $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_COMMON) $(OBJ_MY_LS)

fclean:		clean
		$(RM) $(client) $(server) $(my_ls_lib)

re:		fclean all

.PHONY:		all clean fclean re
