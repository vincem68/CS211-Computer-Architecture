#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char **argv)
{

FILE *folder;
char *name = argv[1];
//printf("%s\n", name);
folder = fopen(name, "r");

int length;
 fscanf(folder, "%d", &length);
 int power; int powerCheck = 1;

int **baseMatrix = malloc(length*sizeof(int *));
  for (int i = 0; i < length; ++i){
     baseMatrix[i] = malloc(length*sizeof(int));
  }  
int **finalMatrix = malloc(length*sizeof(int *));
  for (int i = 0; i < length; ++i){
     finalMatrix[i] = malloc(length*sizeof(int));
  }  
int **secondMatrix = malloc(length*sizeof(int *));
  for (int i = 0; i < length; ++i){
     secondMatrix[i] = malloc(length*sizeof(int));
  }  
for (int i = 0; i < length; i++){
  for (int j = 0; j < length; j++){
    fscanf(folder, "%d", &baseMatrix[i][j]);
    secondMatrix[i][j] = 0;
    finalMatrix[i][j] = 0;
  }
}  
fscanf(folder, "%d", &power);
//printf("power is %d\n", power);
fclose(folder);

if (power == 0){
  for (int a = 0; a < length; a++){
      for (int b = 0; b < length; b++){
         if (a == b){
            secondMatrix[a][b] = 1;
         } else {
         secondMatrix[a][b] = 0; 
         }
      }
   }
} else {
while (powerCheck <= power-1){
for (int i = 0; i < length; i++){
 
    for (int j = 0; j < length; j++){
  
        for (int k = 0; k < length; k++){
   
          if (powerCheck == 1){  
            secondMatrix[i][j] += baseMatrix[i][k] * baseMatrix[k][j];
      //      printf("second will be %d\n", secondMatrix[i][j]);
          }
          else {
            finalMatrix[i][j] += secondMatrix[i][k] * baseMatrix[k][j];
          }
        }
    
    }

}
if (powerCheck != 1){
  for (int r = 0; r < length; r++){
    for (int s = 0; s < length; s++){
      secondMatrix[r][s] = finalMatrix[r][s];
    //  printf("new second value is now %d\n", secondMatrix[r][s]);
      finalMatrix[r][s] = 0;
    }
  } 
}
powerCheck++;
}
} 
for (int p = 0; p < length; p++){
   for (int o = 0; o < length; o++){
     if (o == length-1){
       printf("%d\n", secondMatrix[p][o]);
     } 
     else { printf("%d ", secondMatrix[p][o]);}
    }
}
free(baseMatrix);
free(finalMatrix); 
    return EXIT_SUCCESS;
}

