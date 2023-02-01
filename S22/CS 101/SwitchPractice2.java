/*  Read in a symbol from the command line
    If we read in a $ -- that's addition
    If we read in a ! -- that's subtraction
    If we read in a ^ or & -- that's multiplication
    If we read in a # -- that's division
*/
import java.util.Scanner;
class SwitchPractice2 {
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);

        double num1, num2, result;
        String mySymbol;
        System.out.println("Enter $, !, ^, or #: ");
        mySymbol = s.nextLine();
        System.out.println("Enter 2 numbers for the operation: ");
        num1 = s.nextDouble();
        num2 = s.nextDouble();

        switch(mySymbol) {
            case "$":
                // addition
                result = num1 + num2;
                System.out.format("Addition: ");
                break;
            case "!":
                // subtraction
                result = num1 - num2;
                System.out.format("Subtraction: ");
                break;
            case "^":
            case "&":
                // multiplication
                result = num1 * num2;
                System.out.format("Multiplication: ");
                break;
            case "#":
                // division
                result = num1/num2;
                System.out.format("Division: ");
                break; 
            default:
                result = 0;
                System.out.println("error: ");
                break;

        }
        System.out.format("result = %.2f%n",result);
        s.close();
    }
}