
/* 
Done By>> Anand Kothari


" Reading Input from bin.txt " 

In the bin packing problem, items of different weights (or sizes) must be packed into a finite number of bins each with the capacity Cin a way that minimizes the number of bins used.The decision version of the bin packing problem(deciding if objects will fit into <= k bins) isNP-complete.  There is no known polynomial time algorithm to solve the optimization version of the bin packing problem.  In this homework you will be examining three greedy approximation algorithms to solve the bin packing problem.

First-Fit:Put each item as you come to it into the first (earliest opened) bin into which it fits.  If there is no available bin then open a new bin.

First-Fit-Decreasing: First sort the items in decreasing order by size, then use First-Fit on the resulting list.

Example bin.txt:   The first line is the number of test cases, followed by the capacity of bins for that test case, the number of items and then the weight of each item.  You can assume that the weight of an item does not exceed the capacity of a bin for that problem.

3
10
6
5 10 2 5 4 4
20
19
9 10 2 1 7 3 3 3 3 14 6 5 2 8 6 4 6 2 6
10
20
4 4 4 4 4 4 4 4 4 4 6 6 6 6 6 6 6 6 6 6

Sample Output::
Test Case: 1 First Fit: 4, First Fit Decreasing: 3
Test Case: 2 First Fit: 6, First Fit Decreasing: 5
Test Case: 3 First Fit: 15, First Fit Decreasing: 10

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;
using std::greater;
using std::ifstream;
using std::vector;

vector<int> item_Weight_Vector;

int firstFit(int capacity, vector<int> item_Weights)
{
    vector<int> binCapLeft;
    binCapLeft.push_back(capacity);

    for (int i = 0; i < item_Weights.size(); i++)

    {
        bool canFit = true;

        for (int j = 0; j < binCapLeft.size(); j++)
        {
            if (item_Weights[i] <= binCapLeft[j])
            {
                binCapLeft[j] -= item_Weights[i];
                canFit = false;
                break;
            }
        }

        if (canFit == true)
        {
            binCapLeft.push_back(capacity);
            binCapLeft[binCapLeft.size() - 1] -= item_Weights[i];
        }
    }

    return binCapLeft.size();
}

int bestFit(int capacity, vector<int> item_Weights)
{
    vector<int> binCapLeft;
    binCapLeft.push_back(capacity);
    vector<int> bestbin;

    for (int i = 0; i < item_Weights.size(); i++)

    {
        bool cantFit = true;

        for (int j = 0; j < binCapLeft.size(); j++)
        {
            while (item_Weights[i] <= binCapLeft[j])
            {
                bestbin.push_back(j);
                i++;
            }

            if (bestbin.size() >= 1)
            {
                int k = max(bestbin.value);
                binCapLeft[k] -= item_Weights[i];
                cantFit = false;
                break;
            }
        }

        if (cantFit == true)
        {
            binCapLeft.push_back(capacity);
            binCapLeft[binCapLeft.size() - 1] -= item_Weights[i];
        }
    }

    return binCapLeft.size();
}

int firstFitD(int capacity, vector<int> item_Weights)
{
    sort(item_Weights.begin(), item_Weights.end(), greater<int>());
    int ffd = firstFit(capacity, item_Weights);
    return ffd;
}

ifstream infile("bin.txt");

int main()
{

    if (!infile)
    {
        cout << "File does not exist" << endl;
    }

    ifstream file("bin.txt");

    int data;

    int num_of_test;
    int capacity, item_weight = 0;
    int totalItems = 0;
    int testCasesCount = 0;
    while (file >> num_of_test)

    {

        for (int i = 0; i < num_of_test; i++)

        {

            file >> capacity;

            file >> totalItems;

            for (int i = 0; i < totalItems; i++)

            {

                file >> item_weight;

                item_Weight_Vector.push_back(item_weight);
            }
            testCasesCount++;
            int ff = firstFit(capacity, item_Weight_Vector);
            int ffd = firstFitD(capacity, item_Weight_Vector);
            item_Weight_Vector.clear();
            cout << "Test Case: "
                 << testCasesCount
                 << " First Fit: "
                 << ff
                 << ", First Fit Decreasing: "
                 << ffd
                 << endl;
        }
    }
    return 0;
}