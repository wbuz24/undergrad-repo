/* 
Array list

declare:

ArrayList <Integer> nameOfArrayList;
Type goes here ^

*/

import java.util.Scanner;
import java.util.ArrayList;
class arrayPractice {

   public static void main(String[] args){
      int lengthOfArray;
      int[] scores;

      System.out.print("Enter the number of scores: ");
      Scanner scan = new Scanner(System.in);
      lengthOfArray = scan.nextInt();

      scores = new int[lengthOfArray];

      for (int i = 0; i < lengthOfArray; i++){
         System.out.print("What is the score for student# " + i + ": ");
         scores[i] = scan.nextInt();
      }

      for (int i = 0; i < scores.length; i++){
         System.out.println("score for student# " + i + ": " + scores[i]);
      }

      int sizeOfArray = lengthOfArray;
      ArrayList <Integer> scores2;
      scores2 = new ArrayList<>(sizeOfArray);


      for (int i = 0; i < sizeOfArray; i++){
         System.out.print("Enter a score for the ArrayList: ");
         int s = scan.nextInt();
         scores2.add(s);
      }

      for (int i = 0; i < sizeOfArray; i++){
         System.out.println(scores2.get(i));
      }

      // Beyond initial size allocated:
      System.out.print("Enter a score for the ArrayList: ");
      int s = scan.nextInt();
      scores2.add(s); // dynamically allocating another spot (resizing the AL automatically by 1,
                      // we scanned in to the end)
      System.out.println(scores2.get(sizeOfArray));

      scores2.clear(); // clear everything from the arraylist
      System.out.println("Cleared ArrayList");

      System.out.println("Size of scores2 is: " + scores2.size());
      
      for (int i =0; i < sizeOfArray; i++) {
         System.out.println(scores2.get(i));
      }
      
      
   
   }
}
