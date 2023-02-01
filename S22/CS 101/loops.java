import java.util.Scanner;
class loops {
   public static void main(String[] args) {
      double exponent;
      Scanner s = new Scanner(System.in);

      /* 
      while (true) runs the loop repeatedly until conditions are met to quit
      */
     
      while (true) {

      System.out.print("Enter exponent: ");

      /* 
        This nested if statement passes the scanned value to see if it is
        a double, then else if the string "quit". if both of these are satisfied, the program will break,
        with an else if statement that checks if a random string is entered.

        There are many ways to go about this but currently our best option is the 
        if & else if statements instead of trying to use the ! function or nested if statements
        for readability.

      */
      if (s.hasNextDouble()){
        exponent = s.nextDouble();
        exponent = Math.exp(exponent);
        System.out.format("Result = %.4f%n", exponent);
      }   
      else if (s.hasNext("quit")) {
        break;
        } 
      else {
        String var = s.nextLine();
        System.out.print("Invalid input.\n");
        /*
        This else statement is only reached if the value in the scanner is
        NEITHER a double or the string "quit". 
        
        I had issues with this block of code as I could make the loop break successfully, however
        had issues not getting stuck in an infinite loop. I later discovered the issue is that 
        the scanner was getting stuck storing the output string "Invalid input" as the input for 
        the next loop, which triggered an infinite sequence.

        To fix this problem, I included line #32 to store the value in the scanner before moving 
        on to the next iteration.

        */

      }
       
    }
    s.close(); // scanner opens and closes only once in the code.
  }
     
}