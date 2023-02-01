class Dog {

    // BLUEPRINT for creating objects
    // A class is a  blueprint for an object. An object is 
    public int mAge; // m is in front to remind us it is a MEMBER variable
    /* this variable is public & therefore can be accessed by anyone
    & therefore can cause problems or make the program run in unexpected ways
    */

    // all member variables should be PRIVATE to protect the data.
    // public means it can be accessed in the main class

    private int weight, age; 
    private String name;


    // constructor is called when we make a new object of type Dog
    // bark will be printed, but java assigns a spot in memory for mAge & weight.
    public Dog() {
        System.out.println("A dog barks."); 
    }
    public Dog(int defaultWeight, int defaultAge, String defaultName) {
        weight = defaultWeight;
        age = defaultWeight;
        name = defaultName;

    }

    // Getters & Setters 
    // Change member variable by OUR rules or access variables by OUR rules

    public void setWeight(int weightFromMain) {
        if (weightFromMain > 0){
            weight = weightFromMain;
        }
        else {
            System.out.println("Weight must be a positive integer.");
        }
    }
    /*
    Might seem silly to simply return weight, however this allows us to keep the variable "weight" private
    and not allow users to access it, however still allows us to use the value of "weight"
    */
    public int getWeight() {
        return weight;
    }
    public void setName(String name) {
        // member variable to store a dog's name is called "name"
        // here, we also have argument for setName called "name"
        /* keyword "this" is used with naming conflicts, and we put it in front of member variable to 
         tell them apart. */
         // void keyword means nothing is returned
        this.name = name;
    }
        public String getName() {
            return this.name; // not necessary to use this here
        }
    
    // 1 lb = .453592 kgs
    public double convertLBtoKG() { // Can be done in a few different ways
        double returnVal;

        returnVal = weight*.453592;
        return returnVal;
    }

}