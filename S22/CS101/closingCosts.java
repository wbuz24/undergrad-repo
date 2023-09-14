/* closing cost calculator
    Ask user for 3 houses they are interested in
    price, down payment.
*/
import java.util.Scanner;
class closingCosts {

    /* function definitions */
    static double calculation(int price, int downPayment){
        double cash, dPP, cCP;
        // do calculation
        // if we have time, error check
        int closingCostPercent = 4;

        dPP = downPayment/100.0;
        cCP = closingCostPercent/100.0;

        cash = (price * dPP) + (price * cCP);
        return cash;
    }

    static void prompt1(int num) {
        System.out.print("What is the price of estate " + num + "? ");
    }

    static void prompt2() {
        System.out.print("What is the down payment in percent? ");
    }
    
    public static void main(String[] args) {
        

        int homePrice, downPayPercent;
        double cashToClose; 
        
        Scanner s = new Scanner(System.in);
        
        prompt1(1);
        homePrice = s.nextInt();
        prompt2();
        downPayPercent = s.nextInt();
        cashToClose = calculation(homePrice,downPayPercent);
        System.out.println(cashToClose);
        // Calculate closing costs
        

        prompt1(2);
        homePrice = s.nextInt();
        prompt2();
        downPayPercent = s.nextInt();
        cashToClose = calculation(homePrice,downPayPercent);
        System.out.println(cashToClose);

        s.close();
    }
}