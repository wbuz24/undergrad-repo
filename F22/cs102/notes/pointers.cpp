/* Introduction to Pointers */
/* A pointer is a memory address of a variable. It is a construct that gives you
more control of a computer's memory.
We use the term "pointer" because the address can be thought of "pointing" to the variable.
A pointer identifies WHERE the variable is, rather than identifying what it's NAME is.

Pointers come in handy so we can store a piece of data just once, and reference it's
location if other objects need to use it. 
*/

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    /* DECLARATION: You declare a pointer as you would any other variable of that type, only you
    put an asterisk in front of the variable. (Note: 1st way the asterisk is used)
    If you want to declare multiple pointers, there must be an asterisk before EACH
    of the pointer variables.
    The following declares two pointers that point to integers, and two ordinary ints. */
    int *p1, *p2, v1, v2;
    v1 = 1;
    v2 = 2;
    //cout << v1 << v2 << endl;

    /* Note that you can also declare pointers with the asterisk next to the type, instead
    of the variable name. I personally find this more confusing. The same rule applies above - 
    p4 is actually a DOUBLE not a double pointer, but it's harder to tell written this way. */
    double* p3, p4;
    //p3 = 3.4;   // We can't do this - p3 isn't a double... it's a POINTER to a double. But the declaration is visually deceiving
    //p4 = 4.5;
    //cout << p4 << endl;

    /* The clearer way to declare is in front of the name. Genaric syntax:
    Type_Name *Variable_Name1, *Variable_Name2, ... ;
    */

    /* Let's init some pointers. */
    int i;      // integer
    int *ip;    // integer pointer

    /*
    SETTING: You can set a pointer's value by having it point to a piece of data that already exists. 
    You do that using the ampersand. (You can also set pointers equal to each other.)
    */
    /* See the code below: You can use the ampersand to determine the address of a variable, and you can
    then assign that address to a pointer variable.
    For example... */

    i = 55;
    ip = &i;

    /* This sets the variable 'ip' equal to a pointer that points to the variable 'i'. 
    Now, i is "the variable pointed to by ip". */

    /*
    ACCESS DATA: When you want to access what a pointer points to, you use the asterisk.
    When you want to access parts of an object that you would normally use a dot operator for (aka public fields
    or functions), but that member of the object is a pointer variable, you would instead use an 'arrow', ->
    NOTE: This is the 2nd way to use an asterisk. (First is declaration, up top.)
    When the asterisk is used this way, it is called "the deferencing operator" and the pointer
    variable is said to be "deferenced." */

    *ip = 42;   // deferencing the pointer 'ip'
    cout << "Value of i: " << i << endl;
    cout << "Value of ip *ip: " << *ip << endl;    // We have to derefence the pointer again to print out the value it's pointing to

    cout << "Value of ip: " << ip << endl;     // What happens if we don't? We print out the memory address it points to
    cout << endl;

    /* So to summarize, the * operator in front of a pointer variable produces the variable it points
    to. When used this way, the * operator is called the dereferencing operator.
    The operator & in front of an ordinary variable produces the address of that
    variable. The & operator is called the address-of operator. */

    cout << "Value of i: " << i << endl;    // Print the integer value - what is stored in i.
    cout << "Address of &i: " << &i << endl;    // Prints the address of i.
    cout << "Value of ip: " << ip  << endl;    // Prints the address stored in ip. This should be the same as &i.
    cout << "Value stored in  *i: " << *ip << endl;    // Prints value that's stored in i. Should be the same as line 74.
    cout << "Address of pointer variable itself (&ip): " << &ip << endl;    // This is the address of the pointer variable itself. 
    //cout << endl;

    /* If I change i, then *ip will automatically change. If I change *ip, then i will
    automatically change. Currently i = 42. */
    //cout << "Previous value of i: " << i << " and previous value of *ip: " << *ip << endl;
    i = 100;
    //cout << "i = " << i << " and *ip = " << *ip << endl;
    *ip  = 200;
    //cout << "i = " << i << " and *ip = " << *ip << endl;
    //cout << endl;

    
    /* NEW
    The "new" keyword creates a new dynamic variable of a specified type
    and returns a pointer that points to this new variable.
    The generic way to do this:
    MyType *p;
    p = new MyType;
    OR
    MyClass *p;
    p = new MyClass();

    Think of it as creating a "nameless" variable that we can refer to
    via a pointer. Here's an example with an int.
    */
    int *pointer1, *pointer2;
    pointer1 = new int;

    cout << "Give me an int: ";
    cin >> *pointer1;
    cout << "You gave me " << *pointer1 << " and it's address is: " << pointer1 << endl;
    /*
    This creates a new dynamic variable of MyType.
    In C++, if there is not enough memory available to create the new variable,
    the new operation will terminate the program.

    This is called a dynamic variable because these variables are created
    and destroyed while the program is running.
    */

    /* What happens when we run the code below? I'm commenting it out because it's an error. */
    //cout << "Another int: ";
    //cin >> *pointer2;
    //cout << "You gave me " << *pointer2 << " and it's address is: " << pointer2 << endl;

    /*
    A SEG FAULT! Aka we didn't allocate memory for the nameless integer
    being pointed to by pointer2.
    The program quits immediately.
    Comment out to fix.
    */

    /* If I reuse pointer1 to make an new integer... then I've completely lost the 
    user input originally stored. We don't have a hold on that input anymore (aka we let go of the old address
    to create a new one), and the int at that address was nameless.
    This is called a MEMORY LEAK. It's a bit easier to see with more complicated examples than integers.
    The below creates a memory leak (remember lines 108-09).
    */
    pointer1 = new int;
    *pointer1 = 42;
    //cout << "Loosing the old input with a memory leak. *pointer1 is now " << *pointer1 << endl;

    /*
    DELETE: To destroy a dynamic variable, we use the "delete" keyword.
    It eliminates the dynamic variable and returns the memory back for re-use.
    EX:
    delete p;

    AFTER the delete call, the value of p is undefined (i.e. we have no idea where
    it's pointing.) If some other pointer variable was also pointing to p, let's say
    p2, then it's ALSO undefined.
    If you try to de-reference p after the delete call, (*p), it will be totally
    unpredictable.
    
    Both p and p2 are what we call DANGLING POINTERS.
    A dangling pointer is a non-NULL pointer which points to already free memory.

    After you call delete, you should treat p and p2 as uninitialized variables.
    You can set them to NULL to make it clear in your code. */

    delete pointer1;

}
