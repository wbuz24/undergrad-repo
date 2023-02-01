/*
    Class code 
    2/10/22
    CS 101
    format printing
*/

import java.util.Scanner;
class formattedOutput {
    public static void main(String[] args) {

        // learn format printing
        /*
        Key differences:
        - Dont use the plus sign to separate literal strings & variables
        - We use specific symbols to denote where the variable 
        - Must tell java what those type of variables are
        */
        String first, last;
        double gpa;
        Scanner myInput = new Scanner(System.in);

        System.out.println("What is your first name?");
        first = myInput.next();

        System.out.println("What is your first last?");
        last = myInput.next();

        System.out.println("What is your gpa?");
        gpa = myInput.nextDouble();

        /*
            Inside the "()", the first thing to write is the formatted string in quotes
            INCLUDING any special symbols for having variables in the string.
            After the string quotes, we list variables we want to use in order.
            
            ("formatted string,", variable1, variable2, variable3,)
        */
        System.out.format("Your first, last name & gpa are:%n%-11s %-11s %.2f", first, last, gpa);
        /* if input is larger than specified char width, entire input will be printed with no formatting
        inbetween
        */ 
        myInput.close();

        /*
        % - ___ . ______ f: minus sign, character width, a period, & sig figs
        % - ___ s: minus sign, char width
        % - ___ d: minus sign, char width
        %-10s left justified with 10 character width
        %10s right justified w/ 10 character width
        */
    }
}