/* Wbuziak
2/1/2022
Assignment: Greeting Program */
import java.util.Scanner;
class greeting {
   public static void main(String[] args) {
      String first;
      String last;
      Scanner s = new Scanner(System.in);
      System.out.print("What is your first name? ");
      first = s.next();
      // Request last name ( follows model given )
      System.out.print("what is your last name? ");
      last = s.next();
      // Print output message (Using concatenation to produce a pleasing output message)
      System.out.print("I hear they call you " + first + " " + last);
      s.close();
      /* This code uses concatenation of strings based off user inputs,
      the important part to note about this assignment is the use of spaces
      to produce a desirable output*/
   }
}





   