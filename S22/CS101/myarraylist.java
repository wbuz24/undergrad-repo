/*
    Will Buziak
    5-10-2022
    myArrayList program
    create an array list using arrays
    CS 101
*/

import java.util.Scanner;
class myarraylist {
    public static void main(String[] args) {
        int i;
        int sz;
        double iv;
        myarraylist mal = new myarraylist();
        Scanner s = new Scanner(System.in);
        boolean running = true;

        do {
            System.out.print("Enter command: ");
            switch (s.next()) {
                case "new":
                    if (s.hasNextInt()) {
                        sz = s.nextInt();
                        if (s.hasNextDouble()) {
                            iv = s.nextDouble();
                            mal = new myarraylist(sz, iv);
                        }
                        else {
                            mal = new myarraylist(sz);
                        }
                    }
                    else {
                        mal = new myarraylist();
                    }
                break;
                case "get":
                    i = s.nextInt();
                    if (i < 0 || i >= mal.size()) {
                        System.out.println("Index " + i + " does not exist.");
                    }
                    else {
                        System.out.println(mal.get(i));
                    }
                break;
                case "index":
                    iv = s.nextDouble();
                    System.out.println(mal.indexOf(iv));
                break;
                case "set":
                    i = s.nextInt();
                    iv = s.nextDouble();
                    if (i < 0 || i >= mal.size()) {
                        System.out.println("Index " + i + " does not exist.");
                    }
                    else {
                        mal.set(i, iv);
                    }
                break;
                case "rem":
                    if (s.hasNextInt()) {
                        i = s.nextInt();
                        if (i < 0 || i >= mal.size()) {
                            System.out.println("Index " + i + " does not exist.");
                        }
                        else {
                            mal.remove(i);
                        }
                    }
                    else {
                        iv = s.nextDouble();
                        mal.remove(iv);
                    }
                break;
                case "size":
                    System.out.println(mal.size());
                break;
                case "add":
                    if (s.hasNextInt()) {
                        mal.add(s.nextInt(), s.nextDouble());
                    }
                    else {                    
                        mal.add(s.nextDouble());
                    }
                break;
                case "clear":
                    mal.clear();
                break;
                case "contains":
                    System.out.println(mal.contains(s.nextDouble()));
                break;
                case "sub":
                    i = s.nextInt();
                    double[] v = mal.sub(i, s.nextInt());
                    for (i = 0;i < v.length;i++) {
                        System.out.println(v[i]);
                    }
                break;
                case "list":
                    if (mal.isEmpty()) {
                        System.out.println("ArrayList is empty.");
                    }
                    for (i = 0;i < mal.size();i++) {
                        System.out.format(" [%2d] = %.4f%n", i, mal.get(i));
                    }
                break;
                case "quit":
                    running = false;
                break;
                default:
                    System.out.println("Invalid command!");
                    s.nextLine();
                case "h":
                case "?":
                case "help":
                    System.out.println("Help:");
                    System.out.println(" add <val>       - Add the value <val>.");
                    System.out.println(" add <idx> <val> - Add the value <val> at index <idx>.");
                    System.out.println(" clear           - Clears all elements of the list.");
                    System.out.println(" contains <val>  - Checks if the list contains <val>.");
                    System.out.println(" get <idx>       - Get the value of the element at index <idx>.");
                    System.out.println(" index <val>     - Get the index of the first element that has value <val>.");
                    System.out.println(" list            - Lists all elements in the list.");
                    System.out.println(" rem <val>       - Remove the first element that contains <val>.");
                    System.out.println(" rem <idx>       - Remove the element at index <idx>.");
                    System.out.println(" set <idx> <val> - Set the value at index <idx> to <val>.");
                    System.out.println(" size            - Get the number of elements in the list.");
                    System.out.println(" sub <f> <t>     - Get a sub-array from [<f>, <t>).");
                    System.out.println(" quit            - Quit the program.");
                break;
            }
        } while (running);
        s.close();
    }
      public myarraylist() {
        this(0);
    }

    public myarraylist(int size) {
      mValues = new double[size];
    }

    public myarraylist(int size, double defval) {  
       // using a for loop incrementally inserts "defval" into each element
    mValues = new double[size];
    for (int i = 0; i < size; i++){ 
         mValues[i] = defval;
      }    
    }

    public void add(double val) {
        // can call preceding add function
        add(size(), val);
    }

    public void add(int index, double val) {
       // this add function is more complicated:
       /*
        requires an if else statement to check if the index is grater than the size, to which it simply adds 
        the value using the previous add method.
        else, creates a new array of 1 greater size, copies the array from mValues
        and inserts the value at index. completes copying the values and sets the original array to the copy
       */
    if (index > size()){
        add(val);
    }
    else {
        double[] copy = new double[size() + 1];
    for (int i = 0; i < index; i++){
        copy[i] = mValues[i];
    }
    copy[index] = val;
    for (int i = index + 1; i < size() + 1; i++){
        copy[i] = mValues[i-1];
      }
    mValues = copy;
    }
}

    public void clear() {
      mValues = new double[0];
    }

    public int indexOf(double val) {
        // uses a nested if statement inside a for loop to check if the value at index i is 
        // equal to val then returns the index, else it returns -1
      for (int i = 0; i < size(); i++){
         if (mValues[i] == val){
            return i;
         }
      }
      return -1;
    }

    public boolean contains(double val) {
      if (indexOf(val) == -1){
          return false;
      }
      else{
          return true;
      }
    }

    public double get(int index) {
      return mValues[index]; 
    }

    public boolean isEmpty() {
     if (size() == 0)
         return true;
     
     else
        return false;
    }

    public void remove(int index) {
       /*
        double for loops iterate through copying the array, then removes the value at index and continues to copy.
        necessary to have index + 1 so it skips the index value
       */
         double[] copy = new double [size() - 1];

         for (int i = 0; i < index; i++){
            copy[i] = mValues[i];
         }
         for (int i = index + 1; i < size(); i++){
            copy[i - 1] = mValues[i];
         }
         mValues = copy;
    }

    public void remove(double val) {
        // easiest to use indexOf method instead of repeating code
     int index = indexOf(val);
     if (index != -1)
         remove(index);
    }

    public void set(int index, double val) {
      mValues[index] = val;
    }

    public int size() {
        return mValues.length;
    }

    public double[] sub(int first, int last) {
       // by creating the array and using a for loop beginning at the value "first"
       // you can then use a dummy variable incremented in the loop to set the new array 
       // to the values starting at "first"
      int size = last - first;
      double[] array = new double[size];
      for (int i = first; i < size; i++){
        int j = 0;
          array[j] = mValues[i];
          j++;
      }
      return array;
    }
    private double[] mValues;
}