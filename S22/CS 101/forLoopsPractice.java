import java.util.Scanner;
class forLoopsPractice {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        /* For loops have four parts
           something we use to count up to a value or until 
           a condition is met.

           for (Part 1; Part 2; Part 3) {
               Part 4;
           } 
           Part 1: initializer, counter's initial value
           Part 2: condition for the loop to stop at
           Part 3: step increment (often by 1, but can be anything)
           Part 4: block of code to execute while iterating
           */
           int numOfPlayers = 3;
           for (int i = 0; i < numOfPlayers; i++) {
               // never returns to part 1 (initializer)
               System.out.println("i is equal to: " + i);
               // loop breaks after the condition is met
           }

    }
}