// Will Buziak
// CS 101
// Arrays program
// 5-3-2022

import java.util.Scanner;
class arrays {
    private final static int VECTOR_SIZE = 3;
    private final static int MATRIX_SIZE = VECTOR_SIZE * VECTOR_SIZE;
    public static void main(String[] args) {
                 double[] matrix;
                 double[] vector;
        Scanner s = new Scanner(System.in);
        matrix = new double[MATRIX_SIZE];
        vector = new double[VECTOR_SIZE];

        System.out.format("Enter %d matrix values: ", MATRIX_SIZE);
        // This for loop iterates for each spot in the matrix and stores the scanner value.
                 for (int i = 0; i < MATRIX_SIZE; i++) {
                     matrix[i] = s.nextDouble();
                 }
        System.out.format("Enter %d vector values: ", VECTOR_SIZE);  
        // A for loop is necessary for storing both matrices as you need an iterator to 
        // ensure each spot is filled correctly
                 for (int i = 0; i < VECTOR_SIZE; i++) {
                  vector[i] = s.nextDouble();
              }
        s.close();
        // Must call the multiply method declared later in the program, important to 
        // have correct order of inputs
                 double[] result = multiply(matrix,vector);

        System.out.print("Result = [");
        printVector(result);
        System.out.println("]");
    }
    private static void printVector(double[] arr) {
        /* 
            This for loop formats the output and the line "VECTOR_SIZE - 1" designates that
            the last spot is not included, i.e. there is a space after each value, but not the last
        */

        for (int i = 0; i < VECTOR_SIZE-1; i++){
           System.out.format("%.3f ", arr[i]);
        }
        System.out.format("%.3f", arr[VECTOR_SIZE - 1]);
    }
    
    private static double[] multiply(double[] matrix, double[] vector) {
        double[] result;
        result = new double[VECTOR_SIZE];
        /*
            nested for loops iterate through each matrix, the first, i, through matrix
            and the second, j, through vector.

            using the "+=" operator avoids having to add the result vector to itself.

            difficult part here is the indexing for the matrix variable.
        */
        for (int i = 0; i < VECTOR_SIZE; i++ ){
            for (int j = 0; j < VECTOR_SIZE; j++){
                result[i] += matrix[i*VECTOR_SIZE + j]*vector[j];
            }
        }
        return result;
    }
}