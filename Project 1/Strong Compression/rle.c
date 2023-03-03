#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{

char *OGword = argv[1];
int length = strlen(OGword);
char *compression = (char *)malloc(sizeof(char)*(length+2));
 compression[0] = '\0';
int count = 1;
for (int i = 0; OGword[i] != '\0'; i++){

  if (isdigit(OGword[i])) {
    free(compression);
    printf("error\n");
    return EXIT_SUCCESS;

  } 
  if (OGword[i] == OGword[i+1] && OGword != '\0'){
     count++;
     
   }
  
   if ((OGword[i] != OGword[i+1])){/*null checking here*/ 
    int smallLength = 0; int temp = count;
    while (temp != 0){
      smallLength++;
      temp = temp/10;
    
    }
   char check = OGword[i];
   char *add = (char*)malloc(sizeof(char)*(smallLength+10));
   sprintf(add,"%c%d", check, count);
  int see = 0; int y = 0;
  while (compression[y] != '\0'){
     y++;
     see+=1;
   }
   if ((see+smallLength) > strlen(OGword)){
      free(add);
      printf("%s\n", OGword);
      return EXIT_SUCCESS;
   }  
   else {strcat(compression, add);}
   free(add);
   count = 1;
    if ((strlen(compression)) > strlen(OGword)){
      printf("%s\n", OGword);
      return EXIT_SUCCESS;
   }  
 
  }
}
    printf("%s\n", compression);
    free(compression);
    return EXIT_SUCCESS;

}
