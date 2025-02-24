/*
** EPITECH PROJECT, 2022
** ezdrf
** File description:
** ezrf
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <limits.h>
#include <pwd.h>

#pragma once

typedef struct list {
   int fds;
   bool link;
   bool auth;
   bool pass;
   bool inter;
   char *str;
   struct list *next;
} list;

void add_link(int i, list **ls);
void init(list **lst);
void set_struct(int port, struct sockaddr_in *ad);
int create_socket(int port);
void print(list **lst);
int readd(int n_fds, char **buffer);
int check_cmd(char *str);
int valid_cmd(char *str, char *c);
char *get_path();
void PWD(int fd, list *tmp);
void CDUP(int fd, list *tmp);
void DELE(int fd, char *str);
void NOOP(int fd);
void QUIT(list *lst);
void CWD(int fd, char *str, list *tmp);
void HELP(int fd);
void handle_com(char *str, list *tmp);
fd_set accpt(int *activity, int max, int new_socket, char *buffer, char *message, int addrlen, fd_set readfds, list **lst);
int enter_dir(char **curr_dir, char **av);
int core(int wx, char **av);





