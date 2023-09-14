import java.util.Scanner;

class hangman{
   public static void main(String[] args){
      int n, limbs;
      String player1, player2, winner;
      String[] word = new String[1];
      Scanner scan = new Scanner(System.in);
      boolean running = true;
      boolean condition = false;
      limbs = 10;
         System.out.print("Player 1, enter a word: ");
         word[1] = scan.next();
         System.out.println("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
         n = word.length;
         System.out.println("10 limbs remaining");

         System.out.println("Letters guessed:");

         for (int i = 0; i < n; i++){
            System.out.print("_ ");
         }
      
      
      while (running){
         System.out.print("Player 2, guess a letter: ");
         String L = scan.next();

         for (int i = 0; i < n; i++){
            if (L.equals(word[i])){
               System.out.print(L);
            }
            else{
               System.out.print("_ ");
            }
            if (!L.equals(word[i])){
               limbs--;
               System.out.format("%d limbs remaining", limbs);
            }
         }
      }
   }
}