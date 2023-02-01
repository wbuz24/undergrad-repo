 /*
      have 2 players, ask for their scores
      and store in an arraylist
      which can use to print scores for each hole
      & change scores.
      */


import java.util.ArrayList;
import java.util.Scanner;

class golfUpdated{
   public static void main(String[] args){

      String play1, play2;
      int score1 = 0;
      int score2 = 0;
      int strokes;
      int playNum;

      ArrayList<Integer> player1Holes;
      ArrayList<Integer> player2Holes;

      final int SHORT_GAME = 4;
      final int TOTAL_HOLES = 18;

      player1Holes = new ArrayList<>(TOTAL_HOLES);
      player2Holes = new ArrayList<>(TOTAL_HOLES);

      Scanner scan = new Scanner(System.in);

      System.out.println("Welcome to golf scoring!");
      System.out.print("Player 1, what is your name? ");
      play1 = scan.nextLine();
      System.out.print("Player 2, what is your name? ");
      play2 = scan.nextLine();


      for (int i = 0; i < SHORT_GAME; i++){
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

         can use .size() method here with an ArrayList, however, arrays use .length, not .size()
         and we can use the .get() method to retrieve elements from the ArrayList
         .get() uses an index as a parameter, and gives us what is stored in that index.

         remember- 0 indexing.
      */

      System.out.println(play1 + "'s' Game: ");
      for (int i = 0; i < player1Holes.size(); i++){

         System.out.println(" Hole " + (i+1) + ": " + player1Holes.get(i));
      }

      for (int i = 0; i < player2Holes.size(); i++){
         System.out.println(" Hole " + (i+1) + ": " + player2Holes.get(i));
      }

      // check for incorrect scores
      System.out.println("Was there an incorrect score for Player 1 or 2?");

      System.out.print("If so, which player was it (1-2 or 0? ");
      playNum = scan.nextInt();

      // use a conditional to check 

      if (playNum == 1){
         // need to ask which hole #
         // can use .set() method to change score at index hole #
         System.out.print("which hole? ");
         int inHole = scan.nextInt(); // index

         System.out.print("What is the correct score? ");
         int newScore = scan.nextInt(); // new value

         player1Holes.set(inHole - 1, newScore);
         System.out.println("Player 1's corrected game:");
         for (int i =0; i < player1Holes.size(); i++){
            System.out.println(" Hole " + (i +1 ) + ": " + player1Holes.get(i));
         }
      }
      else if (playNum == 2){
         // need to ask which hole #
         // can use .set() method to change score at index hole #
         System.out.print("which hole? ");
         int inHole = scan.nextInt(); // index

         System.out.print("What is the correct score? ");
         int newScore = scan.nextInt(); // new value

         player2Holes.set(inHole - 1, newScore);
         System.out.println("Player 2's corrected game:");
         for (int i =0; i < player2Holes.size(); i++){
            System.out.println(" Hole " + (i +1 ) + ": " + player2Holes.get(i));
         }
      }


      /* can change code to have more helper functions
         Do this anywhere with repetition

         should do more error checking

         did not account for BOTH player's scores incorrect
      
      */
      /*
      for (int i =0; i < SHORT_GAME; i++){
         System.out.println("You entered: " + player1Holes.get(i));
      }
      */
      scan.close();
   }
}