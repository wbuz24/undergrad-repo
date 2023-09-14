/*
  conditions.java
    use if else statements to error check
    Will Buziak
    3/1/2022
*/
import java.util.Scanner;
class conditions {
   public static void main(String[] args) {
      String user, pass;
      Scanner s = new Scanner(System.in);
      System.out.print("Enter username: ");
      user = s.next();
        if(!(user.equals("orange"))){
            s.close();
            System.out.println("unknown user, " + user);
            return;
        }
        /*
        It is more efficient to write an if statement that evalutes if the string
        is NOT equal to the value, print & exit the code than trying to evaluate if the string
        is correct, do nothing and skip the else case.
        Therefore, it is not necessary to have any else or else if statements 

        It was necessary to use the .equals() evaluator in order to evaluate the string

        It is worthy to note that so long as you use the nextLine() operator for BOTH
        user & pass, it will work, however since the expected imput is only one word it is
        less prone to error to just use next().
        */
      System.out.print("Enter password: ");
      pass = s.next();
      s.close();
        if(!(pass.equals("white"))){
            System.out.println("Incorrect password.");
            return;
        }
        
      System.out.println("Welcome!");
   }
}