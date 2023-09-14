import java.util.Scanner;
class ifStatements {
    public static void main(String[] args){
       int i = 0;
       boolean conditionsDry;
       if (i == 0){
           System.out.print("i is zero.");
       }
       if (i != 0){
           System.out.print("i is not equal to zero."); 
       }

       conditionsDry = true;
       if(!conditionsDry) {
           System.out.print("conditions are not dry");
       }
       else{
           System.out.print("conditions are dry");
       }

       string sensorInput;
       System.out.print("enter a sensor: ");
       sensorInput = scan.next();

       if (sensorInput.equals("HR")){
           System.out.print("HR sensor added.");

       }
       if (sensorInput.equals("speed")){
           System.out.print("speed sensor added.");

       }

       else {
           System.out.print("sensor not recognized.");
       }
    }
}