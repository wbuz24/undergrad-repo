/*  Collects student data for a database
    and verify the data back to the user. 
*/
import java.util.Scanner;
class StudentData {
    public static void main(String [] args) {
        /* Receive input from the user, including
        first name, last name, student ID, high school,
        last letter grade in CS course, age, and GPA */

        /* "camelCase" is java convention using first 
        word lower case and trailing words capitalized
        */

        String firstName; // "first" is lowercase, and "Name" uppercase
        String last_Name; // "snake case"
        String STUDENT_ID; // "screaming snake case"
        String highSchool; 
        char lastGrade; //does not use +/-
        int age;
        double GPA;

        /* Prompt the user for the data */
        System.out.print("Kid stats for betting pool\n What is your first name? ");
        Scanner inputScanner = new Scanner(System.in);
        firstName = inputScanner.nextLine();

        System.out.print(" What is your last name? ");
        last_Name = inputScanner.nextLine();

        System.out.print(" Student ID? ");
        STUDENT_ID = inputScanner.nextLine();

        System.out.print(" Where did you attend high school? ");
        highSchool = inputScanner.nextLine();

        System.out.print(" What was your last CS grade? ");
        lastGrade = inputScanner.nextLine().charAt(0);

        System.out.print(" How old are you? ");
        age = inputScanner.nextInt();

        System.out.print(" What is your GPA? ");
        GPA = inputScanner.nextDouble();
        /* verify information with the user

        */
        
        System.out.print("First name: " + firstName + "\nLast Name: " + last_Name);
        System.out.print("\nStudent ID: " + STUDENT_ID);
        System.out.print("\nAttended: " + highSchool);
        System.out.print("\nLow bar has been set with a previous grade of: " + lastGrade + ", & a GPA of: " + GPA);
        System.out.println("\nIt has been downhill for the past " + age + " Years, you are: " + age + " years old");

        System.out.print("Make sure you pay Tom by the end of the week.");

        inputScanner.close();
    }
}