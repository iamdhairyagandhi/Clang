#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

int remove_spaces(const char *source, char *result, int *num_spaces_removed){
   int i=0, j =0;
   int k = 0;
   int removed=0;
   int len_str=0;

   if(source==NULL){
	return FAILURE;
   }
   len_str=strlen(source); 
   if(len_str == 0)
       return FAILURE;
  j=len_str-1;
   while(source[i] == ' ' || source[i] == '\t'){
       i++;
       removed++;
   }
  
   while(source[j] == ' ' || source[j] == '\t'){
       j--;
       removed++;
   }
  
   while(i <= j){
       result[k] = source[i];
       i++;
       k++;
   }
  
   result[k] = '\0';
   if(num_spaces_removed){
	*num_spaces_removed=removed;
   }  
   return SUCCESS;
}


int center(const char *source, int width, char *result){
   int n;
   int i = 0, j = 0, k;
   int str_len=0;
   if(source == NULL)
       return FAILURE;
   str_len=strlen(source);

   if(str_len == 0 || width < str_len){
     return FAILURE;
   }
   n = (width - str_len)/2;
  
   for(k = 0; k < n; k++)
       result[k] = ' ';
  
   for(; source[i] != '\0'; i++, k++)
       result[k] = source[i];
  
   for(;j < n; j++, k++)
       result[k] = ' ';
  
   result[k] = '\0';
   return SUCCESS;
}
