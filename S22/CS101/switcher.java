/*
  switcher.java
    utilize switch statements to error check
    Will Buziak
    2/25/2022
*/
import java.util.Scanner;
class switcher {
   public static void main(String[] args) {
      double left, right, result;
      String operator;
      Scanner s = new Scanner(System.in);

      System.out.print("Enter <left> <op> <right>: ");
      /*       Scan the double, the operator as a string, and another double */
      /*       Use the variables declared for you above. */

      /* I had to add the double "result" in order to make it easier to compute within
       the switch statement. 
       I am not sure if this is allowed since it was given in the problem statement
       that we are not allowed to change the template, since this new double was a part of 
       template outside of the to do, this would be classified as part of the template 
      */
        left = s.nextDouble();
        operator = s.next();
        right = s.nextDouble();
      
      s.close();
        /*
         This switch statement uses string formatting to easily deal with the float
         condition as well as creating a string with both doubles and strings without
         having to mess around with data types so much. 
         
         An important note is the use of breaks so that one case does not run into another

         If the default case used a similar output string then you would not need to repeat the
         system output line in each case and could just leave it outside of the switch statement. 
         Since default case is different, each case must specify it's actions individually.
        */
      switch(operator) {
        case "+":
          result = left+right;
          System.out.format("%.1f %s %.1f = %.1f%n%n", left, operator, right, result);
          break;
        case "-":
          result = left-right;
          System.out.format("%.1f %s %.1f = %.1f\n\n", left, operator, right, result);
        break;
        case"/":
          result = left/right;
          System.out.format("%.1f %s %.1f = %.1f\n%n", left, operator, right, result);
          break;
        case"*":
          result = left*right;
          System.out.format("%.1f %s %.1f = %.1f\n\n", left, operator, right, result);
          break;
        default:
          System.out.println("Invalid operator!\n\n");
          break;
    }
   }
}