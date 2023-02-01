import java.util.Scanner;
class classes {
   public static void main(String[] args) {
      boolean isrunning = true;

      // looking at constructor definition below, it does not take any inputs
      classes myclass = new classes(); // creating a new class instance is the same as creating a new object
      Scanner s = new Scanner(System.in);
      do {
         do {
            System.out.print("Enter an integer (\"quit\" to quit): ");
            if (!s.hasNextInt()) {
               if (s.next().equals("quit")) {
                  isrunning = false;
                  break;
               }
               System.out.println("You did not enter an integer, try again.");
            }
            else {
               myclass.addValue(s.nextInt());
               // This line uses the . function to essentially create a "local" variable that
               // the code can use later on. we specify the "addValue" method in which the value will be used as an input
               break;
            }
         } while (true);
      } while (isrunning);
      s.close();
      
     
      System.out.format("Number of values entered = %d%n", myclass.getNumValues());
      System.out.format("Sum of all values        = %d%n", myclass.getSum());
      System.out.format("Product of all values    = %d%n", myclass.getProduct());
      System.out.format("Biggest value            = %d%n", myclass.getMax());
      System.out.format("Smallest value           = %d%n", myclass.getMin());
      System.out.format("Average of all values    = %.2f%n", myclass.getAverage());
      // I originally made the mistake of using the original variable names such as "myclass.mNumvalues()"
      // which obviously created an error but I quickly realized it was because I was using a private variable
      // this was a quick fix to simply use the getter variable which is public.
   }

   // method
   public void addValue(int val) {
      mNumValues++;

      mSumOfValues = mSumOfValues + val;

      mProductOfValues = mProductOfValues * val;


      /*
         The first if statement checks if there is only one value at which that value is both
         the max & the min. if this is not true the next two if statements check if the value
         is a minimum or maximum & set that value to the respective extreme.

         I originally tried to use an if else statement to produce mutual exclusivity,
         however was running into simple syntax errors such as the statement trying to make me use
         a semi-colon. now I am not sure if this is correct syntax or not but decided that simply using separate if 
         statements was satisfactory. 
      */
      if (mNumValues == 1) {
         mMaximumValue = val;
         mMinimumValue = val;
      }
      if (val > mMaximumValue) {
         mMaximumValue = val;
      }
      if (val < mMinimumValue) {
         mMinimumValue = val;
      }
   }

   // method
   public double getAverage() {
         if (mNumValues == 0) {
            double average = 0.0;
            return average;
         }
         else {
            double average = (double)(mSumOfValues/mNumValues);
            return average;
         }
         // this set of if statement first checks if the number of values is zero, to which the average is then
         // output as 0.0, else, the average is calculated and returned.
   }

   // constructor
   public classes() {
     mNumValues = 0;
     mSumOfValues = 0;
     mProductOfValues = 1;
     mMaximumValue = 0;
     mMinimumValue = 0;
     // it is important to note that the product must be 1 in order to properly multiply integers

   }

   // fields
   private int mNumValues;
   private int mSumOfValues;
   private int mProductOfValues;
   private int mMaximumValue;
   private int mMinimumValue;


   // getters & setters written for us to access above fields
   public int getSum() {
      return mSumOfValues;
   }

   public int getNumValues() {
      return mNumValues;
   }

   public int getProduct() {
      return mProductOfValues;
   }

   public int getMin() {
      return mMinimumValue;
   }

   public int getMax() {
      return mMaximumValue;
   }
}