import java.util.Scanner;
class March24_2 {
    public static void main(String[] args) {
        // mini golf scoring
        // if we see brackets, that is a grouping of code

        /* can have a while inside a do-while loop
           can have do-while inside while loop
        */    
        Scanner scan = new Scanner(System.in);
        int numPlay, score, numHole, currentPlayNum, currentHole;
        currentPlayNum = 0;
        currentHole = 0;
        score = 0;

        System.out.println("Welcome to mini-golf scoring !");
        System.out.print("How many players are in your course? ");
        numPlay = scan.nextInt();
        System.out.print("How many holes are in your course? ");
        numHole = scan.nextInt();

        

        
        do {
            System.out.println("Player " + (currentPlayNum + 1) + ": ");
            do{
                System.out.print("What is the score for hole # " + (currentHole + 1) + " ? ");
                score = score + scan.nextInt();
                currentHole++;
            } while(currentHole < numHole);
            // gather and add scores
            System.out.println("  Final score is " + score);
            score = 0;
            currentHole = 0;
            currentPlayNum++;
        } while (currentPlayNum < numPlay);

        System.out.println("thanks for playing!");

        scan.close();
    }
}