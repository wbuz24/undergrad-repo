import java.util.Scanner;
class forloops {
   public static void main(String[] args) {
      String input;
      int n;
      Scanner s = new Scanner(System.in);

      /* 
       I used a while (true) loop to continuously ask the user until the program reads the input "quit" at which point it breaks.
      */
      while (true) {
      System.out.print("Sum or product (type 'quit' to quit): ");
      input = s.next();
      if (input.equals("quit")) {
         break;
      }
      else if (!input.equals("sum") && !input.equals("product")) {
         System.out.println("Invalid operation, try again.");
         continue;
      }
      System.out.print("How many values? ");
      n = s.nextInt();
      if (input.equals("sum")) {
         /*
            This section of code initializes the double result as zero. This computes the sum by adding the value
            of result to itself + the loaded value from user input. The for loop continues this summation until the # of doubles
            are sufficiently added. 
         */
        double result = 0;
      
            for (int i=0; i < n; i++) {
                System.out.print("Enter value #" + i + ": ");
                double sumVal = s.nextDouble();
                
                result = result + sumVal;
            }
            System.out.format("Sum = %.3f%n", result);
        }
        // uses string format to format the output to three decimals. 
        // This is favorable over print format so you can control the precision all in the output line.
      else {
         /* 
            This section begins by initializing the result variable as 1, I originally initialized it as zero in the same fashion as
            the previous for loop for summation, however quickly realized that my output was giving me zeros because any # multiplied
            by zero is zero.
         */
        
        double result2 = 1;
        for (int j=0; j < n; j++) {
            System.out.print("Enter value #" + j + ": ");
            double prodVal = s.nextDouble();
            
            result2 = result2 * prodVal;
        }
        System.out.format("Product = %.3f%n", result2); 
         }
         
         
        }
      s.close();
   }
}