#include <iostream>

int main()
{
    int arr[][2] = {{1, 2}, {3, 4}};

    int ***ptrArr;

    ptrArr = new int **[2];
    for (int i = 0; i < 2; i++)
        ptrArr[i] = new int *[2];

    ptrArr[0][0] = &arr[1][1];
    ptrArr[0][1] = &arr[1][0];
    ptrArr[1][0] = &arr[0][1];
    ptrArr[1][1] = &arr[0][0];

    std::cout << *ptrArr[0][0] << std::endl;
    
    // Deallocate the memory for ptrArr
    for (int i = 0; i < 2; i++)
        delete[] ptrArr[i];
    delete[] ptrArr;


    return 0;
}
