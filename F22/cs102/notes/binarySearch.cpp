#include <vector>

using namespace std;

void binarySearch(vector <int> A, int n, int x) {
    int lower = 1;
    int upper = n;
    
    bool xfound = true;

   while (xfound) {
        if (upper < lower) {
            cout << "x does not exist" << endl;
            xfound = false;
        }
            int mid = lower + (upper - lower) / 2;
        

        if (A[mid] < x) {
            lower = mid + 1;
        }

        if (A[mid] > x) {
            upper = mid - 1;
        }

        if (A[mid] == x) {
            cout << "x found at location midpoint" << endl;
            xfound = false;
        }
   }
}
