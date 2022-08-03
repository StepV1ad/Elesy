#include <string>
#include <vector>
#include <fstream>  // ������ � �������
#include <iostream>
#include <cstdlib> // ��� ��������� ��������� �����
#include <ctime>

using namespace std;
#define RAND_ARR_SIZE 100 // ���������� ����� � ������

void quickSort(int*& arr, int low, int high, int type)
{
    int mid, count;
    int l = low, h = high;
    mid = arr[(l + h) / 2]; //���������� �������� ��������
    do
    {
        if (type == 0) {
            while (arr[l] < mid)
                l++;
            while (arr[h] > mid)
                h--;
        }
        else if (type == 1) {
            while (arr[l] > mid)
                l++;
            while (arr[h] < mid)
                h--;
        }
        if (l <= h) //������������ ���������
        {
            count = arr[l];
            arr[l] = arr[h];
            arr[h] = count;
            l++;
            h--;
        }
    } while (l < h);
    if (low < h)
        quickSort(arr, low, h, type);
    if (l < high)
        quickSort(arr, l, high, type);
}

void write_arr(const vector<string>& filesName)
{
    fstream fs;
    srand(time(nullptr));
    int left_border = 1000;
    int range_len = 50000; // ������ ������� = range_len + left_border
    for (unsigned int j = 0; j < filesName.size(); j++) {
        fs.open(filesName[j], fstream::out | ofstream::trunc);
        if (fs.is_open()) // ���������, ��� ���� ������� ������
        {
            for (int i = 0; i < RAND_ARR_SIZE; i++)
                fs << (left_border + rand() % range_len) << '\n'; // ���������� � ����
            fs.close(); // ��������� ����
        }
    }
}

void read_arr(const vector<string>& filesName, int*& arr, int numRead)
{
    fstream fs;
    arr = new int[numRead * RAND_ARR_SIZE];
    for (unsigned int j = 0; j < numRead; j++) {
        fs.open(filesName[j], fstream::in);
        if (fs.is_open()) // ���������, ��� ���� ������� ������
        {
            for (int i = j * RAND_ARR_SIZE; i < (j + 1) * RAND_ARR_SIZE; i++)
                fs >> arr[i]; // ������ �� ����� 
            fs.close(); // ��������� ����
        }
    }
}

void print(int* arr, int size)
{
    for (int i = 0; i < size * RAND_ARR_SIZE; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "ru");
    vector<string> filesName;
    string numWrite;
    cout << "������� ���������� ����������� ������: ";
    cin >> numWrite;
    for (int i = 0; i < stoi(numWrite); i++)
    {
        char insP[200] = "data_";
        strcat_s(insP, to_string(i).c_str());
        strcat_s(insP, ".txt");
        filesName.emplace_back(insP);
    }
    write_arr(filesName); // ���������� ������� � �����
    
    cout << "������� ���������� ������ ��� ������: ";
    int numRead = 0;
    cin >> numRead;
    int* array_from_file = nullptr;
    read_arr(filesName, array_from_file, numRead); // ������ ������ �� �����
    
    print(array_from_file, numRead);
    cout << "���������� �� �����������(0) ��� �� �������� (1): ";
    int type;
    cin >> type;
    quickSort(array_from_file, 0, numRead * RAND_ARR_SIZE-1, type);
    
    print(array_from_file, numRead);

    string filesExcel = "data_excel.xls";
    fstream fsE;
    
    fsE.open(filesExcel, fstream::out | ofstream::trunc);
    if (fsE.is_open())
    {
        for (int i = 0; i < numRead * RAND_ARR_SIZE; i++)
            fsE << array_from_file[i] << '\n';
        fsE.close();
    }
        
    delete[] array_from_file;
    return 0;
}