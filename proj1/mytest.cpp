// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"

class Tester
{
public:
    bool compressNormalCase()
    {
        bool result = true;

        // create CSR object
        CSR test;

        // make array to pass to compress
        int testArray[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};

        // compress the array
        test.compress(4, 6, testArray, 24);

        // see if m_nonzeros is exactly 8
        if (test.m_nonzeros != 8)
        {
            result = false;
        }

        // test to see if the right value is in the right position
        if (test.getAt(2, 1) != 50)
        {
            result = false;
        }

        // return the result
        return result;
    }

    bool compressErrorCaseOne()
    {
        // create CSR object
        CSR test;

        // make array to pass to compress
        int testArray[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};

        // compress the array
        // make rows equal to 3 and colms equal to 5 which is incorrect for a matrix of 24 size
        test.compress(3, 5, testArray, 24);

        // if the CSR object is empty, return true
        if (test.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool compressErrorCaseTwo()
    {

        // create CSR object
        CSR test;

        // make array to pass to compress
        int testArray[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};

        // compress the array with 0 rows and 0 colms
        test.compress(0, 0, testArray, 24);

        // if test is not empty, return false
        if (!test.empty())
        {
            return false;
        }

        return true;
    }

    bool EqualityNormalCase()
    {
        int result;

        int testArray[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};

        // create two objects
        CSR test1;
        CSR test2;

        // compress the same data into both objects
        test1.compress(4, 6, testArray, 24);
        test2.compress(4, 6, testArray, 24);

        // result will store the value returned from the overloaded operator
        result = (test1 == test2);

        return result;
    }

    bool EqualityEdgeCase()
    {
        int result;

        // Create two empty objects
        CSR test1;
        CSR test2;

        // result will store the value returned from the overloaded operator
        result = (test1 == test2);

        return result;
    }

    bool getAtErrorCase()
    {
        try
        {
            // create test array
            int testArray[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};

            // create two objects
            CSR test1;
            CSR test2;

            // compress the same data into both objects
            test1.compress(4, 6, testArray, 24);

            // will throw an runtime error
            test1.getAt(100, 100);
        }
        // catch the error and return true
        catch (exception &e)
        {
            return true;
        }
        return false;
    }

    bool copyConstructorNormalCase()
    {
        bool result;

        // test array
        int testArray1[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};

        // create first CSR object
        CSR aCSR;

        // compress testArray1 into aCSR
        aCSR.compress(4, 6, testArray1, 24);

        // call copy constructor for bCSR
        CSR bCSR(aCSR);

        // use overloader equality operator to see if the two are equal
        result = (aCSR == bCSR);

        // return result
        return result;
    }

    bool copyConstructorEdgeCase()
    {
        bool result;

        // create first CSR object
        CSR aCSR;

        // call copy constructor for bCSR
        CSR bCSR(aCSR);

        // use overloader equality operator to see if the two are equal
        result = (aCSR == bCSR);

        // return result
        return result;
    }

    bool csrListEqualityNormalCase()
    {
        bool result;

        // create test array
        int testArray1[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};
        int testArray2[] = {0, 0, 0, 0, 100, 200, 0, 0, 300};

        // create two CSR objects
        CSR test1;
        CSR test2;

        // compress the same data into both objects
        test1.compress(4, 6, testArray1, 24);
        test2.compress(3, 3, testArray2, 9);

        // create CSRList object
        CSRList bCSRList;

        // add the CSR objects to bCSRList
        bCSRList.insertAtHead(test1);
        bCSRList.insertAtHead(test2);

        // create second CSRList object
        CSRList cCSRList;

        // add the CSR objects to cCSRList
        cCSRList.insertAtHead(test1);
        cCSRList.insertAtHead(test2);

        // call overloaded operator
        result = (cCSRList == bCSRList);
        // return result
        return result;
    }

    bool csrListEqualityEdgeCase()
    {
        bool result;

        // create CSRList object
        CSRList bCSRList;

        // create second CSRList object
        CSRList cCSRList;

        // call overloaded operator
        result = (cCSRList == bCSRList);

        // return result
        return result;
    }

    bool csrListAssignmentNormalCase()
    {
        bool result;

        // create test array
        int testArray1[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};
        int testArray2[] = {0, 0, 0, 0, 100, 200, 0, 0, 300};

        // create two CSR objects
        CSR test1;
        CSR test2;

        // compress the same data into both objects
        test1.compress(4, 6, testArray1, 24);

        test2.compress(3, 3, testArray2, 9);

        // create CSRList object
        CSRList bCSRList;

        // add the CSR objects to bCSRList
        bCSRList.insertAtHead(test1);
        bCSRList.insertAtHead(test2);

        // create second CSRList object
        CSRList cCSRList;

        // call overloaded assignment operator
        cCSRList = bCSRList;

        // call overloaded Equality operator
        result = (bCSRList == cCSRList);

        // return result
        return result;
    }

    bool csrListAssignmentEdgeCase()
    {
        bool result;

        // create test array
        int testArray1[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};
        int testArray2[] = {0, 0, 0, 0, 100, 200, 0, 0, 300};
        // create two CSR objects
        CSR test1;
        CSR test2;

        // compress the same data into both objects
        test1.compress(4, 6, testArray1, 24);

        test2.compress(3, 3, testArray2, 9);

        // create CSRList object
        CSRList bCSRList;

        // add the CSR objects to bCSRList
        bCSRList.insertAtHead(test1);
        bCSRList.insertAtHead(test2);

        // create second CSRList object
        CSRList cCSRList;

        // call overloaded assignment operator on bCSRList, should make bCSRList an empty object
        bCSRList = cCSRList;

        // call overloaded Equality operator
        result = (bCSRList == cCSRList);

        // return result
        return result;
    }

    bool csrListGetAtNormalCase()
    {
        try
        {
            // create test array
            int testArray1[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};
            int testArray2[] = {0, 0, 0, 0, 100, 200, 0, 0, 300};
            // create two CSR objects
            CSR test1;
            CSR test2;

            // compress the same data into both objects
            test1.compress(4, 6, testArray1, 24);

            test2.compress(3, 3, testArray2, 9);

            // create CSRList object
            CSRList bCSRList;

            // add the CSR objects to bCSRList
            bCSRList.insertAtHead(test1);
            bCSRList.insertAtHead(test2);

            // call getAt for value 59 in testArray1
            int value = bCSRList.getAt(1, 2, 2);

            if (value != 59)
            {
                return false;
            }

            return true;
        }
        // in case that an run time error gets thrown
        // catch it and return false
        catch (exception &e)
        {
            return false;
        }
    }

    bool csrListGetAtErrorCase()
    {
        try
        {
            // create CSRList object
            CSRList bCSRList;

            // call getAt
            bCSRList.getAt(1, 2, 2);

            // this should never run and if it does, return false
            return false;
        }
        // catch run time error and return true
        catch (exception &e)
        {
            return true;
        }
    }

    bool csrListCopyConstrutorNormalCase()
    {
        bool result;
        // create test array
        int testArray1[] = {0, 0, 0, 0, 40, 0, 0, 69, 13, 0, 0, 0, 0, 50, 59, 0, 0, 0, 0, 0, 0, 80, 90, 91};
        int testArray2[] = {0, 0, 0, 0, 100, 200, 0, 0, 300};
        // create two CSR objects
        CSR test1;
        CSR test2;

        // compress the same data into both objects
        test1.compress(4, 6, testArray1, 24);

        test2.compress(3, 3, testArray2, 9);

        // create CSRList object
        CSRList bCSRList;

        // add the CSR objects to bCSRList
        bCSRList.insertAtHead(test1);
        bCSRList.insertAtHead(test2);

        // create new object with copy constructor
        CSRList cCSRList(bCSRList);

        // see if bCSRList is equal to cCSRList
        result = (bCSRList == cCSRList);

        return result;
    }

    bool csrListCopyConstrutorEdgeCase()
    {
        bool result;

        //create CSRList object
        CSRList bCSRList;

        //call copy constructor with empty object
        CSRList cCSRList(bCSRList);

        //check if both are same
        result = (bCSRList == cCSRList);

        return result;
    }
};
// this program presents a sample usage of project 1
int main()
{
    try
    {
        Tester tester;

        if (tester.compressNormalCase())
        {
            cout << "compressNormalCase passed!" << endl;
        }
        else
        {
            cout << "compressNormalCase failed!" << endl;
        }

        if (tester.compressErrorCaseOne())
        {
            cout << "compressErrorCaseOne passed!" << endl;
        }
        else
        {
            cout << "compressErrorCaseOne failed!" << endl;
        }

        if (tester.compressErrorCaseTwo())
        {
            cout << "compressErrorCaseTwo passed!" << endl;
        }
        else
        {
            cout << "compressErrorCaseTwo failed!" << endl;
        }

        if (tester.EqualityNormalCase())
        {
            cout << "EqualityNormalCase passed!" << endl;
        }
        else
        {
            cout << "EqualityNormalCase failed!" << endl;
        }

        if (tester.EqualityEdgeCase())
        {
            cout << "EqualityEdgeCase passed!" << endl;
        }
        else
        {
            cout << "EqualityEdgeCase failed!" << endl;
        }

        if (tester.getAtErrorCase())
        {
            cout << "getAtErrorCase passed!" << endl;
        }
        else
        {
            cout << "getAtErrorCase failed!" << endl;
        }

        if (tester.copyConstructorNormalCase())
        {
            cout << "copyConstructorNormalCase passed!" << endl;
        }
        else
        {
            cout << "copyConstructorNormalCase failed!" << endl;
        }

        if (tester.copyConstructorEdgeCase())
        {
            cout << "copyConstructorEdgeCase passed!" << endl;
        }
        else
        {
            cout << "copyConstructorEdgeCase failed!" << endl;
        }

        if (tester.csrListEqualityNormalCase())
        {
            cout << "csrListEqualityNormalCase passed!" << endl;
        }
        else
        {
            cout << "csrListEqualityNormalCase failed!" << endl;
        }

        if (tester.csrListEqualityEdgeCase())
        {
            cout << "csrListEqualityEdgeCase passed!" << endl;
        }
        else
        {
            cout << "csrListEqualityEdgeCase failed!" << endl;
        }

        if (tester.csrListAssignmentNormalCase())
        {
            cout << "csrListAssignmentNormalCase passed!" << endl;
        }
        else
        {
            cout << "csrListAssignmentNormalCase failed!" << endl;
        }

        if (tester.csrListAssignmentEdgeCase())
        {
            cout << "csrListAssignmentEdgeCase passed!" << endl;
        }
        else
        {
            cout << "csrListAssignmentEdgeCase failed!" << endl;
        }

        if (tester.csrListGetAtNormalCase())
        {
            cout << "csrListGetAtNormalCase passed!" << endl;
        }
        else
        {
            cout << "csrListGetAtNormalCase failed!" << endl;
        }

        if (tester.csrListGetAtErrorCase())
        {
            cout << "csrListGetAtErrorCase passed!" << endl;
        }
        else
        {
            cout << "csrListGetAtErrorCase error!" << endl;
        }

        if (tester.csrListCopyConstrutorNormalCase())
        {
            cout << "csrListCopyConstrutorNormalCase passed!" << endl;
        }
        else
        {
            cout << "csrListCopyConstrutorNormalCase failed!" << endl;
        }

        if (tester.csrListCopyConstrutorEdgeCase())
        {
            cout << "csrListCopyConstrutorEdgeCase passed!" << endl;
        }
        else
        {
            cout << "csrListCopyConstrutorEdgeCase failed!" << endl;
        }
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
