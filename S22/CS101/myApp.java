import java.util.Scanner;
class myApp {
    public static void main (String[] args) {
        Scanner scan = new Scanner(System.in);

        // this is our class we created in Dog.java
        // our first object of type Dog.
        // object is named "iris" and I am using a constructor like w/ Scanner.

        Dog iris = new Dog();
        
        iris.mAge = 1;


        cat Davie = new cat();
        System.out.println("iris is: " + iris.mAge + " years old.");

        cat myCat = new cat(2);

        System.out.println(cat.getNumcats()); // because numCats is a static variable, & getNumCats is a static method,
                                              // I cant call this on just "Davie" 
                                              // all 3 cat objects share numCats
                                              // Davie & myCat cannot have different values of numCats because it is shared.
        

        iris.setWeight(45);

        System.out.println("iris weighs: " + iris.getWeight() + " lbs");
        double newWeight = iris.convertLBtoKG();
        System.out.println("iris weight: " + newWeight + " kgs");

        iris.setName("Iris Buziak"); 
        System.out.println("Dog's name is " + iris.getName());
        scan.close();
    }
}