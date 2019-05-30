#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>

/*Auxiliary method for generating numbers in chosen range*/
int Generator(int low, int high)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> ndis(low, high);
  return ndis(gen);
}

/*Auxiliary method for generating string of given size*/
std::string GeneratorS(int size)
{
  std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  std::string result;
  std::random_device rd;
  std::mt19937 generator(rd());
  for (int i = 0; i < size; i++)
  {
    std::shuffle(str.begin(), str.end(), generator);
    result = result + str.substr(0, 1);
  }
  return result;
}

/*Auxiliary method for generating vector of random integers*/
std::vector<int> RandomVectorInt(int size, int low, int high)
{
  std::vector<int> v;
  for (int i = 0; i < size; i++)
  {
    v.push_back(Generator(low, high));
  }
  return v;
}

/*Auxiliary method for generating vector of random strings*/
std::vector<std::string> RandomVector(int size, int low, int high)
{
  std::vector<std::string> v;
  for(int i = 0; i < size; i++)
  {
    v.push_back(GeneratorS(Generator(low, high)));
  }
  return v;
}

/*Function that prints all elements from vector*/
template <typename T>
void Print(std::vector<T> &a)
{
  for (int i = 0; i < a.size(); i++)
  {
    std::cout << a[i] << " ";
  }
  std::cout << "\n";
}

/*Auxiliary methods for finding minimum and maximum elements in vector*/
int Low(std::vector<int> &a)
{
  return *min_element(a.begin(), a.end());
}
int High(std::vector<int> &a)
{
  return *max_element(a.begin(), a.end());
}

/*Another one method just to get needed digit from integer */
int GetDigit(int a, int pos)
{
  for (int i = 0; i < pos - 1; i++)
  {
    a = a / 10;
  }
  a = a % 10;
  return a;
}

/*Auxiliary method to get bit at position i*/
int GetBit(int a, int i)
{
  a = (a >> i) & 1U;
  return a;
}

/*Get data in CSV format from the vector*/
void GetCSV(std::vector<std::vector<double>> &v, std::vector<int> &num)
{
  std::ofstream myfile;
  myfile.open ("TimeData.csv");
  int j = 0;
  for (int i = 0; i < v[0].size(); i++)
  {
    myfile << num[i];
    for(int j = 0; j < v.size(); j++)
    {
      myfile << "," << v[j][i];
    }
    myfile << "\n";
  }
  myfile.close();
}

template<typename T>
class Node
{
public:
  Node *prev = nullptr;
  Node *next = nullptr;
  T value;
};

template <typename T>
class LinkedList
{
  Node<T> *Head, *Tail; 
  int m_size = 0;

public:
  LinkedList():Head(nullptr),Tail(nullptr){};
  int size ()
  {
    return m_size;
  }
  Node<T> *GetHead()
  {
    return Head;
  }
  Node<T> *GetTail()
  {
    return Tail;
  }

  Node<T> *get (int pos)
  {
    Node<T> *temp = Head;
    int count = 0;
    if(temp == nullptr)
    {
      return nullptr;
    }
    while(temp != nullptr)
    {
      if(count == pos)
      {
        return temp;
      }
      temp = temp->next;
      count++;
    }
    return nullptr;
  }

  /*Inserts node with input value to specified position*/
  Node<T> *insert (T value, int pos) 
  {
    Node<T> *temp = new Node<T>;
    if (pos == m_size)
    {
      push_back(value);
    }
    else if (pos > m_size)
    {
      return nullptr;
    }
    else if (pos == 0)
    {
      m_size++;
      temp->prev = nullptr;
      temp->next = Head;
      Head->prev = temp;
      Head = temp;
      temp->value = value;
      return temp;
    }
    else if (pos > 0)
    {
      m_size++;
      int count = 0;
      Node<T> *tmp = Head;
      while (count != pos)
      {
        tmp = tmp->next;
        count++;
      }
      temp->next = tmp;
      temp->prev = tmp->prev;
      tmp->prev->next = temp;
      tmp->prev = temp;
      temp->value = value;
      return temp;
    }
    return nullptr;
  }

  /*Inserts node with input value in the end of the list */
  Node<T> *push_back (T value)
  {
    Node<T> *temp = new Node<T>;
    temp->next = nullptr;
    temp->value = value;
    if (Head != nullptr)
    {
      temp->prev = Tail;
      Tail->next = temp;
      Tail = temp;
    }
    else
    {
      temp->prev = nullptr;
      Head = Tail = temp;
    }
    m_size++;
    return temp;
  }
  
  /* Auxilary method to change position of existing node without removing it*/
  void change (Node<T> *temp, int pos, int place)
  {
    if (pos == place)
    {
      return;
    }
    /* Untie given node, so it's flying in the space now */
    if (Head == nullptr || temp == nullptr)
    {
      return;
    }
    if (Head == temp)
    {
      Head = temp->next;
    }
    if (temp->next != nullptr)
    {
      temp->next->prev = temp->prev;
    }
    if (temp->prev != nullptr)
    {
      temp->prev->next = temp->next;
    }
    m_size--;

    /* Now we are putting it back to the new position*/
    if (place == m_size)
    {
      temp->next = nullptr;
      if (Head != nullptr)
      {
        temp->prev = Tail;
        Tail->next = temp;
        Tail = temp;
      }
      else
      {
        temp->prev = nullptr;
        Head = Tail = temp;
      }
      m_size++;
    }
    else if (place > m_size)
    {
      return;
    }
    else if (place == 0)
    {
      m_size++;
      temp->prev = nullptr;
      temp->next = Head;
      Head->prev = temp;
      Head = temp;
      return;
    }
    else if (place > 0)
    {
      m_size++;
      int count = 0;
      Node<T> *tmp = Head;
      while (count != place)
      {
        tmp = tmp->next;
        count++;
      }
      temp->next = tmp;
      temp->prev = tmp->prev;
      tmp->prev->next = temp;
      tmp->prev = temp;
      return;
    }
  }

  /*Finds first node from the begin with given value*/
  Node<T> *find (T value)
  {
    Node<T> *temp = Head;
    if(temp == nullptr)
    {
      return nullptr;
    }
    else
    {
      while(temp != nullptr)
      {
        if(temp->value == value)
        {
          return temp;
        }
        temp = temp->next;
      }
      return nullptr;
    }
  }
  
  /*removes input node*/
  void remove (Node<T> *node)
  {
    if (Head == nullptr || node == nullptr)
    {
      return;
    }
    if (Head == node)
    {
      Head = node->next;
    }
    if (node->next != nullptr)
    {
      node->next->prev = node->prev;
    }
    if (node->prev != nullptr)
    {
      node->prev->next = node->next;
    }
    m_size--;
    delete node;
  }

  /*Reverses the list*/
  void reverse ()
  {
    Node<T> *save = Head;
    while(save != nullptr)
    {
      Node<T> *tmp = save->next;
      save->next = save->prev;
      save->prev = tmp;
      if (tmp == nullptr)
      {
        Tail = Head;
        Head = save;
      }
      save = tmp;
    }
  }
  
  /*Clears the list*/
  void clear ()
  {
    while (Head)                     
    {
      Tail = Head->next;
      delete Head;
      Head = Tail;
    }
    m_size = 0;
  }
  
  /*Prints list to stdout*/
  void print_list ()
  {
    Node<T> *temp = Head;
    while (temp != nullptr)
    {
      std::cout << temp->value << " ";
      temp = temp->next;
    }
    std::cout << "\n";
  }

  ~LinkedList ()
  {
  }
};

template <typename T>
LinkedList<T> Convert(std::vector<T> &a)
{
  LinkedList<T> result;
  for (int i = 0; i < a.size(); i++)
  {
    result.push_back(a[i]);
  }
  return result;
}

template <typename T>
void InsertionSort(std::vector<T> &a)
{
  int i, j, n;
  T key;
  n = a.size();
  for (i = 1; i < n; i++)
  {
    key = a[i];
    j = i - 1;
    while (j >= 0 && a[j] > key)
    {
      a[j + 1] = a[j];
      j = j - 1;
    }
    a[j + 1] = key;
  }
}

template <typename T>
void QuickSort(std::vector<T> &a, int left, int right)
{
  int index;
  if (left < right)
  {
    T pivot = a[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; j++)
    {
      if (a[j] < pivot)
      {
        i++;
        std::swap(a[i], a[j]);
      }
    }
    std::swap(a[i + 1], a[right]);
    index = i + 1;
    QuickSort(a, left, index - 1);
    QuickSort(a, index + 1, right);
  }
}

void CountingSort(std::vector<int> &a, int low, int high)
{
  int size = high - low + 1;
  int shift = 0 - low;
  std::vector<int> temp(size, 0);
  int index = 0;
  for (int i = 0; i < a.size(); i++)
  {
    temp[a[i] + shift]++;
  }
  for (int i = 0; i < temp.size(); i++)
  {
    for (int j = 0; j < temp[i]; j++)
    {
      a[index] = i - shift;
      index++;
    }
  }
}

template <typename T>
void Merge(std::vector<T> &a, int left, int middle, int right)
{
  int s1 = middle - left + 1;
  int s2 = right - middle;
  std::vector<T> temp1 (s1);
  std::vector<T> temp2 (s2);
  for (int i = 0; i < s1; i++)
  {
    temp1[i] = a[left + i];
  }
  for (int i = 0; i < s2; i++)
  {
    temp2[i] = a[middle + 1 + i];
  }
  int index = left, i = 0, j = 0;
  while (i < s1 && j < s2)
  {
    if (temp1[i] <= temp2[j])
    {
      a[index] = temp1[i];
      i++;
    }
    else
    {
      a[index] = temp2[j];
      j++; 
    }
    index++;
  }
  while (i < s1)
  {
    a[index] = temp1[i];
    index++;
    i++;
  }
  while (j < s2)
  {
    a[index] = temp2[j];
    index++;
    j++;
  }
}

template <typename T>
void MergeSort(std::vector<T> &a, int left, int right)
{
  if (left < right)
  {
    int middle = left + (right - left)/2;
    MergeSort(a, left, middle);
    MergeSort(a, middle + 1, right);
    Merge(a, left, middle, right);
  }
}

void RadixSort(std::vector<int> &a, int maximum)
{
  int step = 0, temp = maximum;
  std::vector<LinkedList<int>> bucket (10);
  while (temp > 0)
  {
    temp = temp / 10;
    step++;
  }
}

template <typename T>
void InsertionSortList(LinkedList<T> &a)
{
  int i, j;
  T key;
  for (i = 1; i < a.size(); i++)
  {
    key = a.get(i)->value;
    j = i - 1;
    while(j >= 0 && a.get(j)->value > key)
    {
      j--;
    }
    a.change(a.get(i), i, j + 1);
  }
}

template <typename T>
void QuickSortList(LinkedList<T> &a, int left, int right)
{
  int index;
  if (left < right)
  {
    T temp;
    T pivot = a.get(right)->value;
    int i = left - 1;
    for (int j = left; j <= right - 1; j++)
    {
      if (a.get(j)->value < pivot)
      {
        i++;
        if (i > j)
        {
          a.change(a.get(j), j, i);
          a.change(a.get(i - 1), i - 1, j);
        }
        else if (j > i)
        {
          a.change(a.get(i), i, j);
          a.change(a.get(j - 1), j - 1, i);
        }
      }
    }
    if (i + 1 > right)
    {
      a.change(a.get(right), right, i + 1);
      a.change(a.get(i), i, right);
    }
    else if (right > i + 1)
    {
      a.change(a.get(i + 1), i + 1, right);
      a.change(a.get(right - 1), right - 1, i + 1);
    }
    index = i + 1;
    QuickSortList(a, left, index - 1);
    QuickSortList(a, index + 1, right);
  }
}

template <typename T>
void MergeList(LinkedList<T> &a, int left, int middle, int right)
{
  int s1 = middle + 1;
  if (a.get(middle)->value <= a.get(s1)->value)
  {
    return;
  }
  while (left <= middle && s1 <= right)
  {
    if (a.get(left)->value <= a.get(s1)->value)
    {
      left++;
    }
    else
    {
      T temp = a.get(s1)->value;
      int index = s1;
      a.change(a.get(s1), s1, left);
      left++;
      middle++;
      s1++;
    }
  }
}

template <typename T>
void MergeSortList(LinkedList<T> &a, int left, int right)
{
  if (left < right)
  {
    int middle = left + (right - left)/2;
    MergeSortList(a, left, middle);
    MergeSortList(a, middle + 1, right);
    MergeList(a, left, middle, right);
  }
}

void RadixSortTen(std::vector<int> &a, int length)
{
  int pos, index = 0;
  std::vector<LinkedList<int>> bucket (10);
  for (pos = 1; pos <= length; pos++)
  {
    for(int i = 0; i < a.size(); i++)
    {
      int x;
      x = GetDigit(a[i], pos);
      bucket[x].push_back(a[i]);
    }
    for(int i = 0; i < 10; i++)
    {
      for(int j = 0; j < bucket[i].size(); j++)
      {
        a[index] = bucket[i].get(j)->value;
        index++;
      }
    }
    for(int i = 0; i < 10; i++)
    {
      bucket[i].clear();
    }
    index = 0;
  }
}

void RadixSortTwo(std::vector<int> &a, int len)
{
  int length = log2(len) + 1;
  int pos, index = 0;
  std::vector<LinkedList<int>> bucket (2);
  for (pos = 0; pos < length; pos++)
  {
    for (int i = 0; i < a.size(); i++)
    {
      int x;
      x = GetBit(a[i], pos);
      bucket[x].push_back(a[i]);
    }
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < bucket[i].size(); j++)
      {
        a[index] = bucket[i].get(j)->value;
        index++;
      }
    }
    for(int i = 0; i < 2; i++)
    {
      bucket[i].clear();
    }
    index = 0;
  }
}

void TestInteger(int length, std::vector<std::vector<double>> &a)
{
  double res = 0, res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0;
  for (int i = 0; i < 3; i++)
  {
    std::vector<int> save, temp;
    LinkedList<int> savelist;
    save = RandomVectorInt(length, -2147483648, 2147483647);
    savelist = Convert(save);
    temp = save;

    auto start = std::chrono::system_clock::now();
    InsertionSort(temp);
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    res = res + time.count();

    auto start1 = std::chrono::system_clock::now();
    InsertionSortList(savelist);
    auto end1 = std::chrono::system_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    res1 = res1 + time1.count();
    temp = save;
    savelist = Convert(save);

    auto start2 = std::chrono::system_clock::now();
    MergeSort(temp, 0, temp.size() - 1);
    auto end2 = std::chrono::system_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    res2 = res2 + time2.count();

    auto start3 = std::chrono::system_clock::now();
    MergeSortList(savelist, 0, savelist.size() - 1);
    auto end3 = std::chrono::system_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    res3 = res3 + time3.count();
    temp = save;
    savelist = Convert(save);

    auto start4 = std::chrono::system_clock::now();
    QuickSort(temp, 0, temp.size() - 1);
    auto end4 = std::chrono::system_clock::now();
    auto time4 = std::chrono::duration_cast<std::chrono::milliseconds>(end4 - start4);
    res4 = res4 + time4.count();

    auto start5 = std::chrono::system_clock::now();
    QuickSortList(savelist, 0, savelist.size() - 1);
    auto end5 = std::chrono::system_clock::now();
    auto time5 = std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
    res5 = res5 + time5.count();
    temp = save;
  }
  res = res / 3;
  res1 = res1 / 3;
  res2 = res2 / 3;
  res3 = res3 / 3;
  res4 = res4 / 3;
  res5 = res5 / 3;
  a[0].push_back(res);
  a[1].push_back(res1);
  a[2].push_back(res2);
  a[3].push_back(res3);
  a[4].push_back(res4);
  a[5].push_back(res5);
}

void TestString(int length, std::vector<std::vector<double>> &a)
{
  double res = 0, res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0;
  for (int i = 0; i < 3; i++)
  {
    std::vector<std::string> save, temp;
    LinkedList<std::string> savelist;
    save = RandomVector(length, 1, 5);
    savelist = Convert(save);
    temp = save;

    auto start = std::chrono::system_clock::now();
    InsertionSort(temp);
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    res = res + time.count();

    auto start1 = std::chrono::system_clock::now();
    InsertionSortList(savelist);
    auto end1 = std::chrono::system_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    res1 = res1 + time1.count();
    temp = save;
    savelist = Convert(save);

    auto start2 = std::chrono::system_clock::now();
    MergeSort(temp, 0, temp.size() - 1);
    auto end2 = std::chrono::system_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    res2 = res2 + time2.count();

    auto start3 = std::chrono::system_clock::now();
    MergeSortList(savelist, 0, savelist.size() - 1);
    auto end3 = std::chrono::system_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    res3 = res3 + time3.count();
    temp = save;
    savelist = Convert(save);

    auto start4 = std::chrono::system_clock::now();
    QuickSort(temp, 0, temp.size() - 1);
    auto end4 = std::chrono::system_clock::now();
    auto time4 = std::chrono::duration_cast<std::chrono::milliseconds>(end4 - start4);
    res4 = res4 + time4.count();

    auto start5 = std::chrono::system_clock::now();
    QuickSortList(savelist, 0, savelist.size() - 1);
    auto end5 = std::chrono::system_clock::now();
    auto time5 = std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
    res5 = res5 + time5.count();
    temp = save;
  }
  res = res / 3;
  res1 = res1 / 3;
  res2 = res2 / 3;
  res3 = res3 / 3;
  res4 = res4 / 3;
  res5 = res5 / 3;
  a[0].push_back(res);
  a[1].push_back(res1);
  a[2].push_back(res2);
  a[3].push_back(res3);
  a[4].push_back(res4);
  a[5].push_back(res5);
}

void TestN(int length, std::vector<std::vector<double>> &a)
{
  double res = 0, res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0;
  for (int i = 0; i < 3; i++)
  {
    std::vector<int> save, temp;
    save = RandomVectorInt(length, 1, 100000000);
    temp = save;
    int k = High(temp), s = 0;
    while(k > 0)
    {
      k = k / 10;
      s++;
    }

    auto start = std::chrono::system_clock::now();
    CountingSort(temp, Low(temp), High(temp));
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    res = res + time.count();
    temp = save;

    auto start2 = std::chrono::system_clock::now();
    RadixSortTen(temp, s);
    auto end2 = std::chrono::system_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    res2 = res2 + time2.count();
    temp = save;

    auto start3 = std::chrono::system_clock::now();
    RadixSortTwo(temp, High(temp));
    auto end3 = std::chrono::system_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    res3 = res3 + time3.count();
  }
  res = res / 3;
  res2 = res2 / 3;
  res3 = res3 / 3;
  a[0].push_back(res);
  a[1].push_back(res2);
  a[2].push_back(res3);
}

int main()
{
  std::vector<int> a;
  LinkedList<int> b,c,d;
  std::vector<std::vector<double>> time (6);
  std::vector<int> tests;
  for (int i = 1; i <= 5000; i++)
  {
    tests.push_back(i);
  }
  for (int i = 0; i < tests.size(); i++)
  {
    TestInteger(tests[i], time);
  }
  GetCSV(time, tests);
}
