class Arithmetic {
    public static void main(String[] args) {
        /* in order to use exponent operator,
        you must use "Math.pow(x, e);"
        */
        System.out.println(3 + 6);
        System.out.println(3 + 6 - 2 * 4 + 5); // evaluated through pemdas
        // division is different in java, 
        // SPECIFICALLY with integers
        System.out.println(3 / 6); // outputs 0
        // Since both 3 and 6 are integers, java gives us an integer output
        // therefore, it does not round, but rather cuts off the excess
        System.out.println(3.0 / 6); // by changing one to a double, you change both

        // "%" or "mod" is essentially the remainder
        System.out.println(9 % 6); // 1 & 3/6 is 9/6, giving a remainder of 3
        // returns the numerator of a fraction
        System.out.println(1 % 4); // returns 1

        // to summarice: integer divison and mod are new 
        // other arithmetic operations act regularly

        // Prefix and Postfix increment/decrement operators
        // These are unary operators meaning you only need one variable
        // to operate on it
        System.out.println("Prefix and Postfix increment/decrement ops: "); 
        int i = 10;
        int j = 20;

        System.out.println("i = " + i + " and j = " + j);
        i++; // same as i = i + 1; & is the postfix

        System.out.println("i = " + i + " and j = " + j);

        // the key is assignment & increment
        // assigment is i =
        // increment is i + 1

        i = j++; // Getting the value of j and assigning it to i & incrementing by 1
        // prints out 20, because j is assigned first, then j becomes 21

        i = ++j; // this is prefix
        // increment happens first, then assignment. printing 21
        
        // Summarize == On POSTFIX, we do ASSIGNMENT first, then INCREMENT (i = j++)
        //           == On PREFIX, we do INCREMENT first, then ASSIGNMENT ( i = ++j)




    }
}