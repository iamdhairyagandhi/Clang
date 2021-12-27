/* 117119190 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "command.h"
#include "executor.h"
/*static void print_tree(struct tree *t);*/

static int execute_aux(struct tree *t, int p_input_fd, int p_output_fd)
{

   if (t->conjunction == NONE)
   {
      /*
      int *pid_ret;
      int val, in, out;
      if (strcmp(t->argv[0], "exit") == 0)
      {
         exit(0);
      }
      else if (strcmp(t->argv[0], "cd") == 0)
      {
         if (chdir(t->argv[1]) != 0)
         {
            printf("Cannot change to directory %s\n", t->argv[1]);
            *pid_ret = -1;
            return *pid_ret;
         }
         else
         {
            *pid_ret = 0;
            return *pid_ret;
         }
      }
      else
      {
         val = fork();
         if (val == 0)
         {

            if (t->input != NULL)
            {
               if ((in = open(t->input, O_RDONLY)) < 0)
               {
                  *pid_ret = -1;
                  err(EX_OSERR, "File opening (read) failed");
                  return *pid_ret;
               }

               if (dup2(in, p_input_fd) < 0)
               {
                  *pid_ret = -1;
                  err(EX_OSERR, "dup2 (read) failed");
                  return *pid_ret;
               }
               if (close(in) < 0)
               {
                  *pid_ret = -1;
                  err(EX_OSERR, "close error");
                  return *pid_ret;
               }
            }

            if (t->output != NULL)
            {
               if ((out = open(t->output, O_CREAT | O_WRONLY | O_TRUNC, 0664)) < 0)
               {
                  *pid_ret = -1;
                  err(EX_OSERR, "File opening (write) failed");
                  return -1;
               }
               if (dup2(out, p_output_fd) < 0)
               {
                  *pid_ret = -1;
                  err(EX_OSERR, "dup2 (write) failed");
                  return -1;
               }
               if (close(out) < 0)
               {
                  *pid_ret = -1;
                  err(EX_OSERR, "close error");
                  return -1;
               }
            }

            if (execvp(t->argv[0], t->argv) == -1)
            {
               *pid_ret = -1;

               err(EX_OSERR, "Failed to execute %s\n", t->argv[0]);
               return -1;
            }
         }
         else
         {
            wait(pid_ret);
         }
      }
      return *pid_ret;
      */
      int flag;
      int cd_var = 0;
      int file_disc = 0;
      pid_t pid;

      if (strcmp(t->argv[0], "cd") == 0)
      {
         if (t->argv[1] != NULL)
         {
            cd_var = chdir(t->argv[1]);
            if (cd_var != 0)
            {
               perror(" cd error");
               return -1;
            }
         }
         else
         {
            chdir(getenv("HOME"));
         }
      }
      else if (strcmp(t->argv[0], "exit") == 0)
      {
         exit(0);
      }
      else
      {
         if ((pid = fork()) < 0)
         { /* Forking */
            err(EX_OSERR, "fork error");
         }
         if (pid != 0)
         {
            /* Parent code */
            wait(&flag);
            return (flag);
         }
         else
         {

            if (t->input != NULL)
            {
               file_disc = open(t->input, O_RDONLY);
               if (file_disc < 0)
               {
                  perror("open failed");
                  return -1;
               }
               if (dup2(file_disc, STDIN_FILENO) < 0)
               { /* stdin now associated with the file */
                  err(EX_OSERR, "dup2 error");
                  return -1;
               }
               if (close(file_disc) < 0)
               { /* We need it otherwise resource leak */
                  err(EX_OSERR, "close error");
                  return -1;
               }
            }
            if (t->output != NULL)
            {
               file_disc = open(t->output, O_WRONLY | O_TRUNC | O_CREAT, 0664);
               if (file_disc < 0)
               {
                  perror("open failed");
                  return -1;
               }
               if (dup2(file_disc, STDOUT_FILENO) < 0)
               {
                  err(EX_OSERR, "dup2 error");
                  return -1;
               }
               if (close(file_disc) < 0)
               {
                  err(EX_OSERR, "close error");
                  return -1;
               }
            }
            if (execvp(t->argv[0], t->argv) != 0)
            {
               fprintf(stderr, "Failed to execute %s\n", t->argv[0]);
               fflush(stdout);
               exit(EX_OSERR);
            }
         }
      }
   }

   else if (t->conjunction == PIPE)
   {
      pid_t child;
      int fd_pipe[2];
      int fd_in = 1;
      int fd_out = -2;
      if (t->right->input != NULL)
      {

         printf("Ambiguous input redirect.\n");
         return -1;
      }

      if (t->left->output != NULL)
      {

         printf("Ambiguous output redirect.\n");
         return -1;
      }

      if (t->input != NULL)
      {

         if ((fd_in = open(t->input, O_RDONLY)) < 0)
         {

            err(EX_OSERR, "File (input) opening failed");
         }
      }

      if (t->output != NULL)
      {
         if ((fd_out = open(t->output, O_CREAT | O_WRONLY | O_TRUNC, 0664) < 0))
         {
            err(EX_OSERR, "File (output) opening failed");
         }
      }

      if (pipe(fd_pipe) < 0)
      {
         err(EX_OSERR, "pipe error");
      }

      if ((child = fork()) < 0)
      {
         err(EX_OSERR, "fork error");
      }

      if (child)
      {

         if (close(fd_pipe[1]) < 0)
         {
            err(EX_OSERR, "Closing pipe failed");
         }

         if (dup2(fd_pipe[0], STDIN_FILENO) < 0)
         {
            err(EX_OSERR, "dup2 failed");
         }

         execute_aux(t->right, fd_pipe[0], fd_out);

         if (close(fd_pipe[0]) < 0)
         {
            err(EX_OSERR, "Closing pipe failed");
         }

         wait(NULL);
      }
      else
      {

         if (close(fd_pipe[0]) < 0)
         {
            err(EX_OSERR, "Closing pipe failed");
         }

         if (dup2(fd_pipe[1], STDOUT_FILENO) < 0)
         {
            err(EX_OSERR, "dup2 failed");
         }

         execute_aux(t->left, fd_in, fd_pipe[1]);

         if (close(fd_pipe[1]) < 0)
         {

            err(EX_OSERR, "Closing pipe failed");
         }
      }
   }
   else if (t->conjunction == AND)
   {

      if (execute_aux(t->left, p_input_fd, p_output_fd) == 0)
      {
         return execute_aux(t->right, p_input_fd, p_output_fd);
      }
      else
      {
         return -1;
      }
   }
   else if (t->conjunction == SUBSHELL)
   {
      int sub_in = p_input_fd;
      int sub_out = p_output_fd;
      int subshell_stat = 0;
      int fork_value = 0;

      if (t->input != NULL)
      {
         sub_in = open(t->input, O_RDONLY);
         if (sub_in < 0)
         {

            err(EX_OSERR, "Input Open  error");
            return -1;
         }
      }
      if (t->output != NULL)
      {
         sub_out = open(t->output, O_WRONLY | O_TRUNC | O_CREAT, 0664);
         if (sub_out < 0)
         {
            err(EX_OSERR, "Output");
            return -1;
         }
      }
      fork_value = fork();
      if (fork_value < 0)
      {
         err(EX_OSERR, "fork error");
      }

      if (fork_value != 0)
      {
         wait(NULL);
      }
      else
      {
         subshell_stat = execute_aux(t->left, sub_in, sub_out);
         exit(subshell_stat);
      }
   }
   return 0;
}
int execute(struct tree *t)
{
   return execute_aux(t, STDIN_FILENO, STDOUT_FILENO);
}
/*static void print_tree(struct tree *t)
{
   if (t != NULL)
   {
      print_tree(t->left);

      if (t->conjunction == NONE)
      {
         printf("NONE: %s, ", t->argv[0]);
      }
      else
      {
         printf("%s, ", conj[t->conjunction]);
      }
      printf("IR: %s, ", t->input);
      printf("OR: %s\n", t->output);

      print_tree(t->right);
   }
}*/
