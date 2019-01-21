#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

class MatrixOperation{
private:

    // The matrix is a pointer to a pointer //

    float** matrix;
    float*  array;
    float*  solution;
    float x;

    // m = line , n = colum //

    int m,n;

    // trying to figure it out what should i do with this //

    //int k;


public:

    // Our Contructor --> MatrixOperation() //
    // This constructor just alow us to create a matrix and a array, like Ax = b or Ax = 0//

    MatrixOperation( int _m, int _n ){

        printf("First Type of constructor\n");

        m = _m; n = _n;

        printf("--> The constructor has been created!!\n");

        alocMatrix();
        alocArray();
        setMatrix();
        setArray();
        printMatrixArray();


        progressiveElimination();
        regressiveSubstitution();

        printSolution();

        determinantMatrix();

        //upperLowerLU();

        //printMatrix();



    }

    // This constructor use two paarameters a matrix and a array, like Ax = b or Ax = 0//

    MatrixOperation(float** _matrix, float* _array, int _line, int _colum){

        printf("--> Second type of constructor\n");

        n = _colum;
        m = _line;

        alocMatrix();
        alocArray();

        printf("--> The size of Lines: %d -- The size of Colums: %d\n", m, n);

        // puting the values we've received by function on the parameters we created on the class //
        // Matrix //

        for(int i = 0; i < n ;i++){

            for(int j = 0; j < m ; j++){

                matrix[i][j] = _matrix[i][j];

            }

        }

        // array //

        for(int i = 0; i < m ; i++){

            array[i] = _array[i];

        }

        printMatrixArray();


    }


    // ===== GAUSSIAN ELIMINATION ===== //

    // This method do the Gaussian Elimination to find the solution of the system //
    // naive elimination , 'cuz doesn't consider the zeros //
    // n max = 100 //
    // I guess its complete //

    void gaussianElimination(){

        if(m != n){

            printf("Error -- Isn't a linear system\n");

        }
        else{

            progressiveElimination();
            progressiveElimination();


        }


    }

    void progressiveElimination(){

        // This method just works for linear systems //

        if(m != n){

            printf("Warning: This is not a Linear System!!\n Wasn't able to continue.\n");


        }else{

            halfPivot();

            for(int k = 0 ; k < n - 1 ; k++){

                for(int i = k + 1 ; i < m ; i++){

                    float factor = matrix[i][k]/matrix[k][k];

                    for(int j = k ; j < n ; j++){

                        matrix[i][j] = (matrix[i][j] - (matrix[k][j]*factor));

                    }

                    array[i] = array[i] - factor * array[k];

                }

                // To show pass by pass how was done //

                printMatrixArray();

                printf("\n");

            }

            printf("The Gaussian Elimination was successful!!\n");

            printMatrixArray();

            printf("\n");

        }

    }

    // this method do the substitution  to solve the  system //
    // I guess Its finished //

    void regressiveSubstitution(){

        printf("--> Regressive Solution\n");

        solution[m-1] = (array[m-1]/matrix[m-1][m-1]);

        for(int i = m - 1 ; i >= 0 ; i--){

            printf("--> %d\n", i);

            float soma = array[i];

            for(int j = i + 1 ; j < n ; j++){

                printf("- Soma = %f --", soma);

                soma = soma - (matrix[i][j]*solution[j]);

                printf(" Soma = %f \n", soma);

                printf("- Soma = Soma - %f * %f \n", matrix[i][j], solution[j]);

            }

            solution[i] = soma/matrix[i][i];

        }
    }

    // Half pivot, this methos was created to avoid divison by zero ou problems with rouding //
    // Seens to be working //

    void halfPivot(){

        if( round(matrix[0][0]) != 0 ){

            printf("--> The first Element is not near/equal to zero.\n");

        }
        else{

            // We need to know which is the greatest value//
            float higher;
            // u is going to be the value of the 'i' //
            int u;

            higher = matrix[0][0];

            for(int i = 0; i < m ; i++){

                if(higher < matrix[i][0]){

                    higher = matrix[i][0];
                    u = i;

                }

            }

            if(higher == matrix[0][0]){

                printf("--> There is not other value that is higher than the first element.\n");

            }
            else{

                printf("There is other value in the matrix tha is higher than the first element.\n");

                // Here we are going to change the lines, in this case, the first with the respective one //

                // Variable to put the value //

                float swaper;

                for(int j = 0; j < n ; j++){

                    swaper = matrix[0][j];
                    matrix[0][j] = matrix[u][j];
                    matrix[u][j] = swaper;

                }

                // Swaping the values of the 'b' array //

                swaper = array[0];
                array[0] = array[u];
                array[u] = swaper;


            }

        }


        printMatrixArray();

    }

    // ===== END OF METHOS OF GAUSSIAN ELIMINATION ===== //

    // ===== REMEMBER TO PUT THIS METHOD ON PRIVATE ===== //

    // This method calculates the determinant //

    void determinantMatrix(){

        if( n == m ){

            printf("--> Line and colum has the same size.\n");

            if(n == 1)
                printf("Determinant: %f\n", matrix);
            else if(n == 2)
                printf("Determinant: %f\n", determinantMatrixSize2());
            else if(n == 3)
                printf("Determinant: %f\n", determinantMatrixSize3());
            else if(n > 3 && n < 16)
                printf("Determinant: \n");

        }
        else{

            // To calculate the determinant, the matrix needs to be a square matrix //

            printf("--> This isn't a square matrix. It's note possible to calculate the determinant.\n");

        }

    }

    // This method calculates the determinant of a matrix with size = 2 //

    float determinantMatrixSize2(){

        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

    }

    // This method calculates the determinant of a matrix with size = 3 //

    float determinantMatrixSize3(){

        return ( matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] -
                 matrix[0][2] * matrix[1][1] * matrix[2][1] - matrix[2][1] * matrix[1][2] * matrix[0][0] - matrix[0][1] * matrix[1][0] * matrix[2][2]);

    }

    // This methos calculates the determinant of a matrix with size greater than 3 //

    // ===== END OF THE LIST OD METHOD THAT I SHOULD PUT ON PRIVATE  ===== //

    // This method prints our matrix //

    void printMatrix(){

        printf("--> Matrix has been printed \n\n");

        for(int i = 0 ; i < m ; i++){

            for(int j = 0 ; j < n ; j++){

                printf("%f ", matrix[i][j]);

            }

            printf("\n");

        }


        printf("\n");

    }

    // LU decomposition Using the Crout's method //

    void upperLowerLU(){

        printf("--> Decomposition LU\n");

        for(int j = 1 ; j < n ; j++){

            matrix[0][j] = matrix[0][j]/matrix[0][0];

        }

        for(int j = 1 ; j < n-1 ; j++){

            for(int i = j; i < n ; i++){

                long double sum = 0;

                for(int k = 0; k < j-1; k++){

                    sum = sum + matrix[i][k] * matrix[k][j];

                }

                matrix[i][j] = matrix[i][j] - sum;

            }

            for(int k = j + 1 ; k < n; k++){

                long double sum = 0;

                for(int i = 0; i < j - 1 ; i++){

                    sum = sum + matrix[j][i] * matrix[i][k];

                }

                matrix[j][k] = matrix[j][k] - sum;

            }

        }

        long double sum = 0;

        for(int k = 0 ; k < n-1 ; k++){

            sum = sum + matrix[n-1][k] * matrix[k][n-1];

        }

        matrix[n-1][n-1] = matrix[n-1][n-1] - sum;

    }

    // This method prints our Array //

    void printArray(){

        for(int i = 0 ; i < m ; i++){

            printf("%f ", array[i]);

        }

        printf("\n");

     printf("-->The Array has been printed\n");

    }

    // This method prints our Array + Matrix //

    void printMatrixArray(){

        printf("--> The Matrix Ax = b has been printed\n");

        int k = 0;

        for(int i = 0 ; i < m ; i++){

            for(int j = 0 ; j < n ; j++){

                printf("%f ", matrix[i][j]);

            }

            printf("  %f", array[k]);

            printf("\n");

            k++;

        }

    }

    // print solution vector //

    void printSolution(){

        printf("--> The solution Array\n");

        for(int i = 0 ; i < m ; i++){

            printf("%f ", solution[i]);

        }

        printf("\n");

    }

    // Dynamicaly alocating the matrix //

    void alocMatrix(){
        printf("--> The Matrix has been Alocated \n");

        // using malloc to dynamicaly use the matrix //

        matrix = (float**)malloc(sizeof(float*)*n);

        for(int j = 0 ; j < n ; j++){

            matrix[j] = (float*)malloc(sizeof(float)*m);

        }

    }

    // This method alocate the array b and x //

    void alocArray(){

        array = (float*)malloc(sizeof(float)*m);

        printf("--> The array has been alocated!!\n");

        solution = (float*)malloc(sizeof(float)*m);

        printf("--> The solution array has been alocated!!\n");


    }

    // This method set the values and the size of the matrix //

    void setMatrix(){

        printf("--> Please insert the values of the matrix \n");

        for(int i = 0 ; i < m ; i++){

            for(int j = 0 ; j < n ; j++){

                scanf("%f ", &matrix[i][j]);

            }

            if(i == m - 1){

                break;

            }

        }

        cin.ignore();

        printf("The matrix has been set!!\n");

    }

    // This methos set the value of the array //

    void setArray(){

        printf("--> Please insert the values of the vector 'b' \n");

        for(int i = 0 ; i < m ; i++){

            scanf("%f ", &array[i]);

            if( i == m -1){

                break;

            }

        }

        printf("The array 'b' has been set!!\n");

    }

    // Change the value of the Matrix //

    void changeValue(){
        int i,j;
        printf("--> You wish to change the value of what value? line : Colum \n");
        scanf("%d %d", &i, &j);

        printf("--> Wich value you want to insert: \n");
        scanf("%f", &x);

        matrix[i][j] = x;
    }

    // ==== METHODS TO MAKE OPERATIONS WITH THE MATRIX //

    // This method multiply the matrix by a constant //

    void multiplyByContant(float _k){

        //printf("Choose the value you wish to multiply by:");
        //scanf("%f", &_k);

        for(int i = 0 ; i < m ; i++ ){

            for(int j = 0 ; j < n ; j++ ){

                matrix[i][j] = matrix[i][j]*_k;

            }
        }

        printf("--> The matrix has been multiplied by: %1f\n", _k);

        printMatrix();

    }

    // Method to multiply two matrcies //
    // first matrix, line1, colum1, second matrix, line2, colum2) //
    // I haven't test it yet //

    void multiplyTwoMatricies(float** matrix1, int line1, int colum1, float** matrix2, int line2, int colum2){

        if(colum1 != line2){

            printf("It's impossible to multiply this matrix, because first matrix's line is diferent from second matrix's colum value");

        }
        else{

            for(int k = 0; k < line1; k++){

                for(int i = 0; i < colum2; i++){

                    float soma = 0;

                    for(int j = 0; j < line2; j++){

                        soma = soma + matrix1[k][j] * matrix2[j][i];

                    }

                    matrix[k][i] = soma;

                }


            }

        }

    }

    // ==== THE END OF METHODS TO MAKE OEPRATIONS WITH MATRIX //

    // ===== JUST FOR TRANSPOSED MATRIX ===== //

    // this method verify if the matrix is equal to its transposed //

    bool transposedVerify(){

        if(n == m){

            for(int i = 0; i < n ; i++){

                for(int j = 0; j < n ; j++){

                    if(matrix[i][j] != matrix[j][i]){

                        printf("The Matrix isn't equal to its tranpose. \n");

                        return 0;

                    }


                }


            }

            return 1;

        }
        else{

            printf("This is not a square Matrix!! Can't Verify.\n");

            return -1;

        }


    }

    // This method print the transposed matrix //

    void printTranposedMatrix(){

        printf("--> The Transposed Matrix has been printed\n");

        for(int i = 0 ; i < m ; i++){

            for(int j = 0 ; j < n ; j++){

                printf("%f ", matrix[j][i]);

            }

            printf("\n");

        }

    }

    // ===== END OF TRNAPOSED MATRIX ===== //
};



int main()
{
    float** matrix;
    float*  array;

    // MATRIX //

    matrix = (float**)malloc(sizeof(float*)*3);

    for(int j = 0 ; j < 3 ; j++){

        matrix[j] = (float*)malloc(sizeof(float)*3);

    }

    // ARRAY //

    array = (float*)malloc(sizeof(float)*3);

    // Initializing the values //

    for(int i = 0; i < 3 ; i++){

        for(int j = 0 ; j < 3 ; j++){

            matrix[i][j] = 10;

        }

        array[i] = 5;

    }


    // THE CLASS //

    MatrixOperation teste(matrix, array, 3, 3);

    return 0;
}
