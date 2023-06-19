#include <chrono>
#include <iostream>
#include <list>

int main() {
  for (int i = 0; i < 10; ++i) {
    std::list<int> myList;

    // 向列表中添加1000000个元素
    for (int i = 0; i < 1000000; ++i) {
      myList.push_back(i);
    }

    // 测试前置递减的性能
    auto startTime = std::chrono::high_resolution_clock::now();

    for (auto it = myList.begin(); it != myList.end(); ++it) {
      --(*it);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
        endTime - startTime);
    std::cout << "前置递减时间：" << duration.count() << " 纳秒" << std::endl;

    // 测试后置递减的性能
    startTime = std::chrono::high_resolution_clock::now();

    for (auto it = myList.begin(); it != myList.end(); it++) {
      (*it)--;
    }

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime -
                                                                    startTime);
    std::cout << "后置递减时间：" << duration.count() << " 纳秒" << std::endl;
  }

  return 0;
}
