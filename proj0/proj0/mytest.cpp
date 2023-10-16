// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
class Tester{
    public:

    bool errorCase(){
        bool result;

        Bingo obj1(-5, 5, MINVAL, MAXVAL);

        //call initCard, nothing should happen since it
        //should be an empty object
        obj1.initCard();

        //checks if m_card is populated or not
        if (obj1.m_card){
            //if yes, the obj was created and failed the test
            result = false;
        }else{
            //if no, the obj is empty and the test passed
            result = true;
        }

        return result;
    }

    bool edgeCase(){
        bool result;

        //create object with edge case of 2 and 5
        Bingo obj1(2,5,MINVAL,MAXVAL);
        obj1.initCard();

        //see if m_card is populated
        if (obj1.m_card){
            //if yes, result equals true
            result = true;
        }else{
            //if no, result equals false
            result = false;
        }

        return result;
    }

    bool normalCase(){
        bool result;

        Bingo obj1(10,5,MINVAL,MAXVAL);
        obj1.initCard();

        if (obj1.m_card){
            result = true;
        }else{
            result = false;
        }
        return result;
    }

    bool errorCaseTwo(){
        bool result;

        Bingo obj1(-5,-10, MINVAL, MAXVAL);
        obj1.initCard();

        //see if m_card is populated
        if (obj1.m_card){
            //if yes, that means the test failed
            result = false;
        }else{
            //if no, that means the test passed
            result = true;
        }
        return result;
    }

    bool normalCaseTwo(){
        //create normal object with rows = 10 and cols = 5
        Bingo obj1(10,5,MINVAL,MAXVAL);

        //fill the card with data
        obj1.initCard();


        return obj1.m_card;
    }

    bool reCreateErrorCase(){
        bool result;

        //create a normal object
        Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
        obj1.initCard();

        //clear the object for reCreateCard
        obj1.clear();
        
        //the bool reCreateCard returns is given to result
        result = obj1.reCreateCard(-5,-10,MINVAL,MAXVAL);

        //reCreateCard returns false if an empty object was made
        if (result == false){
            return true;
        }else{
            //returns false if reCreateCard did not create an empty object
            return false;
        }
    }

    bool reCreateNormalCase(){

        bool result;
        //create a normal object
        Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
        obj1.initCard();

        //clear the object for reCreateCard
        obj1.clear();
        
        //the bool reCreateCard returns is given to result
        result = obj1.reCreateCard(10,5,MINVAL,MAXVAL);
        obj1.initCard();

        //if result is true, that means reCreateCard created a new card
        if (result){
            return true;

        //if result is false, that means reCreateCard created an empty card
        }else{
            return false;
        }
    }

    bool initCardErrorCase(){

        bool result;
        //create a empty object
        Bingo obj1;

        //call initCard on empty object
        result = obj1.initCard();

        //if the object is empty, result will return false
        if (!(result)){
            return true;
        }else{
            return false;
        }
    }

    bool initCardNormalCase(){

        //create the object and call initCard()
        Bingo obj1(5,5,MINVAL,MAXVAL);
        obj1.initCard();

        //count is used to messure the amount of times a value was in the correct range
        int count = 0;

        //cSize is the range divided by m_numCols (which is 5)
        int cSize = (obj1.m_maxBallVal - obj1.m_minBallVal + 1)/obj1.m_numCols;

        //iterate through the number of rows
        for (int r = 0; r < obj1.m_numRows; r++){

            //iterate through the number of colms
            for (int c = 0; c < obj1.m_numCols; c++){

                //calculate the current minimum value (will increase after more iterations)
                int curMin = obj1.m_minBallVal + (c * cSize);
                //calculate the current maximum value (will increase after more iterations)
                int curMax = curMin + cSize - 1;

                //checks every value in m_card and sees if its in the correct range for each column
                if (obj1.m_card[r][c].getVal() >= curMin && obj1.m_card[r][c].getVal() <= curMax){
                    //increase count if its in the correct range
                    count++;
                }
            }
        }
        //if count is equal to the total number of cells, return true
        if (count == (obj1.m_numRows * obj1.m_numCols)){
            return true;
        }else{
            return false;
        }
    }

    bool playErrorCase(){
        int result;
        //create an empty object
        Bingo obj1(CARDROWS,CARDCOLS, MINVAL, MAXVAL);

        //use initCard
        obj1.initCard();

        //get a vector of balls;
        vector<int> balls = obj1.drawBalls();

        //call play but set numDraws to greater than MAXVAL
        result = obj1.play(100,balls);

        //if result equals 0, that means that play never ran
        if (result == 0){
            return true;
        }else{
            return false;
        }

    }

    bool assignmentEdge(){
        bool result = true;

        //make bingo object
        Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);

        //fill obj1 with data
        obj1.initCard();
        vector<int> balls = obj1.drawBalls();
        obj1.play(BALLS,balls);

        //create empty object
        Bingo obj2;

        //set obj2 to obj1
        obj2 = obj1;

        //iterate and check all m_card cells
        for (int i=0;i<obj1.m_numRows;i++){
            for (int j=0;j<obj1.m_numCols;j++){
                result = (obj2.m_card[i][j] == obj1.m_card[i][j]);
            }
        }

        //iterate and check all m_helper cells
        for (int i=0;i<obj1.m_helperSize;i++){
            result = (obj2.m_helper[i] == obj1.m_helper[i]);
        }

        //iterate and check all m_trackRows ints
        for (int i=0;i<obj1.m_numRows;i++){
            result = (obj2.m_trackRows[i] == obj1.m_trackRows[i]);
        }

        //iterate and check all m_trackCols ints
        for (int i=0;i<obj1.m_numCols;i++){
            result = (obj2.m_trackCols[i] == obj1.m_trackCols[i]);
        }

        //check if the min and max values are the same
        result = (obj2.m_minBallVal == obj1.m_minBallVal);
        result = (obj2.m_maxBallVal == obj1.m_maxBallVal);
        return result;
    }

    bool assignmentNormal(){
        bool result = true;

        //make bingo object
        Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);

        //fill obj1 with data
        obj1.initCard();
        vector<int> balls = obj1.drawBalls();
        obj1.play(BALLS,balls);

        //create new object
        Bingo obj2(10,10,MINVAL,MAXVAL);

        //set obj2 to obj1
        obj2 = obj1;

        //iterate and check all m_card cells
        for (int i=0;i<obj1.m_numRows;i++){
            for (int j=0;j<obj1.m_numCols;j++){
                result = (obj2.m_card[i][j] == obj1.m_card[i][j]);
            }
        }

        //iterate and check all m_helper cells
        for (int i=0;i<obj1.m_helperSize;i++){
            result = (obj2.m_helper[i] == obj1.m_helper[i]);
        }

        //iterate and check all m_trackRows ints
        for (int i=0;i<obj1.m_numRows;i++){
            result = (obj2.m_trackRows[i] == obj1.m_trackRows[i]);
        }

        //iterate and check all m_trackCols ints
        for (int i=0;i<obj1.m_numCols;i++){
            result = (obj2.m_trackCols[i] == obj1.m_trackCols[i]);
        }

        //check if the min and max values are the same
        result = (obj2.m_minBallVal == obj1.m_minBallVal);
        result = (obj2.m_maxBallVal == obj1.m_maxBallVal);

        return result;
    }
    
    private:
    
    /**********************************************
    * If we need helper functions to be reused in *
    *   test functions they can be declared here!
    **********************************************/
};
int main(){
    Tester tester;
    // Bingo obj1(CARDROWS,CARDCOLS,MINVAL,MAXVAL);
    // vector<int> balls = obj1.drawBalls();
    // if (obj1.initCard()){
    //     obj1.dumpCard();
    //     cout << "\ngame over after " << obj1.play(85,balls) << " hits!\n" << endl;
    //     obj1.dumpCard();
    // }

    if (tester.errorCase()){
        cout << "The error case passed" << endl;
    }else{
        cout << "The error case failed" << endl;
    }

    if (tester.edgeCase()){
        cout << "The edge case passed" << endl;
    }else{
        cout << "The edge case failed" << endl;
    }
    
    if (tester.normalCase()){
        cout << "The normal case passed" << endl;
    }else{
        cout << "The edge case failed" << endl;
    }

    if (tester.errorCaseTwo()){
        cout << "The error case two passed" << endl;
    }else{
        cout << "The error case two failed" << endl;
    }

    if (tester.normalCaseTwo()){
        cout << "The normal case two passed" << endl;
    }else{
        cout << "The error case two failed" << endl;
    }

    if (tester.reCreateErrorCase()){
        cout << "The reCreateCard error case passed" << endl;
    }else{
        cout << "The reCreateCard error case failed" << endl;
    }

    if (tester.reCreateNormalCase()){
        cout << "The reCreateCard normal case passed" << endl;
    }else{
        cout << "The reCreateCard normal case failed" << endl;
    }

    if (tester.initCardErrorCase()){
        cout << "The initCard error case passed" << endl;
    }else{
        cout << "The initCard error case failed" << endl;
    }

    if (tester.initCardNormalCase()){
        cout << "The initCard normal case passed" << endl;
    }else{
        cout << "The initCard normal case passed" << endl;
    }

    if (tester.playErrorCase()){
        cout << "The play error case passed" << endl;
    }else{
        cout << "The play error case failed" << endl;
    }

    if (tester.assignmentEdge()){
        cout << "The assignment edge case passed" << endl;
    }else{
        cout << "The assignment edge case failed" << endl;
    }

    if (tester.assignmentNormal()){
        cout << "The assignment normal case passed" << endl;
    }else{
        cout << "The assignment edge case failed" << endl;
    }

    return 0;
}