import java.util.Scanner;
class doWhile {
    public static void main(String[] args) {
        /* Assume atleast one pet in database
           so we will use a do-while loop

           ask for last name, pets name, weight in lbs, last time for meds AM/PM
        */   

        Scanner scan = new Scanner(System.in);
        String lastName, petName, yn;
       
        double weightLB, weightKG;
        int medsAM, medsPM;

        System.out.print("welcome to the database!");
        System.out.print("do you have more than one pet to enter?: ");
        yn = next();

        if (yn.equals("n")) {
        do {
            // collect user info
            System.out.print("Please enter last name: ");
            lastName = scan.next();
            System.out.print("Please enter last name: ");
            petName = scan.next();
            
            System.out.print("please enter a weight: ");
            if (!scan.hasNextDouble()) {
                System.out.print("Error - weight");
                break;
            }
            weightLB = scan.nextDouble();

            System.out.print("Please enter last AM medication (on the hour): ");
            if (!scan.hasNextInt()) {
                System.out.print("Error - AM medication");
                break;
            }
            medsAM = scan.nextInt();


            weightKG = weightLB*(0.4535924);
            medsPM = (medsAM + 10) % 12;

            System.out.println(petName + "'s needs to take the next round of medication at " + medsPM + "PM. ");
            System.out.format("%s weighs %.2f kg.", petName, weightKG);
           
        } 
        while (yn.equals("y"));
        System.out.print("do you have another pet to enter?: ");

    }

    scan.close();

    }
}