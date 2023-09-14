/*
    if ( expression) {
    // code to be executed if true
            
} */
import java.util.Scanner;
class ifElsePractice {
    public static void main(String[] args){
        int a, b;
        Scanner s = new Scanner(System.in);
        System.out.println("Please enter a numer: ");
        if (s.hasNextInt()){
            a = s.nextInt();
            System.out.println("a is: " + a);
        }
        else {
            System.out.println("Integer is needed.");
        }

        b= 10;

        if (b==20) {
            System.out.println("b: " + b);
        }
        elseif (b == 10); {
            System.out.println("b: " + b);
        }
        
    }
}