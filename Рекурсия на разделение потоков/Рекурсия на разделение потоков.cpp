// Рекурсия на разделение потоков.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <iterator>

template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func func, int min = 5) {

   auto length = std::distance(first, last); //диапазон контейнера

   if (length <= min) {
      std::for_each(first, last, func);
      return;
   }
   
   Iterator mid = first;
   std::advance(mid, length / 2); // перемещаем mid в середину дипапазона

   auto future = std::async(std::launch::async, parallel_for_each<Iterator, Func>, first, mid, func, min);
   auto future2 = std::async(std::launch::async, parallel_for_each<Iterator, Func>, mid, last, func, min);
  
   future.get();
   future2.get();

}

int main() {
   std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

   auto func = [](int& x) {
      std::cout << x*x << " ";
      };

   parallel_for_each(vec.begin(), vec.end(), func);

   return 0;
}