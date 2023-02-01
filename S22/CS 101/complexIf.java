class complexIf{
    public static void main(String[] args){

        boolean condition1 = true;
        boolean condition2 = true;
        double grade = 92;
        char gradenum;
            if (grade >= 90){
                gradenum = 'A';
            }
            if (grade >= 80 && grade <= 89.999); {
                gradenum = 'B';
            }
            if (condition1 && condition2) {
            /* BOTH condition1 (AND or "&&") condition2 must
               be true in order to execute the following code

               "\\" is the "OR" operator

               && is higher than || on order of operations
               however, parenthesis can be used normally to trump
               order.
            */   
            // execute code
            System.out.println("Both conditions have been satisfied");
            }
            if (grade >= 0 && grade <= 100){
                System.out.println("This is a valid grade: " + grade);
            }
            else {
                System.out.println("This is an invalid grade");
            }
            if (condition1 && condition2 && grade>=0){
              System.out.println("Jackpot Jeffie!!");
            }
            else{
              System.out.println("Better luck next time, Jieftain");
            }
        
            if (gradenum == 'A' || gradenum == 'B'){
                System.out.println("Solid work, governor: " + gradenum);
            }
            
    }  
}