
#include <iostream>
#include <sstream>
#include <chrono>
#include <unistd.h>

const int LONG_SIZE = 8;
const int PAGE_SIZE = sysconf(_SC_PAGESIZE);//2 * 1024 * 1024;
const int ONE_GIG = 1024 * 1024 * 1024;
const long TWO_GIG = 2L * ONE_GIG;

const int ARRAY_SIZE = (int) (TWO_GIG / LONG_SIZE);
const int WORDS_PER_PAGE = PAGE_SIZE / LONG_SIZE;

const int ARRAY_MASK = ARRAY_SIZE - 1;
const int PAGE_MASK = WORDS_PER_PAGE - 1;

const int PRIME_INC = 514229;

long *memory = new long[ARRAY_SIZE];

void init() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    memory[i] = 777;
  }
}

template<typename StrideType>
void perfTest(int runNumber, const StrideType& strideType) {
  auto start = std::chrono::high_resolution_clock::now();
  int pos = -1;
  long result = 0;
  for (int pageOffset = 0; pageOffset < ARRAY_SIZE; pageOffset += WORDS_PER_PAGE) {
    for (int wordOffset = pageOffset, limit = pageOffset + WORDS_PER_PAGE;
         wordOffset < limit;
         wordOffset++) {
      pos = strideType.next(pageOffset, wordOffset, pos);
      result += memory[pos];
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  double nsOp = duration.count() / (double) ARRAY_SIZE;

  if (208574349312L != result) {
    std::stringstream sss;
    sss<<result;
  }

  std::cout<<runNumber<<" - "<<duration.count()<<" s "<<strideType.type<<std::endl;
}

struct LINEAR_WALK {
  int next(int pageOffset, int wordOffset, int pos) const {
    return (pos + 1) & ARRAY_MASK;
  }

  std::string type = "Linear";
};

struct RANDOM_PAGE_WALK {
  int next(int pageOffset, int wordOffset, int pos) const {
    return pageOffset + ((pos + PRIME_INC) & PAGE_MASK);
  }
  std::string type = "Random page";
};

struct RANDOM_HEAP_WALK {
  int next(int pageOffset, int wordOffset, int pos) const {
    return (pos + PRIME_INC) & ARRAY_MASK;
  }
  std::string type = "Random heap";
};

void linear_walker() {
  LINEAR_WALK linear;
  for (int i = 0; i < 5; i++) {
    perfTest(i, linear);
  }
}

void heap_walker() {
  RANDOM_HEAP_WALK heap;
  for (int i = 0; i < 5; i++) {
    perfTest(i, heap);
  }
}

void page_walker() {
  RANDOM_PAGE_WALK page;
  for (int i = 0; i < 5; i++) {
    perfTest(i, page);
  }
}


int main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr<<"Specify task (1, 2 or 3)."<<std::endl;
    return -1;
  }
  int i = atoi(argv[1]);

  if(i == 1)
    linear_walker();
  else if(i==2)
    page_walker();
  else if(i ==3)
    heap_walker();
  else {
    std::cerr << "wrong task number" << std::endl;
    return -1;
  }
}
