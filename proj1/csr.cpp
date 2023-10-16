// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"
///////////////CSR Class Implementation///////////////
CSR::CSR()
{
    // set all values to either nullptr or 0
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;
    m_next = nullptr;
}

CSR::~CSR()
{
    // call clear
    clear();
}

CSR::CSR(const CSR &rhs)
{
    // if rhs is empty, return a empty object
    if (rhs.empty())
    {
        //setting all values to default values
        m_values = nullptr;
        m_col_index = nullptr;
        m_row_index = nullptr;
        m_nonzeros = 0;
        m_m = 0;
        m_n = 0;
        m_next = nullptr;
    }
    else
    {
        // set m_m, m_n, and nonzeros to rhs's values
        m_n = rhs.m_n;
        m_m = rhs.m_m;
        m_nonzeros = rhs.m_nonzeros;

        // define and set all values in m_row_index, m_values, m_col_index to zeros
        m_row_index = new int[m_m + 1]{0};
        m_values = new int[m_nonzeros]{0};
        m_col_index = new int[m_nonzeros]{0};

        // iterate through m_values and set the values from rhs.m_values
        for (int i = 0; i < m_nonzeros; i++)
        {
            m_values[i] = rhs.m_values[i];
        }

        // iterate through m_col_index and set the values from rhs.m_col_index
        for (int j = 0; j < m_nonzeros; j++)
        {
            m_col_index[j] = rhs.m_col_index[j];
        }

        // iterate through m_row_index and set the values from rhs.m_row_index
        for (int n = 0; n < m_m + 1; n++)
        {
            m_row_index[n] = rhs.m_row_index[n];
        }
    }
}

void CSR::clear()
{
    // set m_n, m_m, and m_nonzeros to zero
    m_n = 0;
    m_m = 0;
    m_nonzeros = 0;

    // delete m_values, m_col_index, m_row_index
    delete[] m_values;
    delete[] m_col_index;
    delete[] m_row_index;
}

bool CSR::empty() const
{
    // check if all values in the CSR object are empty and if thats true, return true
    if (m_n == 0 && m_m == 0 && !m_values && !m_col_index && !m_row_index)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CSR::compress(int m, int n, int array[], int arraySize)
{

    // check if m and n are good values, if not, dont run any code
    if (m <= 0 || n <= 0)
    {
        return;
    }

    // check if arraySize is equal, if not, dont run any code
    if (arraySize != (m * n))
    {
        return;
    }

    // once the checks are done, we can continue with compress

    // set m_m and m_n for the passed values
    m_m = m;
    m_n = n;

    // find all nonzeros
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] != 0)
        {
            m_nonzeros++;
        }
    }

    // initialize m_row_index, m_col_index, and m_values to zero
    m_row_index = new int[m_m + 1]{0};
    m_col_index = new int[m_nonzeros]{0};
    m_values = new int[m_nonzeros]{0};

    // create a index for m_col_index and m_values
    int index = 0;

    // create a index for m_row_index
    int rowIndex = 0;

    // iterate through arraySize
    for (int i = 0; i < arraySize; i++)
    {
        // if i % m_n is true, that means we entered a new row
        if (i % m_n == 0)
        {
            // increase rowIndex by one
            rowIndex++;

            // add the previous m_row_index to the current m_row_index
            m_row_index[rowIndex] += m_row_index[rowIndex - 1];
        }

        // if the array[i] is not zero
        if (array[i] != 0)
        {
            // add the value to m_values
            m_values[index] = array[i];

            // add the colm value to m_col_index
            m_col_index[index] = i % m_n;

            // increase the row index by one
            m_row_index[rowIndex] += 1;

            // increase index by one
            index++;
        }
    }
}

int CSR::getAt(int row, int col) const
{
    // if the row and colm passed arent in the correct range, throw runtime error
    if ((row > m_m || row < 0) || (col > m_n || col < 0))
    {
        throw(std::runtime_error("Exception Error, row or colms out of range"));
    }

    // find the row_start
    int row_start = m_row_index[row];

    // find where the row ends
    int row_end = m_row_index[row + 1];

    // iterate through the row_start and row_end
    for (int j = row_start; j < row_end; j++)
    {
        // if we find a matching col value, return the value at that location
        if (m_col_index[j] == col)
        {
            return m_values[j];
        }
    }

    // if that didnt work, that means the number isnt in our lists and therefore throw
    // a runtime error
    throw(std::runtime_error("Exception Error: Object is not in the list!"));
}
bool CSR::operator==(const CSR &rhs) const
{
    bool result = true;

    // check if both objects are empty
    if (rhs.empty() && this->empty())
    {
        return true;
    }

    // check if the rows, colms, and number of zeros are not equal, if true then return false
    if (rhs.m_n != this->m_n || rhs.m_m != this->m_m || rhs.m_nonzeros != this->m_nonzeros)
    {
        return false;
    }

    // check each of the values in both objects, if not equal make result false
    for (int i = 0; i < m_nonzeros; i++)
    {
        if (rhs.m_values[i] != this->m_values[i])
        {
            result = false;
        }
    }

    // check each colm value, if not equal make result false
    for (int j = 0; j < m_nonzeros; j++)
    {
        if (rhs.m_col_index[j] != this->m_col_index[j])
        {
            result = false;
        }
    }

    // check each row value, if not equal make result false
    for (int n = 0; n < rhs.m_m + 1; n++)
    {
        if (rhs.m_row_index[n] != this->m_row_index[n])
        {
            result = false;
        }
    }

    return result;
}

int CSR::sparseRatio()
{
    // find the number of zeros
    double numberOfZeros = (m_n * m_m) - m_nonzeros;

    // divide the number of zeros by the total amount of values
    double sR = numberOfZeros / (m_n * m_m);

    // multiply by 100 to make it a percent
    sR *= 100;

    // return the percent
    return sR;
}

void CSR::dump()
{
    cout << endl;
    if (!empty())
    {
        for (int i = 0; i < m_nonzeros; i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i = 0; i < m_nonzeros; i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i = 0; i < m_m + 1; i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

//////////////CSRList Class Implementation///////////////
CSRList::CSRList()
{
    // set m_head and m_size to default values
    m_head = nullptr;
    m_size = 0;
}

CSRList::CSRList(const CSRList &rhs)
{
    // set m_size and m_head to zero and nullptr
    this->m_size = 0;
    this->m_head = nullptr;


    //if rhs is
    if (rhs.empty())
    {
        return;
    }

    // end is for tracking the last node we want to go to
    int end = rhs.m_size;

    // iterate untill this object and rhs object are the same
    while (this->m_size != rhs.m_size)
    {
        // create a CSR object to iterate through with
        CSR *tail = rhs.m_head;

        // iterate until we reach the end and increase tail
        for (int i = 1; i < end; i++)
        {
            tail = tail->m_next;
        }

        // call insertAtHead with the tail
        this->insertAtHead(*tail);

        // decrease end
        end--;
    }
}

CSRList::~CSRList()
{
    // call clear
    clear();
}

bool CSRList::empty() const
{
    // if m_size is equal to 0, we know the List is empty
    if (m_size == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CSRList::insertAtHead(const CSR &matrix)
{
    // create newNode with the passed matrix
    CSR *newNode = new CSR(matrix);

    // make the newNode->m_next the current m_head
    newNode->m_next = m_head;

    // make m_head the new node
    m_head = newNode;

    // increase m_size by one
    m_size++;
}

void CSRList::clear()
{

    // iterate until m_size is zero
    while (m_size != 0)
    {
        // make a CSR temp that is the current m_head
        CSR *temp = m_head;

        // make a CSR object that is one ahead of temp
        CSR *next = m_head->m_next;

        // delete temp
        delete temp;

        // make m_head to next
        m_head = next;

        // decrease the size
        m_size--;
    }

    // set m_head to nullptr
    m_head = nullptr;
}

int CSRList::getAt(int CSRIndex, int row, int col) const
{
    // if the passed index is greater than m_size, throw runtime error
    if (CSRIndex > m_size)
    {
        throw(std::runtime_error("Exception Error: Object is not in the list!"));
    }

    // create a CSR temp to iterate through the LL
    CSR *temp = m_head;

    // iterate to the where the user wants to go to
    for (int i = 0; i < CSRIndex; i++)
    {
        temp = temp->m_next;
    }

    // call getAt with temp
    return temp->getAt(row, col);
}

bool CSRList::operator==(const CSRList &rhs) const
{
    // if both objects are empty, return true
    if (this->empty() && rhs.empty())
    {
        return true;
    }

    // if m_size and rhs.m_size are not equal, return false
    if (this->m_size != rhs.m_size)
    {
        return false;
    }
    // store the result of the function
    bool result;

    // thisCurrent and rhsCurrent are used to get nodes from both LL
    CSR *thisCurrent = this->m_head;
    CSR *rhsCurrent = rhs.m_head;

    // continue to iterate until we reach the end
    while (thisCurrent != nullptr && rhsCurrent != nullptr)
    {
        // store the result of the overloaded equality operator in result
        result = (*thisCurrent == *rhsCurrent);

        // if result ever is false, return false
        if (result == false)
        {
            return false;
        }

        // continue to the next node
        thisCurrent = thisCurrent->m_next;
        rhsCurrent = rhsCurrent->m_next;
    }

    // return result
    return result;
}

const CSRList &CSRList::operator=(const CSRList &rhs)
{
    // if rhs is empty
    if (rhs.empty())
    {
        // if the this object is not empty, clear it and return it
        if (!this->empty())
        {
            this->clear();
        }
        return *this;
    }

    // if rhs is not empty, clear the current object if its not empty
    if (!this->empty())
    {
        this->clear();
    }

    // end is for tracking the last node we want to go to
    int end = rhs.m_size;

    // iterate untill this object and rhs object are the same
    while (this->m_size != rhs.m_size)
    {
        // create a CSR object to iterate through with
        CSR *tail = rhs.m_head;

        // iterate until we reach the end and increase tail
        for (int i = 1; i < end; i++)
        {
            tail = tail->m_next;
        }

        // call insertAtHead with the tail
        this->insertAtHead(*tail);

        // decrease end
        end--;
    }

    //return this object
    return *this;
}

int CSRList::averageSparseRatio()
{
    //make CSR object to iterate through the LL
    CSR *curr = m_head;

    //ints to store the total amount of numbers and the sum of all the numbers
    double total = 0;
    double sum = 0;

    //iterate through the LL
    while (curr != nullptr)
    {
        //add the sparse ratio of the current node to sum
        sum += curr->sparseRatio();

        //increase total by one
        total++;

        //iterate to next node
        curr = curr->m_next;
    }

    //divide sum by the total number of numbers
    sum /= total;

    //return sum
    return sum;
}

void CSRList::dump()
{
    if (!empty())
    {
        CSR *temp = m_head;
        while (temp != nullptr)
        {
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;
}