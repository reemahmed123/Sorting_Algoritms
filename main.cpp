#include <iostream>
#include <vector>
#include <fstream>
#include<algorithm>
#include<chrono>
#include<bits/stdc++.h>
#include<iomanip>
using namespace std;
class Student
{
    string name;
    string id;
    double GPA;

public:
    Student() {}
    Student(string n, string i, double g) : name(n), id(i), GPA(g) {}

    string getName()  { return name; }
    double getGPA() { return GPA; }
    string getID()  { return id; }
    bool operator<( const Student& other) const
    {
        string name1 = name;
        string name2 = other.name;

        for (char &c : name1)
        {
            c = tolower(c);
        }

        for (char &c : name2)
        {
            c = tolower(c);
        }

        return name1 < name2;
    }

    Student &operator=(const Student &other)
    {
        if (this != &other)
        {
            name = other.name;
            id = other.id;
            GPA = other.GPA;
        }
        return *this;
    }
};
vector<Student> ReadStudentsFromFile(const string &filename)
{
    ifstream file(filename);
    int numStudents;
    file >> numStudents;
    file.ignore();
    vector<Student> students;
    for (int i = 0; i < numStudents; i++)
    {
        string name, id;
        double GPA;
        getline(file, name);
        getline(file, id);
        file >> GPA;
        file.ignore();
        students.push_back(Student(name, id, GPA));
    }
    return students;
}

void WriteStudentsToFile(const string &filename,  string algorithm, double time, vector<Student> &students)
{
    ofstream File(filename,ios::app);
    File << "Algorithm: " << algorithm << endl;
    File << "Running Time: " << time << " milliseconds" << endl;
    for ( auto &student : students)
    {
        File << student.getName() << endl;
        File << student.getID() << endl;
        File << student.getGPA() << endl;
    }
    File<<endl;
}

template <typename T, typename Compare>
void Merge(vector<T> &students, int left, int middle, int right, Compare comp)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<T> L(n1);
    vector<T> R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = students[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = students[middle + 1 + j];
    }

    int k = left, i = 0, j = 0;
    while (i < n1 && j < n2)
    {
        if (comp(L[i], R[j]))
        {
            students[k] = L[i];
            k++;
            i++;
        }
        else
        {
            students[k] = R[j];
            k++;
            j++;
        }
    }

    while (i < n1)
    {
        students[k] = L[i];
        k++;
        i++;
    }

    while (j < n2)
    {
        students[k] = R[j];
        k++;
        j++;
    }
}

template <typename T, typename Compare>
double MergeSort(vector<T> &students, int left, int right, Compare comp)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (left >= right)
    {
        return 0;
    }
    else
    {
        int middle = (left + right) / 2;
        MergeSort(students, left, middle, comp);
        MergeSort(students, middle + 1, right, comp);
        Merge(students, left, middle, right, comp);
       auto stop = std::chrono::high_resolution_clock::now();
       auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();
       return (duration * 1000);
    }
    return 0;
}
template<typename T , typename Compare>
int Partition(vector<T>&students, int left, int right , Compare comp)
{
    T x = students[left];

    int i = left;

    for (int j = left + 1; j <= right; j++)
    {

        if (comp(students[j] , x))
        {

            i = i + 1;

            swap(students[i], students[j]);
        }
    }

    swap(students[i], students[left]);

    return i;
}
template <typename T, typename Compare>
double QuickSort(vector<T>& students, int left, int right,Compare comp)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (left >= right)
    {
       return 0;
    }

    else
    {

        int middle = Partition(students, left, right,comp);
        QuickSort(students, left, middle - 1,comp);
        QuickSort(students, middle + 1, right,comp);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();
        return (duration * 1000);
    }
    return 0;
}
template <typename T, typename Compare>
double selection(vector<T> &data, int n, Compare comp)
{
    auto start = std::chrono::high_resolution_clock::now();
    int i, j, least;
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1, least = i; j < n; j++)
        {
            if (comp(data[j] , data[least]))
            {
                least = j;
            }
        }
        swap(data[least], data[i]);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();

    return duration * 1000;
}
template <typename T, typename Compare>
double shellSort(vector<T> &students, int n, Compare comp)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            T temp = students[i];
            int j;
            for (j = i; j >= gap && comp(temp,students[j-gap]); j -= gap){
                students[j] = students[j - gap];
            }
            // put temp (the original a[i]) in its correct location
            students[j] = temp;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();

    return duration * 1000;
}
template <typename T, typename Compare>
double bubble(vector<T>&students, int n , Compare comp)
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ( comp(students[j + 1] , students[j]))
            {
                swap(students[j], students[j + 1]);
            }
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();

    return duration * 1000;
}
template <typename T, typename Compare>
double insertionSort(vector<T> &students, int n, Compare comp)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1, j; i < n; i++)
    {
        T tmp = students[i];

        for (j = i; j > 0 && comp(tmp, students[j - 1]); j--)
        {
            students[j] = students[j - 1]; // shift
        }

        students[j] = tmp;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();

    return duration*1000;
}
template <class T>
vector<T> Count_Sort( vector<T> &students , double&time)
{
    auto start=std::chrono::high_resolution_clock::now();
    int n=students.size();
    int maxx =0;
    for (int i = 0; i < n; ++i)
    {
        maxx = max((int)students[i].getGPA(), maxx);
    }

    vector<int> countArray(maxx + 1, 0);

    for (int i = 0; i < n; i++)
    {
        countArray[(int)students[i].getGPA()]++;
    }
    for (int i = 1; i <= maxx; i++)
    {
        countArray[i] += countArray[i - 1];
    }

    vector<Student>outputArray(n);
    for (int i = n - 1; i >= 0; i--)
    {
        outputArray[countArray[(int)students[i].getGPA()] - 1] = students[i];
        countArray[(int)students[i].getGPA()]--;
    }

    reverse(outputArray.begin(), outputArray.end());
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<long double>>(stop - start).count();
    time=duration*1000;
    return outputArray;
}
int main()
{
    vector<Student>students=ReadStudentsFromFile("students.txt");
    double t1=insertionSort(students,students.size(),less<Student>());
    WriteStudentsToFile("sortedbyname","Insertion Sort",t1,students);

    students = ReadStudentsFromFile("students.txt");
    double t2 = selection(students, students.size(),less<Student>());
    WriteStudentsToFile("sortedbyname", "Selection Sort", t2, students);

    students = ReadStudentsFromFile("students.txt");
    double t3= bubble(students, students.size(), less<Student>());
    WriteStudentsToFile("sortedbyname", "Bubble Sort", t3, students);

    students = ReadStudentsFromFile("students.txt");
    double t4 = shellSort(students, students.size(), less<Student>());
    WriteStudentsToFile("sortedbyname", "Shell Sort", t4, students);

    students = ReadStudentsFromFile("students.txt");
    double t5=MergeSort(students, 0,students.size()-1, less<Student>());
    WriteStudentsToFile("sortedbyname", "Merge Sort",t5 , students);

    students = ReadStudentsFromFile("students.txt");
    double t6 = QuickSort(students,0, students.size()-1, less<Student>());
    WriteStudentsToFile("sortedbyname", "Quick Sort", t6, students);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   students = ReadStudentsFromFile("students.txt");
    double t7 = insertionSort(students, students.size(), [](Student s1 , Student s2){
        return s1.getGPA()>s2.getGPA();
    });
    WriteStudentsToFile("sortedByGpa", "Insertion Sort", t7, students);

    students = ReadStudentsFromFile("students.txt");
    double t8 = selection(students, students.size(), [](Student s1, Student s2)
            { return s1.getGPA() > s2.getGPA(); } );
    WriteStudentsToFile("sortedByGpa", "Selection Sort", t8, students);

     students = ReadStudentsFromFile("students.txt");
    double t9 = bubble(students, students.size(), [](Student s1, Student s2)
                       { return s1.getGPA() > s2.getGPA(); });
    WriteStudentsToFile("sortedByGpa", "Bubble Sort", t9, students);

     students= ReadStudentsFromFile("students.txt");
    double t10 = shellSort(students, students.size(), [](Student s1, Student s2)
                           { return s1.getGPA() > s2.getGPA(); });
    WriteStudentsToFile("sortedByGpa", "Shell Sort", t10, students);

     students = ReadStudentsFromFile("students.txt");
    double t11 = MergeSort(students, 0, students.size() - 1, [](Student s1, Student s2)
                           { return s1.getGPA() > s2.getGPA(); });
    WriteStudentsToFile("sortedByGpa", "Merge Sort", t11, students);

    students = ReadStudentsFromFile("students.txt");
    double t12 = QuickSort(students, 0, students.size() - 1, [](Student s1, Student s2)
                           { return s1.getGPA() > s2.getGPA(); });
    WriteStudentsToFile("sortedByGpa", "Quick Sort", t12, students);

    double time=0;
   students = ReadStudentsFromFile("students.txt");
    vector<Student>out=Count_Sort(students,time);
    WriteStudentsToFile("sortedByGpa", "Count Sort" , time, out);
    }