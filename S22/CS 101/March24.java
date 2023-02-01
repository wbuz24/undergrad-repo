import java.util.Scanner;
class March24 {
    public static void main(String[] args) {
        String repeat;
        int x, y;
        Scanner scan = new Scanner(System.in);

        /* prompt user to begin loop */
        System.out.print("Would you like to add two integers? ");
        repeat = scan.next();

        while (repeat.equals("yes")) {
            /* Promt user and Gather two integers & error check */
            System.out.print("Enter the first integer: ");

            // .hasNextInt() is a boolean that checks value type
            // .nextInt() creates a pointer to store the value of the Int
            // would use .hasNextInt() BEFORE .nextInt().
            if (scan.hasNextInt()) {
                x = scan.nextInt();
            }
            else {
                System.out.print("Try again: ");
                if (scan.hasNextInt()) {
                    x = scan.nextInt();
                }
                else {
                    System.out.print("invalid data type.");
                    break;
                }
            }

            System.out.print("Enter the first integer: ");
            

            System.out.print("Enter another integer: ");

            /* Ask if user would like to continue */
            System.out.print("Would you like to add again? ");
            repeat = scan.next();
        }
        System.out.println("Program Exiting.");
    }
}