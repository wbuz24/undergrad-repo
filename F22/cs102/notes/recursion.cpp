#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector <int> data, int x);

int main(void)
{
    vector <int> data = { 2, 3, 4, 10, 40 };
    int x = 10;
    /* Hint: to make it recursive, adding parameters... specifically 2
       parameters... will help. */
    int result = binarySearch(data, x);
    (result == -1) ? cout << "Element is not present in array"
        : cout << "Element is present at index " << result;
    cout << endl;
    return 0;
}

int binarySearch(vector <int> arr, int x)
{
    vector <int> copy;
    int l = 0;
    int r = arr.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;

        // Check if x is present at midpoint
        if (arr[m] == x){
            return m;
        }
        // If x greater, ignore left half of vector
        if (arr[m] < x){
            l = m + 1;
            for (int i = l; i < arr.size(); i++) {
                copy.push_back(arr[i]);
            }
            return binarySearch(copy, x);
            // If x is smaller, ignore right half of vector
        }
        else{
            r = m - 1;
            for (int i = 0; i < r; i++){
                copy.push_back(arr[i]);
            }
            return binarySearch(copy, x);
        }


        /* Element was not in the vector. */
        return -1;
    }
}

