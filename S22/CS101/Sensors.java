import java.util.Scanner;
class Sensors {
    public static void main(String[] args){
        // Promt user for sensor (Heart Rate, Speed, Cadence, or Power)
        // Read in the sensor string
        String sensorInput;
        Scanner sense = new Scanner(System.in);

        /*
        Gather the sensor from the user
        */ 
        System.out.print("Enter your sensor (HR, Speed, Cadence, or Power): ");
        sensorInput = sense.next(); 

        /* 
        No error checking present, assumes user
        follows directions
        */
        switch(sensorInput){ // switch statements start & end w/ {}
        case "HR":
        case "Heart Rate":
            // Code executes only for HR
            // "break" exits switch statement without checking other cases
            // returns outside of } to execute the rest of the program
            System.out.println("HR Sensor added.");
            break;
        case "Speed":
        case "S":

        case "Cadence":
        case "C":
        System.out.println("Speed/Cadence sensor added.");
            break;
        case "Power":
        System.out.println("Power sensor added.");
            break;
        default:
        System.out.println("Sensor not recognized.");
            break;
        }
        sense.close();
    }
}