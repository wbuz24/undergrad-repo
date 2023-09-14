import java.util.Scanner;
class movieStarName {
    public static void main(String[] args) {
        String street, petName;
        int numofPlayers;
        Scanner myInput = new Scanner(System.in);

        System.out.print("How many people are playing? ");
        numofPlayers = myInput.nextInt();

        // prompt user for info
        for (int i = 0; i < numofPlayers; i++) {
            System.out.println("Player " + (i + 1) + ": ");
            System.out.print("Enter street you grew up on: ");
            street = myInput.next();
            System.out.print("Enter first pet's name: ");
            petName = myInput.next();
            System.out.print("Enter your middle name: ");
            String middle = myInput.next();

            System.out.println("Your movie star name is " + petName + " " + street + " " + middle + " ");
        
        }
        System.out.println("Thanks for Playing!");
    }
}