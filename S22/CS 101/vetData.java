/* Class code 
    2/15/22
    review & arithmetic practice
    -asks for data about dog from user (use System.out.println)
    -performs calculations
    -outputs to user
*/

import java.util.Scanner;
class vetData{
    public static void main(String[] args) {
        
        String first, last, petName; // notice uppercase, denotes an address
        double weightLB, weightkg;
        int medsAM, medsPM; //notice lowercase variable type
        /* " Double " is a memory address opposed to storing the number
            This is the same concept as a pointer, however, java does not
            work with pointers.
        */
        Scanner dataBaby = new Scanner(System.in);
        System.out.print("Please enter your first name: ");
        first = dataBaby.nextLine();
        System.out.print("Please enter your last name: ");
        last = dataBaby.nextLine();
        System.out.print("Please enter your pet's name: ");
        petName = dataBaby.nextLine();
        System.out.print("Please enter your pet's weight (lbs): ");
        weightLB = dataBaby.nextDouble();
        System.out.print("Please enter what last AM medication (hour): ");
        medsAM = dataBaby.nextInt();
        

        medsPM = (medsAM + 10) % 12;
        weightkg = weightLB / 2.2046;
    


        System.out.format("Your name is:       %s %s\n", first, last);
        System.out.format("Pet's name:         %s\n", petName);
        System.out.format("Pet's weight in kg: %.2f\n", weightkg);
        System.out.format("Take medication at: %d PM\n", medsPM);
        
        dataBaby.close();
    }
}
