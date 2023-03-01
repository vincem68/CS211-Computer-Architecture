#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Gate{
	char kind[12];
	int size;
	int *param;
	int *output;
	struct Gate *next;
}; 
struct Gate *headGate = NULL;

struct TempNode{
	char variable[17];
	struct TempNode *next;
};
struct TempNode *front = NULL;

int place(struct TempNode *front, char *target);

void deleteAll(struct TempNode *front);

void deleteAllGates(struct Gate *headGate);


int main(int argc, char **argv)
{

	FILE *ptr;
	char hold[17];
	int length = 0;	
	char *name = argv[1];	
	struct TempNode *crnt = NULL;
	struct Gate *crntGate = NULL;
	int inputs = 0;
	int outputs = 0;
	ptr = fopen(name, "r");

	while (fscanf(ptr, " %16s", hold) != EOF){

		if (strcmp(hold, "INPUT") == 0 || strcmp(hold,"OUTPUT") == 0){
			
			int x = 0;
			fscanf(ptr, "%d", &x);
			if (strcmp(hold, "INPUT") == 0){
				inputs = x;
			} else { outputs = x;}
			
			for (int i = 0; i < x; i++){
				if (front == NULL){
					front = malloc(sizeof(struct TempNode));
					fscanf(ptr, " %16s", hold);
					strcpy(front->variable, hold);
					front->next = NULL;
					crnt = front;
				}
				else {
					struct TempNode *node = malloc(sizeof(struct TempNode));
					fscanf(ptr, " %16s", hold);
					strcpy(node->variable, hold);
					node->next = NULL;
					length++;
					crnt->next = node;
					crnt = node;
				} 
			}
		}	

		
		else if (strcmp(hold, "AND") == 0 || strcmp(hold, "OR") == 0 || strcmp(hold, "NOR") == 0 || strcmp(hold, "NAND") == 0 || strcmp(hold, "NOT") == 0 || strcmp(hold, "PASS") == 0 || strcmp(hold, "DECODER") == 0 || 
                        strcmp(hold, "XOR") == 0 || strcmp(hold, "MULTIPLEXER") == 0){
			if (headGate == NULL){
				headGate = malloc(sizeof(struct Gate));
				strcpy(headGate->kind, hold);
				headGate->next = NULL;
				crntGate = headGate;
			}
			else {
				struct Gate *newGate = malloc(sizeof(struct Gate));
				strcpy(newGate->kind, hold);
				newGate->next = NULL;
				crntGate->next = newGate;
				crntGate = newGate;
			}
			
			if (strcmp(hold, "AND") == 0 || strcmp(hold, "OR") == 0 || strcmp(hold, "NOR") == 0 || strcmp(hold, "NAND") == 0 ||
                          strcmp(hold, "XOR") == 0){
				char *first = (char *)malloc(sizeof(char)*17); char *second = (char *)malloc(sizeof(char)*17);
				crntGate->size = 2;
				fscanf(ptr, " %16s", first);
				int index1 = 0;
				if (strcmp(first, "1") == 0){
					index1 = -1;
				} 
				else if (strcmp(first, "0") == 0){
					index1 = -2;
				} else { index1 = place(front, first);}
				fscanf(ptr, " %16s", second);
				int index2 = 0;
				if (strcmp(second, "1") == 0){
					index2 = -1;
				} 
				else if (strcmp(second, "0") == 0){
					index2 = -2;
				} else { index2 = place(front, second);}
				free(first); free(second);
				crntGate->param = (int *)malloc(sizeof(int)*2);
				crntGate->param[0] = index1; crntGate->param[1] = index2;
				crntGate->output = (int *)malloc(sizeof(int)*1);
				fscanf(ptr, " %16s", hold);
				int dup = place(front, hold);
				if (dup == -1){
					struct TempNode *node = malloc(sizeof(struct TempNode));
					strcpy(node->variable, hold);
					node->next = NULL;
					length++; crntGate->output[0] = length; crnt->next = node; crnt = node;
				}
				else { crntGate->output[0] = dup; }
			} 

			else if (strcmp(hold, "NOT") == 0 || strcmp(hold, "PASS") == 0){  //we had separate pointers here before
				crntGate->size = 1;
				crntGate->param = (int *)malloc(sizeof(int)*1);
				crntGate->output = (int *)malloc(sizeof(int)*1);
				fscanf(ptr, " %16s", hold);
				if (strcmp(hold, "1") == 0){
					crntGate->param[0] = -1;
				} 
				else if (strcmp(hold, "0") == 0){
					crntGate->param[0] = -2;
				} else { crntGate->param[0] = place(front, hold);}
				fscanf(ptr, " %16s", hold);
				int dup = place(front, hold);
				if (dup == -1){
					struct TempNode *node = malloc(sizeof(struct TempNode));
					strcpy(node->variable, hold);
					node->next = NULL;
					crnt->next = node; crnt = node;
					length++; 
					crntGate->output[0] = length;
				} else {
				crntGate->output[0] = dup;
				}
			}
			
			else if (strcmp(hold, "DECODER") == 0){
				int num = 0;	
				fscanf(ptr, "%d", &num); 
				crntGate->size = num;
				crntGate->param = (int *)malloc(sizeof(int) * (crntGate->size));
				for (int i = 0; i < crntGate->size; i++){
					char *check = (char *)malloc(sizeof(char) * 17);
					fscanf(ptr, " %16s", check);
					if (strcmp(check, "1") == 0){
						crntGate->param[i] = -1;
					} 
					else if (strcmp(check, "0") == 0){
						crntGate->param[i] = -2;
					}
					else { crntGate->param[i] = place(front, check); }
					free(check);
				}
				int out = 0;
				for (int j = 0; j < crntGate->size; j++){
					if (out == 0){
						out = 2;
					}
					else { out *= 2; }
				}
				crntGate->output = (int *)malloc(sizeof(int) * out);
				for (int x = 0; x < out; x++){
					fscanf(ptr, " %16s", hold);
					int dup = place(front, hold);
					if (dup == -1){
						struct TempNode *node = malloc(sizeof(struct TempNode));
						strcpy(node->variable, hold);
						node->next = NULL;
						crnt->next = node;
						crnt = node;
						length++;
						crntGate->output[x] = length;
					} else { crntGate->output[x] = dup; }
				}
			}

			else if (strcmp(hold, "MULTIPLEXER") == 0){
				int num = 0;
				fscanf(ptr, "%d", &num);
				crntGate->size = num;
				int in = 0;
				for (int j = 0; j < crntGate->size; j++){
					if (in == 0){
						in = 2;
					}
					else { in *= 2; }
				}
				crntGate->param = (int *)malloc(sizeof(int) * ((crntGate->size)+in));
				for (int i = 0; i < ((crntGate->size)+in); i++){     //here we put both inputs in, however regular inputs are at the end 
					char *check = (char *)malloc(sizeof(char) * 17);
					fscanf(ptr, " %16s", check);
					if (strcmp(check, "0") == 0){
						crntGate->param[i] = -2;
					} 
					else if (strcmp(check, "1") == 0){
						crntGate->param[i] = -1;
					}
					else { crntGate->param[i] = place(front, check); }
					free(check);
				}
				crntGate->output = (int *)malloc(sizeof(int)*1);
				fscanf(ptr, " %16s", hold);
				int dup = place(front, hold);
				if (dup == -1){
					struct TempNode *node = malloc(sizeof(struct TempNode));
					strcpy(node->variable, hold);
					node->next = NULL;	
					crnt->next = node;
					crnt = node;
					length++;
					crntGate->output[0] = length;
				} else { crntGate->output[0] = dup; }
			}
				
		}
		 
	}
	fclose(ptr);
	//this array represents a fast way to get out values, filled with 1s and 0s
	int *circuit = (int *)malloc(sizeof(int)*(length+1));
	int *prevValues = (int *)malloc(sizeof(int) * inputs);
	for (int i = 0; i < length; i++){
		circuit[i] = 0;
	}
        for (int i = 0; i < inputs; i++){
		prevValues[i] = 0;
	}
	//this tells us how many possible combos we'll have, need this to genrate rows
	int combos = 0;
	for (int j = 0; j < inputs; j++){
		if (combos == 0){
			combos = 2;
		}
		else { combos *= 2;}
	}
	crntGate = headGate;
	int sum = inputs + outputs;
	int counter = 1;
	//this is where we execute the circuit
	for (int i = 0; i < combos; i++){
		
		if (i != 0){
			for (int b = inputs-1; b >= 0; b--){
				if (counter == 1){
					if (prevValues[b] == 0){
						circuit[b] = 1;
						prevValues[b] = 1;
					}
					else if (prevValues[b] == 1){
						circuit[b] = 0;
						prevValues[b] = 0;
					}
				}	
				else {
					if ((i % counter == 0)){
						if (prevValues[b] == 0){
							circuit[b] = 1;
							prevValues[b] = 1;
						}
						else if (prevValues[b] == 1){
							circuit[b] = 0;
							prevValues[b] = 0;
						}
					}
					else { circuit[b] = prevValues[b]; }
				}
				counter *= 2;
			}
			counter = 1;
		}
		while (crntGate != NULL){
			if (strcmp(crntGate->kind, "AND") == 0){	
				if (crntGate->param[0] < 0 || crntGate->param[1] < 0){
					if (crntGate->param[0] == -1 && crntGate->param[1] == -1){
						circuit[crntGate->output[0]] = 1;
					}
					else if (crntGate->param[0] >= 0 && crntGate->param[1] < 0){
						if (crntGate->param[1] == -1 && circuit[crntGate->param[0]] == 1){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
					else if (crntGate->param[1] >= 0 && crntGate->param[0] < 0){
						if (crntGate->param[0] == -1 && circuit[crntGate->param[1]] == 1){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
				//	else { circuit[crntGate->output[0]] = 0; }
				}
				else {
					if (circuit[crntGate->param[0]] == 1 && circuit[crntGate->param[1]] == 1){
						circuit[crntGate->output[0]] = 1;
					}
					else { circuit[crntGate->output[0]] = 0; }
				}
			}
			else if (strcmp(crntGate->kind, "OR") == 0){
				if (crntGate->param[0] < 0 || crntGate->param[1] < 0){
					if (crntGate->param[0] == -1 || crntGate->param[1] == -1){
						circuit[crntGate->output[0]] = 1;
					}
					else if (crntGate->param[0] >= 0 && crntGate->param[1] < 0){
						if (crntGate->param[1] == -2 && circuit[crntGate->param[0]] == 1){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
					else if (crntGate->param[1] >= 0 && crntGate->param[0] < 0){
						if (crntGate->param[0] == -2 && circuit[crntGate->param[1]] == 1){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					} 
				//	else { circuit[crntGate->output[0]] = 0; }
				}	
				else {
					if (circuit[crntGate->param[0]] == 0 && circuit[crntGate->param[1]] == 0){    //remember that these else ones were first
						circuit[crntGate->output[0]] = 0;
					} else { circuit[crntGate->output[0]] = 1; }
				}
			}
			else if (strcmp(crntGate->kind, "NAND") == 0){
				if (crntGate->param[0] < 0 || crntGate->param[1] < 0){
					if (crntGate->param[0] == -2 || crntGate->param[1] == -2){
						circuit[crntGate->output[0]] = 1;
					}
					else if (crntGate->param[0] >= 0 && crntGate->param[1] < 0){
						if (crntGate->param[1] == -1 && circuit[crntGate->param[0]] == 0){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
					else if (crntGate->param[1] >= 0 && crntGate->param[0] < 0){
						if (crntGate->param[0] == -1 && circuit[crntGate->param[1]] == 0){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
			//		else { circuit[crntGate->output[0]] = 0; }
				}
				else {
					if (circuit[crntGate->param[0]] == 1 && circuit[crntGate->param[1]] == 1){
						circuit[crntGate->output[0]] = 0;
					} else { circuit[crntGate->output[0]] = 1; }
				}
			}
			else if (strcmp(crntGate->kind, "NOR") == 0){
				if (crntGate->param[0] < 0 || crntGate->param[1] < 0){
					if (crntGate->param[0] == -2 && crntGate->param[1] == -2){
						circuit[crntGate->output[0]] = 1;
					}
					else if (crntGate->param[0] >= 0 && crntGate->param[1] < 0){
						if (crntGate->param[1] == -2 && circuit[crntGate->param[0]] == 0){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
					else if (crntGate->param[1] >= 0 && crntGate->param[0] < 0){
						if (crntGate->param[0] == -2 && circuit[crntGate->param[1]] == 0){
							circuit[crntGate->output[0]] = 1;
						} else { circuit[crntGate->output[0]] = 0; }
					}
			//		else { circuit[crntGate->output[0]] = 0; }
				}
				else {
					if (circuit[crntGate->param[0]] == 0 && circuit[crntGate->param[1]] == 0){
						circuit[crntGate->output[0]] = 1;
					} else { circuit[crntGate->output[0]] = 0; }
				}
			}
			else if (strcmp(crntGate->kind, "XOR") == 0){
				if (crntGate->param[0] < 0 || crntGate->param[1] < 0){
					if ((crntGate->param[0] == -1 && crntGate->param[1] == -2) || (crntGate->param[0] == -2 && crntGate->param[1] == -1)){
						circuit[crntGate->output[0]] = 1;
					}
					else if (crntGate->param[0] >= 0 && crntGate->param[1] < 0){
						if (crntGate->param[1] == -2 && circuit[crntGate->param[0]] == 1){
							circuit[crntGate->output[0]] = 1;
						}
						else if (crntGate->param[1] == -1 && circuit[crntGate->param[0]] == 0){
							circuit[crntGate->output[0]] = 1;
						}
						else { circuit[crntGate->output[0]] = 0; }
					}
					else if (crntGate->param[1] >= 0 && crntGate->param[0] < 0){
						if (crntGate->param[0] == -2 && circuit[crntGate->param[1]] == 1){
							circuit[crntGate->output[0]] = 1;
						}
						else if (crntGate->param[0] == -1 && circuit[crntGate->param[1]] == 0){
							circuit[crntGate->output[0]] = 1;
						}
						else { circuit[crntGate->output[0]] = 0; }
					}
				}
				else {
					if (circuit[crntGate->param[0]] != circuit[crntGate->param[1]]){
						circuit[crntGate->output[0]] = 1;
					} else { circuit[crntGate->output[0]] = 0; }
				}
			}
			else if (strcmp(crntGate->kind, "NOT") == 0){
				if (crntGate->param[0] < 0){
					if (crntGate->param[0] == -1){
						circuit[crntGate->output[0]] = 0;
					} else { circuit[crntGate->output[0]] = 1; }
				} 
				else {
					if (circuit[crntGate->param[0]] == 1){
						circuit[crntGate->output[0]] = 0;
					} else { circuit[crntGate->output[0]] = 1; }
				}
			}
			else if (strcmp(crntGate->kind, "PASS") == 0){
				if (crntGate->param[0] < 0){
					if (crntGate->param[0] == -1){
						circuit[crntGate->output[0]] = 1;
					} else { circuit[crntGate->output[0]] = 0; }
				}
				else {
					if (circuit[crntGate->param[0]] == 1){
						circuit[crntGate->output[0]] = 1;
					} else { circuit[crntGate->output[0]] = 0; }
				}
			}
			else if (strcmp(crntGate->kind, "DECODER") == 0){
				int total = 0; int cap = 1; int sub = 1;
				
				for (int i = 0; i < crntGate->size; i++){
					cap *= 2;
				}
				for (int c = (crntGate->size)-1; c >= 0; c--){
					if (crntGate->param[c] < 0){
						if (crntGate->param[c] == -1){
							if (c == (crntGate->size)-1){
								total = 1;
							} else { total += sub; }
						}
					}
					else {
						if (circuit[crntGate->param[c]] == 1){
							if (c == (crntGate->size)-1){
								total = 1;
							}  
							else { total += sub; }
						}
					}
					sub *= 2;
				}
				for (int d = 0; d < cap; d++){
					if (total == d){
						circuit[crntGate->output[d]] = 1;
					} else { circuit[crntGate->output[d]] = 0; }
				}				
				
			}
			else if (strcmp(crntGate->kind, "MULTIPLEXER") == 0){
				int total = 0; int cap = 1; int sub = 1;
				
				for (int i = 0; i < crntGate->size; i++){
					cap *= 2;
				}
				for (int c = ((crntGate->size)+cap)-1; c >= cap; c--){
					if (circuit[crntGate->param[c]] == 1){
						if (c == (crntGate->size)-1){
							total = 1;
						}  
						else { total += sub; }
					}
					sub *= 2;
				}
				for (int d = 0; d < cap; d++){
					if (total == d){
						if (crntGate->param[d] == -1){
							circuit[crntGate->output[0]] = 1;
						} 
						else if (crntGate->param[d] == -2){
							circuit[crntGate->output[0]] = 0;
						}
						else { circuit[crntGate->output[0]] = circuit[crntGate->param[d]]; }
					}
				}
			}
			crntGate = crntGate->next;
	
		}
		crntGate = headGate;

		for (int a = 0; a < sum; a++){
			if (a == inputs){
				printf("| ");
			}
			if (a == sum - 1){
				printf("%d\n", circuit[a]);
			} else { printf("%d ", circuit[a]); }
		}
		for (int i = 0; i < length; i++){
				circuit[i] = 0;
		}
	}		

	free(prevValues);
	free(circuit);
	deleteAllGates(headGate);	
	deleteAll(front); 

    return EXIT_SUCCESS;
}

void deleteAll(struct TempNode *crnt){
	
	struct TempNode *prev = NULL;
	while (crnt != NULL){
		prev = crnt; 
		crnt = crnt->next;
		free(prev);
	}
}


void deleteAllGates(struct Gate *crntGate){
	struct Gate *prev = NULL;
	while (crntGate != NULL){
		free(crntGate->param); free(crntGate->output);
		prev = crntGate;
		crntGate = crntGate->next;
		free(prev);
	}
}
		


int place(struct TempNode *front, char *target){

	struct TempNode *point = front;
	int index = 0;
	while (point != NULL){
		if (strcmp(point->variable, target) == 0){
			return index;
		}
		point = point->next;
		index++;
	}

	return -1;

}
