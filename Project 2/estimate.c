#include <stdio.h>
#include <stdlib.h>


double **transpose(double **originalMatrix, double **newTranspose, int row, int col);

double **multiply(double **firstMatrix, int row1, int col1, double **secondMatrix, int col2, double **product);

double **inverse(double **originalMatrix, double **newInverse, int row, int col);

double *smallMultiply(double **matrix, double *array, double *product, int row, int col);



int main(int argc, char **argv)
{

	FILE *filePointer;
	char *fileName = argv[1];
	int rows = 0;
	int columns = 0;
	
	filePointer = fopen(fileName, "r");

	fscanf(filePointer, "%*[^\n]\n");
	fscanf(filePointer, "%d", &columns);
	fscanf(filePointer, "%d", &rows);
	columns += 1;
	//here we should store the file contents in a malloced array
	//look at first 2 numbers to determine how much size to malloc
		
	double **trainData = malloc(rows * sizeof(double *));  //this is X
	for (int i = 0; i < rows; ++i){
		trainData[i] = malloc(columns * sizeof(double));
	}

	//this is the transpose of the train data
	double **trainDataTranspose = malloc(columns * sizeof(double *)); // this is XT
	for (int j = 0; j < columns; ++j){
		trainDataTranspose[j] = malloc(rows * sizeof(double)); 
	}
	
	//this is the original pricing from the train data
	double *trainPrices = (double *)malloc(sizeof(double) * rows);   //this is Y
	int priceCount = 0;

	//this sets up our X and our Y
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < (columns+1); j++){   //idk if we need to fix this but keep an eye on it
			if (j == 0){
				trainData[i][j] = 1.000000;
			}
			else if (j == columns){
				fscanf(filePointer, "%lf", &trainPrices[priceCount]);		
				priceCount++;
			}
			else {
				fscanf(filePointer, "%lf", &trainData[i][j]);
			}
		}
	}
	
	trainDataTranspose = transpose(trainData, trainDataTranspose, rows, columns);
	
	double **firstProduct = malloc(columns * sizeof(double *));   //this is where XT * X is
	for (int i = 0; i < columns; ++i){
		firstProduct[i] = malloc(columns * sizeof(double));
	}

	firstProduct = multiply(trainDataTranspose, columns, rows, trainData, columns, firstProduct);
  
	double **xInverse = malloc(columns * sizeof(double *));  //this is our inverse
	for (int i = 0; i < columns; ++i){
		xInverse[i] = malloc(columns * sizeof(double));
	}

	xInverse = inverse(firstProduct, xInverse, columns, columns);
	
	double **secondProduct = malloc(columns * sizeof(double *));
	for (int i = 0; i < columns; ++i){
		secondProduct[i] = malloc(rows * sizeof(double));
	}	

	secondProduct = multiply(xInverse, columns, columns, trainDataTranspose, rows, secondProduct);


	double *W = (double *)malloc(sizeof(double) * columns);

	W = smallMultiply(secondProduct, trainPrices, W, columns, rows);

	//free everything
	free(trainPrices);
	for (int i = 0; i < columns; ++i){
		free(firstProduct[i]);
	}
	free(firstProduct);
	for(int i = 0; i < columns; ++i){
		free(xInverse[i]);
	}
	free(xInverse);
	for (int i = 0; i < columns; ++i){
		free(secondProduct[i]);
	}
	free(secondProduct);
	for (int i = 0; i < rows; ++i){
		free(trainData[i]);
	}
	free(trainData);
	for (int i = 0; i < columns; ++i){
		free(trainDataTranspose[i]);
	}
	free(trainDataTranspose);
	

	fclose(filePointer); 

	//this starts the data portion of the program
	FILE *filePointer2;
	char *fileName2 = argv[2];
	int columns2 = 0;
	int rows2 = 0;
	filePointer2 = fopen(fileName2, "r");
	fscanf(filePointer2, "%*[^\n]\n");
	fscanf(filePointer2, "%d", &columns2);		
	fscanf(filePointer2, "%d", &rows2);
	columns2 += 1;
	double **finalData = malloc(rows2 * sizeof(double *));
	for (int i = 0; i < rows2; ++i){
		finalData[i] = malloc(columns2 * sizeof(double));
	} 
	if (finalData == NULL){
		printf("yes");
	}	
	for (int x = 0; x < rows2; x++){
		for (int y = 0; y < columns2; y++){
			if (y == 0){
				finalData[x][y] = 1;
			} else {
				fscanf(filePointer2, "%lf", &finalData[x][y]);
			}
		}
	}

	double *finalPrices = (double *)malloc(sizeof(double) * rows2);

	finalPrices = smallMultiply(finalData, W, finalPrices, rows2, columns2);

	for (int i = 0; i < rows2; i++){
		printf("%.0f\n", finalPrices[i]);
	}

	free(finalPrices);
	free(W);
	for (int j = 0; j < rows2; ++j){
		free(finalData[j]);
	}
	free(finalData);
	
	fclose(filePointer2);

	return EXIT_SUCCESS;	
//	return EXIT_FAILURE;
}


double **transpose(double **originalMatrix, double **newTranspose, int row, int col){

	
	for (int i = 0; i < col; i++){
		for (int j = 0; j < row; j++){
			newTranspose[i][j] = originalMatrix[j][i];
		}
	}


	return newTranspose;


}


double **inverse(double **original, double **newInverse, int row, int col){

	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			if (i == j){
				newInverse[i][j] = 1;
			}
			else {
				newInverse[i][j] = 0;
			}
		}
	}

	double pivot1 = 0; double pivot2 = 0;
	for (int x = 0; x < row; x++){
		pivot1 = original[x][x];// printf("pivot1 is %lf\n", pivot1);
		for (int a = x; a < col; a++){
			if (pivot1 != 0){
				original[x][a] = original[x][a] / pivot1;
			}
		}
		for (int b = 0; b < col; b++){
			if (pivot1 != 0){
				newInverse[x][b] = newInverse[x][b] / pivot1;
			}
		}
		for (int y = x + 1; y < row; y++){
			pivot2 = original[y][x];
			for (int b = x; b < col; b++){
				original[y][b] = original[y][b] - (pivot2 * original[x][b]);
			}
			for (int c = 0; c < col; c++){
				newInverse[y][c] = newInverse[y][c] - (pivot2 * newInverse[x][c]);
			}
		
		}
	
	}

	for (int i = row-1; i >= 0; i--){
		for (int j = i - 1; j >= 0; j--){
			pivot1 = original[j][i];
			for (int k = col - 1; k >= 0; k--){
				original[j][k] = original[j][k] - (pivot1 * original[i][k]);
				newInverse[j][k] = newInverse[j][k] - (pivot1 * newInverse[i][k]);
			}
		}
	}				
	return newInverse;
}
double *smallMultiply(double **matrix, double *array, double *product, int row, int col){
	
	for (int j = 0; j < row; j++){
		product[j] = 0;
	}
	
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			product[i] += matrix[i][j] * array[j];
		}
	}
	
	return product;

}


double **multiply(double **firstMatrix, int row1, int col1,  double **secondMatrix, int col2, double **product){

	for (int x = 0; x < row1; x++){
		for (int y = 0; y < col2; y++){
			product[x][y] = 0;
		}
	}

	for (int i = 0; i < row1; i++){
		for (int j = 0; j < col2; j++){
			for (int k = 0; k < col1; k++){
				product[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}	


	return product;
}
