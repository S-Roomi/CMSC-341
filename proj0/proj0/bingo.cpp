// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
Bingo::Bingo(){

    //set all values to empty or nullptr
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr;
    m_card = nullptr;

}

Bingo::Bingo(int rows, int columns, int min, int max){

    //cRange used to calculate if the range of ball values passed is correct
    int cRange = ((max - min)+1)%columns;

    //if rows are in the correct range and columns is 5 and the min-max range is correct
    //create an object with the passed values
    if ((rows >= 2 && rows <= 15) && (columns == 5) && (cRange == 0)){

        //set the values to the passed ones
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;

        //initialize m_trackCols and m_trackRows
        m_trackCols = new int[m_numCols](); 
        m_trackRows = new int[m_numRows](); 

        //set m_helperSize
        m_helperSize = m_maxBallVal+1;

        //initialize m_helper and m_card
        m_helper = new Cell[m_helperSize]; 
        m_card = new Cell*[m_numRows]; 


    }else{
        //the values passed weren't correct so create an empty object
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;
        m_maxBallVal = 0;
        m_trackCols = nullptr;
        m_trackRows = nullptr;
        m_helper = nullptr;
        m_card = nullptr;
    }
    
}

bool Bingo::reCreateCard(int rows, int columns, int min, int max){

    //if m_card was not cleared pior, that means clear was not called
    //so call it now
    if (!m_card){
        clear();
    }

    //cRange used to calculate if the range of ball values passed is correct
    int cRange = ((max - min)+1)%columns;

    if ((rows >= 2 && rows <= 15) && (columns == 5) && (cRange == 0)){
        
        //set the values to the passed ones
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;

        //initialize m_trackCols and m_trackRows
        //used () to make all values zero
        m_trackCols = new int[m_numCols] (); 
        m_trackRows = new int[m_numRows] (); 

        //set m_helperSize
        m_helperSize = m_maxBallVal+1;

        //initialize m_helper and m_card
        m_helper = new Cell[m_helperSize]; 
        m_card = new Cell*[m_numRows]; 

        //return true since the object was made correctly
        return true;
    }else{
        //the values passed weren't correct so create an empty object
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;
        m_maxBallVal = 0;
        m_trackCols = nullptr;
        m_trackRows = nullptr;
        m_helper = nullptr;
        m_card = nullptr;
        
        //return false since the object wasn't made correctly
        return false;
    }
}

Bingo::~Bingo(){
    //call clear
    clear();
}

void Bingo::clear(){
    //delete m_trackCols and set the pointer as nullptr
    delete[] m_trackCols;
    m_trackCols = nullptr;

    //delete m_trackRows and set the pointer as nullptr
    delete[] m_trackRows;
    m_trackRows = nullptr;

    //delete m_helper
    delete[] m_helper;
    
    //iterate throught m_card and delete all arrays inside of it
    for (int i = 0; i < m_numRows; i++){
        delete[] m_card[i];
    }

    //delete m_card
    delete[] m_card;
    
    //set these values as empty
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
    
}

bool Bingo::initCard(){

    //if an empty obj calls initCard, return false
    if (!m_card){
        return false;
    }

    //calculate the size of each column
    int cSize = (m_maxBallVal - m_minBallVal + 1)/m_numCols;

    //iterate through number of rows
    for (int r = 0; r < m_numRows; r++){
        
        //create a new array at each row
        m_card[r] = new Cell[m_numCols];

        //iterate through number of columns
        for (int c = 0; c < m_numCols; c++){

            //find the current minimum and maximum value for the current iteration
            int curMin = m_minBallVal + (c * cSize);
            int curMax = curMin + cSize - 1;

            //create a Random class with the new curMin and curMax
            Random random(curMin, curMax, SHUFFLE);

            //create a list with the size of curMax - curMin - 1
            int rList[curMax-curMin-1];

            //send the random list into getShuffle
            random.getShuffle(rList);


            //set the row with r, col with c, and value with a random value from rList
            m_card[r][c].setRow(r);
            m_card[r][c].setCol(c);
            m_card[r][c].setVal(rList[r]);

            //set the row with r, col with c, and value with a random value from rList
            m_helper[rList[r]].setRow(r);
            m_helper[rList[r]].setCol(c);
            m_helper[rList[r]].setVal(rList[r]);

        }
    }
    //if everything worked correctly, return true
    return true;
}

vector<int> Bingo::drawBalls(){
    //make random class call rand and set it to SHUFFLE
    Random rand = Random(m_minBallVal, m_maxBallVal, SHUFFLE);

    //created a vector call randBalls
    vector<int> randBalls;

    //Shuffle randBalls
    rand.getShuffle(randBalls);

    //return randBalls
    return randBalls;
}

int Bingo::play(int numDraws, vector<int> rndBalls){

    //if an empty card calls play, return 0;
    if (!m_card){
        return 0;
    }
    //checks if numDraws is greater than m_maxBallVal
    if (numDraws > m_maxBallVal){
        return 0;
    }

    
    bool isOver = false;

    //check if numDraws is equal to the max ball value
    bool isEqual = (numDraws == m_maxBallVal);

    //numReplace is used to count the number of replacements made
    int numReplaced = 0;


    while (isOver == false){

        //iterate through numDraws
        for (int i = 0; i < numDraws; i++){
            
            //grab a random number from the passed vector
            int randNum = rndBalls.at(i);
            
            //if the random number is in m_helper  
            if (m_helper[randNum].isEmpty() == false){
                //change the cell in m_card to EMPTYCELL
                m_card[m_helper[randNum].getRow()][m_helper[randNum].getCol()].setVal(EMPTYCELL);

                //increase the value in m_trackRows by 1
                m_trackRows[m_helper[randNum].getRow()] += 1;

                //increase the value in m_trackCols by 1
                m_trackCols[m_helper[randNum].getCol()] += 1;


                //increase numReplaced by 1
                numReplaced++;
            }

            //if isEqual is true, the game will end after the finish after the first
            //row or column is filled with EMPTYCELL
            if (isEqual){
                for (int j = 0; j < m_numRows; j++){

                    //if m_trackRows[j] is equal to m_numCols, the game is over since the row was filled
                    if (m_trackRows[j] == m_numCols){

                        isOver = true;

                        return numReplaced;
                    }
                }
                
                for (int n = 0; n < m_numCols; n++){

                    //if m_trackCols[n] is equal to m_numRows, the game is over since the colm was filled
                    if (m_trackCols[n] == m_numRows){

                        isOver = true;

                        return numReplaced;
                    }
                }
            }
        }
        isOver = true;
    }
    return numReplaced;
}

const Bingo & Bingo::operator=(const Bingo & rhs){
    //clear the current object
    this->clear();

    //if rhs is an empty object, return this since its now an empty object as well
    if (!rhs.m_card){
        return *this;
    }

    //set these values to the ones from rhs
    m_numCols = rhs.m_numCols;
    m_numRows = rhs.m_numRows;
    m_maxBallVal = rhs.m_maxBallVal;
    m_minBallVal = rhs.m_minBallVal;

    //add new dynamic memeory to m_trackCols and m_trackRows
    m_trackCols = new int[m_numCols] ();
    m_trackRows = new int[m_numRows] ();

    //get m_helper size from rhs
    m_helperSize = rhs.m_helperSize;

    //create a new m_helper
    m_helper = new Cell[m_helperSize];

    //create a new m_card
    m_card = new Cell*[m_numRows];

    //iterate through m_trackCols and set the values to the one from rhs
    for (int i = 0; i < m_numCols; i++){
        m_trackCols[i] = rhs.m_trackCols[i];
    }

    //iterate through m_trackRows and set the values to the one from rhs
    for (int i = 0; i < m_numRows; i++){
        m_trackRows[i] = rhs.m_trackRows[i];
    }

    //iterate through m_helper and add the row, col, and value from the rhs m_helper
    for (int i = 0; i < m_helperSize; i++){
        m_helper[i].setCol(rhs.m_helper[i].getCol());
        m_helper[i].setRow(rhs.m_helper[i].getRow());
        m_helper[i].setVal(rhs.m_helper[i].getVal());
    }


    //iterate through m_card and set the values of the cell to the ones from rhs.m_card
    for (int r = 0; r < m_numRows; r++){
        m_card[r] = new Cell[m_numCols];
        for (int c = 0; c < m_numRows; c++){
            m_card[r][c].setRow(rhs.m_card[r][c].getRow());
            m_card[r][c].setCol(rhs.m_card[r][c].getCol());
            m_card[r][c].setVal(rhs.m_card[r][c].getVal());
        }
    }
    
    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";    
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
}