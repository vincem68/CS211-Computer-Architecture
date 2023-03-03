#include <stdio.h>
#include <stdlib.h>


struct Node{
   int number;
   struct Node *left;
   struct Node *right;
};

struct Node *insert(struct Node *root, int digit);
struct Node *delete(struct Node *root, int digit);
void print(struct Node *root);
void search(struct Node *root, int digit);
void deleteAll(struct Node *root);

struct Node *root = NULL;
//int count = 0;

int main(int argc, char **argv)
{
//	root = NULL;
	int value = 0;
	char command = '\0';
	while (scanf(" %c", &command) != EOF){
		if (command == 'i' || command== 'd' || command == 's'){
			scanf("%d", &value);
		}
		if (command == 'i'){
			root = insert(root, value);
		}
		if (command == 's'){
			search(root, value);
		}
		if (command == 'p'){
			if (root != NULL){ //	int check = 0;
				print(root);
				printf("\n");
			} else {
				printf("\n");
			}
		}
		if (command == 'd'){
			root = delete(root, value);
		}
	}
	if (root != NULL){
		struct Node *temp = root;
		deleteAll(temp);
	}

    return EXIT_SUCCESS;
}

struct Node *insert(struct Node *root, int digit){
	struct Node *crnt = root; struct Node *prev = crnt;
	if (root == NULL){
		root = malloc(sizeof(struct Node));
		root->number = digit;
		root->left = NULL; root->right = NULL;
		printf("inserted\n");
	}
	else {
		while (crnt != NULL){
			if (crnt->number == digit){
				printf("not inserted\n");
				break;
			}
			else if (digit < crnt->number){
  				if (crnt->left == NULL){
					struct Node *newNode = malloc(sizeof(struct Node));
					newNode->left = NULL; newNode->right = NULL;
					newNode->number = digit;
					crnt->left = newNode;
					printf("inserted\n");
	//				count++;
					break;
				}
				prev = crnt; 
				crnt = crnt->left;
			}
			else {
				if (crnt->right == NULL){
				struct Node *newNode = malloc(sizeof(struct Node));
				newNode->left = NULL; newNode->right = NULL;
				newNode->number = digit; crnt->right = newNode;
				printf("inserted\n");
				break;
			}
				prev = crnt;
				crnt = crnt->right;
			}
		}
	}
	return root;
}

struct Node *delete(struct Node *root, int digit){

	if (root == NULL){
		printf("absent\n");
	}
	else {
		struct Node *crnt = root; struct Node *prev = crnt;
		while (crnt != NULL){
			if (crnt->number > digit){
				prev = crnt;
				crnt = crnt->left;
			}
			else if (crnt->number < digit){
				prev = crnt;
				crnt = crnt->right;
			}
			else {
				if (crnt->left == NULL && crnt->right == NULL){
					if (crnt == root){
						root = NULL;
						printf("deleted\n");
						return root;
					} else {
						if (prev->left == crnt){
							prev->left = NULL;
						} else if (prev->right == crnt){
							prev->right = NULL;
						}
						free(crnt);
						printf("deleted\n");
						return root;
					}
				}
				//this is if we have to delete a node with one child
				else if ((crnt->left != NULL && crnt->right == NULL) || (crnt->left == NULL && crnt->right != NULL)){
					if (crnt == root){
						//here we check if we delete root, we copy it's data from it's child and delete child
						if (root->left != NULL){
							struct Node *temp = root;
							root = root->left;
							free(temp);
							printf("deleted\n");
							return root;;
						}
						else if (root->right != NULL){
							struct Node *temp = root;
							root = root->right;
							free(temp);
							printf("deleted\n");
							return root;
						}
					}  
					if (crnt->left != NULL){
						if (prev->left == crnt){
							prev->left = crnt->left;
							free(crnt);
							printf("deleted\n");
							return root;
						}
						else if (prev->right == crnt){
							prev->right = crnt->left;
							free(crnt);
							printf("deleted\n");
							return root;
						}  
					}
					else if (crnt->right != NULL){
						if (prev->left == crnt){
							prev->left = crnt->right;
							free(crnt);
							printf("deleted\n");
							return root;
						} 
						else if (prev->right == crnt){
							prev->right = crnt->right;
							free(crnt);
							printf("deleted\n");
							return root;
						} 		
					}
				}
				else if (crnt->left != NULL && crnt->right != NULL){
					struct Node *temp = crnt->left; struct Node *prevTemp = crnt;
					if (temp->right == NULL){
						if (temp->left == NULL){
							crnt->number = temp->number;
							crnt->left = NULL;
							free(temp);
							printf("deleted\n");
							return root;
						}
						else {
							crnt->number = temp->number;
							crnt->left = temp->left;
							free(temp);
							printf("deleted\n");
							return root;
						}
					}
					while (temp->right != NULL){
						prevTemp = temp;
						temp = temp->right;
					}	
					crnt->number = temp->number;
					if (temp->left != NULL){
						prevTemp->right = temp->left;
					} else {
						prevTemp->right = NULL;
					}
					free(temp);
					printf("deleted\n");
					break;
  				}
			}
		}
		if (crnt == NULL){
			printf("absent\n");
		}
	}
	return root;
}


void search(struct Node *root, int digit){
	struct Node *crnt = root;
	while (crnt != NULL){
		if (crnt->number == digit){
			printf("present\n");
			break;
		}
		if (crnt->number < digit){
			crnt = crnt->right;
		}
		else {
			crnt = crnt->left;
		}	
	}
	if (crnt == NULL){
		printf("absent\n");
	}
}


void print(struct Node *root){// put if statements here 
	if (root == NULL){
		printf(" \n");
	}
	printf("(");
	if (root->left != NULL){
		print(root->left);
	}
        printf("%d", root->number);
	if (root->right != NULL){
		print(root->right);
	}

	printf(")");
}

void deleteAll(struct Node *root){
	if (root->left != NULL){
		deleteAll(root->left);
	}
	if (root->right != NULL){
		deleteAll(root->right);
	}
	if (root != NULL){
		free(root);
	}
}	
