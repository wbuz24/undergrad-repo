import java.util.Scanner;
class miniGolfForLoops {
    public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    int numOfPlayers, score, numHole, currentPlayerNum, currentHole;
    currentHole = 0;
    score = 0;
    numHole = 0;

    System.out.print("Welcome to mini golf scoring !");
    System.out.print("How many players? ");
    numOfPlayers = scan.nextInt();

    if (numOfPlayers > 0) {
        System.out.print(" What is the score for hole #: " + (currentHole + 1) + "?");
        numHole = scan.nextInt();

    }

    for (int i = 0; i < numOfPlayers; i++) {
        System.out.println("Player " + (i + 1) + ": ");

        for (int j = 0; j < numHole; j++) {
            System.out.print(" What is the score for hole #" + (j + 1) + "? ");
            score = score + scan.nextInt();
        }
    }
    System.out.print(" Total score is " + score + ".");
    score = 0;
    System.out.print("Thanks for Playing !");
    
    scan.close();
}
}