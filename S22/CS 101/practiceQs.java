class practiceQs{
    public static void main(String[] args){
        // typecasting
        double d = 12.923; // double takes 8 bytes of memory, int takes 4
        int i = (int)d; // truncates instead of rounding
        // going from a double to an int is called "narrowing"
        System.out.println("when 'narrowing' from a double to an int, i = " + i);

        double p = i; 
        // "widening" or "automatic widening" does not need to be casted 
        // int takes up less space than a double, therefore java can fill in easily
        System.out.print("when 'widening' from an int to a double, p = " + p);


    }
}