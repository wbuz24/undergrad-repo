/*  Varops.java
    Input three doubles, output formula and result
    with two decimal places
    Will Buziak
    2/14/2022
*/
import java.util.Scanner;
class varops {
   public static void main(String[] args) {
      double a;
      double b;
      double c;
      Scanner s = new Scanner(System.in);
      System.out.print("Enter three doubles (a / b + c): ");
      a = s.nextDouble();
    
      b = s.nextDouble();
    
      c = s.nextDouble();
      // Input allows three inputs so long as there is whitespace inbetween the doubles
      s.close();

      double result = (a/b) + c; 
      // double roundResult = Math.round(result*100.0)/100.0;
      /* This takes the result of the equation and ensures a precision
      of 2 decimal places
      */
      /*
      Using concatenation of strings with the '+' along with
      stored variables, must watch for spaces to allow easy reading
      in output.
      */
      String sentence;
      sentence = String.format("%.2f / %.2f + %.2f = %.2f ", a,b,c,result); 
      System.out.print(sentence);
      // string format is quicker to deal with 
      // decimals in one step as output
      // System.out.print(a + " / " + b + " + " + c + " = " + roundResult); 
      // uses concatenation (requires more front end manipulation)
      // must use quotes around arithmetic operators,
      // otherwise, java thinks you are trying to perform arithmetic
   }
}