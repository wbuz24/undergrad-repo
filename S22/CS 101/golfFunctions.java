import java.util.ArrayList;
import java.util.Scanner;

class golfFunctions{
   public static final int TOTAL_HOLES = 2;

   public static void printHoles(ArrayList<Integer> myAL) {

      for (int i = 0; i < myAL.size(); i++){

         System.out.println(" Hole " + (i+1) + ": " + myAL.get(i));
      }
   }

   public static String askName(int n, Scanner s) {
      System.out.print("Player " + n + ", what is your name? ");
      String name = s.nextLine();
      return name;
   }

   public static void editHoles(ArrayList<Integer> myAL, scanner s, String name){
      int inHole;
      int newScore;
      do {
      System.out.print("which hole? ");
      inHole = s.nextInt(); // index
      } while (inHole < 1 || inHole > TOTAL_HOLES);
      do {
      System.out.print("What is the correct score? ");
      newScore = s.nextInt(); // new value
      } while (newScore < 1);
      myAL.set(inHole - 1, newScore);
      System.out.println(name + "'s corrected game:");
      printHoles(myAL);
   }

   public static int addScores(ArrayList<Integer> myAL){
      int score = 0;
      for (int i = 0; i < myAL.size(); i++){
         score += myAL.get(i);
      }
      return score;
   }
   public static void main(String[] args){

      String play1, play2;
      int score1;
      int score2;
      int strokes;
      int playNum;

      ArrayList<Integer> player1Holes;
      ArrayList<Integer> player2Holes;

      player1Holes = new ArrayList<>(TOTAL_HOLES);
      player2Holes = new ArrayList<>(TOTAL_HOLES);

      Scanner scan = new Scanner(System.in);

      System.out.println("Welcome to golf scoring!");
      
      play1 = askName(1, scan);
      play2 = askName(2, scan);


      for (int i = 0; i < TOTAL_HOLES; i++){
         System.out.print("What was Player 1's score for hole " + (i+1) + "? ");
         strokes = scan.nextInt();
         player1Holes.add(strokes);

         // can re-use throwaway var "strokes" because it is being stored elsewhere in the arraylist
         System.out.print("What was Player 2's score for hole " + (i+1) + "? ");
         strokes = scan.nextInt();
         player2Holes.add(strokes);

      }

      /* see if scores are correct by looping through player's respective
         array lists 
         remember- 0 indexing.
      */

      System.out.println(play1 + "'s' Game: ");
      printHoles(player1Holes);

      printHoles(player2Holes);

      // check for incorrect scores
      do {
      System.out.println("Was there an incorrect score for Player 1 or 2?");

      System.out.print("If so, which player was it (1-2 or 0? ");
      playNum = scan.nextInt();

      // use a conditional to check 

      if (playNum == 1){
         // need to ask which hole #
         editHoles(player1Holes, scan, play1);
      }
      else if (playNum == 2){
         editHoles(player2Holes, scan, play2);
         }
      
      } while (playNum != 0);

      // add up scores and declare winner
      score1 = addScores(player1Holes);
      score2 = addScores(player2Holes);

      if (score1 < score2){
         System.out.println("Congrats! " + play1 + " has won the game!");
      }
      else if (score2 > score1){
         System.out.println("Congrats! " + play2 + " has won the game!");
      }
      else {
         System.out.println("There has been a tie!");
      }
      System.out.println("Thank you for playing " + play1 + " " + play2);

   }
}