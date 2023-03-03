#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
 int number;
 struct Node *next;
};

struct Node *front = NULL;

struct Node *insert(struct Node *front, int digit);
struct Node *delete(struct Node *front, int digit);
int count = 0;
int main(int argc, char **argv)
{


//front->next = NULL;
int value= 0;
char c = '\0';
//int count = 0;
 struct Node *link = malloc(sizeof(struct Node));
 while (scanf(" %c %d", &c, &value) != EOF){  
    if (c == 'i'){
      front = insert(front, value);
    }
    if (c == 'd'){
      front = delete(front, value);
       if (count > 0){
       }
    }
    link = front;
      if (count == 0){
      printf("%d :\n", count);
      } else if (count > 0){
        printf("%d : ", count);
      }
    int see = 1;
    while (link != NULL){
      if (see == count){
         printf("%d\n", link->number);
      }
      else {
      printf("%d ", link->number);
      }
      link = link->next;
      see++;
   }
}
struct Node *crnt = front; struct Node *prev = crnt;
while (crnt != NULL){
	prev = crnt;
        crnt = crnt->next;
	free(prev);
}
 free(link);

    return EXIT_SUCCESS;
}

struct Node *insert(struct Node *front, int digit){
  if (front == NULL){
   front = malloc(sizeof(struct Node));
   front->number = digit;
   front->next = NULL;
   count++;
  }
  else {
  //  printf("insert part 2\n");
     // = malloc(sizeof(struct Node));
    struct Node *crnt = front;  
    struct Node *prev = crnt;
        while (crnt != NULL){
        	if (crnt->number == digit){
           		break;
        	}
 
        	if (crnt->number > digit){
           		if (crnt == front){
              			struct Node *newNode = malloc(sizeof(struct Node));
              			newNode->number = front->number;
				front->number = digit;
             			newNode->next = front->next;
              			front->next = newNode;
				count++;
              		break;
           		} else {
           			struct Node *newNode = malloc(sizeof(struct Node));
           			newNode->number = digit;
           			newNode->next = crnt;
           			prev->next = newNode; 
				count++;
           			break;
           		}
        	}	
        	prev = crnt;
		crnt = crnt->next; 
       	}

	if (crnt == NULL){
    		struct Node *newNode = malloc(sizeof(struct Node));
    		newNode->number = digit;
		newNode->next = NULL;
		prev->next = newNode;
		count++;
      //          printf("last was inserted\n");
	}

	}
	return front;
}


struct Node *delete(struct Node *front, int digit){
  
    struct Node *crnt = front; struct Node *prev = crnt;//malloc(sizeof(struct Node));
    while (crnt != NULL){
      if (digit < crnt->number){
         break;
      }
      if (digit == crnt->number){
        if (crnt == front){
          if (front->next == NULL){
 		front = NULL;
		count--;
		break;
	  } else {
        // 	 front->number = front->next->number;
		 struct Node *temp = front;//->next; //front->next->next;
	 	 front = front->next;
 		 free(temp);
                 count--;
                 break;
		}
        } else {
          prev->next = crnt->next;
        }
      free(crnt); 
      count--; 
      break;
    }
    prev = crnt; crnt = crnt->next;
    }
return front;
}

