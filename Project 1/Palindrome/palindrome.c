#include <stdlib.h>
#include <string.h>


 int main(int argc, char **argv){ 
  char *number = argv[1];
   if (atoi(number) == 0){
     printf(" ");
     return EXIT_SUCCESS;
   }
   int numberLength = strlen(number);
 //  printf("%d", numberLength);
   int numberPlace = 0;
   int count = 0;
   int space = atoi(number);
   while (count < 3 && space != 0){
      space = space/10;
      numberPlace++;
      count++;
  }
  
  int check = numberPlace-1;
   if (space >  0){
     for (int i = 0; i < space; i++){
       printf("M");
     }
   }
 /*  int romanNumberLength = strlen(romanNumber);*/  
   for (int i = (numberLength-1-check); i <= numberLength-1; i++){     
        
    if (numberPlace == 1){
       
      if (number[i] == '5'){
      //  strcat(romanNumber, "V");
            printf("V");    
      }
      else if (number[i] == '4'){
   //    strcat(romanNumber, "VI");
         printf("IV");
      }
      else if (number[i] < '4') {
       /*  char *r = (char *)malloc(5);r[5] = '\0';*/
     //   char r[5];
         for (int x = 0; x < (number[i]-'0'); x++){
     //       r[x] = 'I';
             printf("I");
         }
   //    strcat(romanNumber, r);
      }
      else if (number[i] == '9'){
          printf("IX");
     //      strcat(romanNumber, "XI");
      }
      else if (number[i] > '5' && number[i] < '9'){ 
         //    char r[5];
          printf("V");
          int x = 0;   
     //     printf("%s and %x\n", r, x);
          while (x < ((number[i]-'0')-5)){
       //     r[x] = 'I';
           printf("I");
            x++;
          } 
       
        } 
      }
    

    else if (numberPlace == 2){
       if (number[i] == '5'){
       //  strcat(romanNumber, "L");
          printf("L");      
      }
      else if (number[i] == '4'){
     //     strcat(romanNumber, "LX");
          printf("XL");
      }
      else if (number[i] < '4') {
         //      char o[5];
          int x = 0; 
          while (x < (number[i]-'0')){
     //       o[x] = 'X';
            printf("X");
            x++;
          } 
         
   //    strcat(romanNumber, o);
         
      }
      else if (number[i] == '9'){
       //   strcat(romanNumber, "CX");
          printf("XC");
      }
      else if (number[i] > '5' && number[i] < '9'){
         //      char o[5];
          printf("L");
          int x = 0;
          while (x < ((number[i]-'0')-5)){
    //        o[x] = 'X';
            printf("X");
            x++;
          } 
  //      o[x] = 'L'; 
    //   strcat(romanNumber, o);
        }
    } 
 
    else if (numberPlace == 3){
      
      if (number[i] == '5'){
     //   strcat(romanNumber, "D");
          printf("D");         
      }
      else if (number[i] == '4'){
      //  strcat(romanNumber, "DC");
         printf("CD");
      }
      else if (number[i] < '4') {
         //         char m[5];
          int x = 0;
          while (x < (number[i]-'0')){
      //      m[x] = 'C';
            printf("C");
            x++;
          } 
        
    //   strcat(romanNumber, m);
       
      }
      else if (number[i] == '9'){
      //  strcat(romanNumber, "MC");
           printf("CM");
      }
      else if (number[i] > '5' && number[i] < '9'){
          printf("D");
  //         char m[5];
          int x = 0;
          while (x < ((number[i]-'0')-5)){
     //       m[x] = 'C';
            printf("C");
            x++;
          } 
       
      } 
       
    
    }
   
      else { break; }   
      numberPlace--;
    }
 
   return EXIT_SUCCESS;


}

