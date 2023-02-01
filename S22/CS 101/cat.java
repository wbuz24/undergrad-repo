/* Access Protection 
    private - can ONLY access data within the class
        typically member variables are private. (data integrity/security)
    public - anyone can access
        typically methods are public
        can set private data or access private data via public methods
            that take into account the security or rules data should follow
    (protected) - used in inheritance
        ex. If we created an Animal class, we could have a "dog" & "cat" class inherit from 
            Animal, which means they could "inhert" the Animal blueprint & make it their own.
    (default)
 constructors - overloading
 
 static keyword

*/

class cat{
    // member variables (private variables)
    private int age;
    private String catName, owner;
    private double weight;

    // constructor - we are "overloading" the constructor, because we have multiple ways to call it
    // If we didn't have any constructor, Java would make one for us.
    // It would look like line 29 & 30 (and nothing in line 33). 
    // essentially assigns memory for the object created

    // static - only ONW spot in memory, no matter how many objects we create.
    // in myApp, we create 3 cats. each cat object in myapp will have it's own age, catName, weight, owner
    // with numCats being STATIC - they will share it. only 1 will be used for all 3 cat objects

    private static int numCats;

    static { // static block
        numCats = 0; // all cats share this piece of memory
    }


    public cat() {
        System.out.println("A cat meows."); 
        numCats++;
    }

    public cat(String catName) {
        this.catName = catName; // this. removes naming conflict between parameter name & member variable
        numCats++;
    }

    public cat(int givenAge) {
        age = givenAge;
        numCats++;
    }
    public cat(int defaultWeight, int defaultAge, String defaultName, String defaultOwner) {
        weight = defaultWeight;
        age = defaultWeight;
        catName = defaultName;
        owner = defaultOwner;
        numCats++;
    }
    // must create a function to access number of cat objects created.
    // this is public because methods are typically public & we want myApp to call this
    // this is static because it will only access static variables
    // think of "static" as referred to all objects instead of individual ones.

    public static int getNumCats() {
        return numCats;
    }
}