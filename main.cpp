#include <bits/stdc++.h>
#include <SDL.h>

// !! ELAPSED TIME IS NOT ACCURATE :)

using namespace std;

#define numbersSize 100
#define maxNumber 100
#define widthScale 10
#define heightScale 5
#define WINDOW_WIDTH numbersSize*widthScale
// (!!! DON'T MAKE IT TOO LARGE OR THE SCREEN WILL NOT FIT)
#define WINDOW_HEIGHT maxNumber * heightScale
// (!!! DON'T MAKE IT TOO LARGE OR THE SCREEN WILL NOT FIT)
#define delayTime 1

SDL_Window* window = nullptr;
SDL_Renderer * renderer = nullptr;
vector<int> numbers(numbersSize);

void random_numbers() {
  srand((unsigned) time(NULL));
  for (int i = 0; i < numbersSize; ++i) {
    int random = 1 + (rand() % maxNumber);
    numbers[i] = random;
  }
}

void draw(int i = -1, int j = -1) {
  for (int k = 0; k < numbersSize; ++k) {
    if (k == i) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    } else if (k == j) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    SDL_RenderDrawLine(renderer, k, 99, k, numbers[k]);
  }
}

void selectionSort() {
  const auto start = chrono::high_resolution_clock::now();
  for (int i = 0; i < numbersSize - 1; ++i) {
    int minIdx = i;
    for (int j = i + 1; j < numbersSize; ++j) {
      if (numbers[j] < numbers[minIdx]) {
        minIdx = j;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw(i, minIdx);
        SDL_RenderPresent(renderer);
        SDL_Delay(delayTime);
      }
    }
    swap(numbers[minIdx], numbers[i]);
  }
  const chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
  std::cout << "Elapsed Time: " << elapsed.count() << " sec\n";
}
void bubbleSort() {
  const auto start = chrono::high_resolution_clock::now();
  bool flag = true;
  for (int i = 0; i < numbersSize; ++i) {
    for (int j = i; j < numbersSize; ++j) {
      if (numbers[j] < numbers[i]) {
        swap(numbers[i], numbers[j]);
        flag = false;
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw(i, j);
      SDL_RenderPresent(renderer);
      SDL_Delay(delayTime);
    }
    if (flag) {
      break;
    }
  }
  const chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
  std::cout << "Elapsed Time: " << elapsed.count() << " sec\n";
}
void insertionSort() {
  const auto start = chrono::high_resolution_clock::now();
  for (int i = 1; i < numbersSize; ++i) {
    int j = i - 1;
    while (j >= 0 && numbers[j] > numbers[j + 1]) {
      int temp = numbers[j + 1];
      numbers[j + 1] = numbers[j];
      numbers[j] = temp;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw(i, j + 1);
      SDL_RenderPresent(renderer);
      SDL_Delay(delayTime);
      j--;
    }
  }
  const chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
  std::cout << "Elapsed Time: " << elapsed.count() << " sec\n";
}
void merge(int l, int r) {
  int m = l + (r - l) / 2;
  vector<int> left = {numbers.begin() + l, numbers.begin() + m + 1};
  vector<int> right = {numbers.begin() + m + 1, numbers.begin() + r + 1};
  int i = 0, j = 0;
  int k = l;
  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j]) {
      numbers[k] = left[i++];
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw(i - 1, j);
      SDL_RenderPresent(renderer);
      SDL_Delay(delayTime);
    } else {
      numbers[k] = right[j++];
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw(i, j - 1);
      SDL_RenderPresent(renderer);
      SDL_Delay(delayTime);
    }
    k++;
  }
  while (i < left.size()) {
    numbers[k++] = left[i++];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw(-1, i - 1);
    SDL_RenderPresent(renderer);
    SDL_Delay(delayTime);
  }
  while (j < right.size()) {
    numbers[k++] = right[j++];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw(-1, j - 1);
    SDL_RenderPresent(renderer);
    SDL_Delay(delayTime);
  }
}
void mergeSort(int l, int r) {
  if (r - l + 1 <= 1) {
    return;
  }
  int m = l + (r - l) / 2;
  mergeSort(l, m);
  mergeSort(m + 1, r);
  merge(l, r);
}
void callMerge() {
  const auto start = chrono::high_resolution_clock::now();
  mergeSort(0, numbersSize - 1);
  const chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
  std::cout << "Elapsed Time: " << elapsed.count() << " sec\n";
}
void quickSort(int l, int r) {
  if (r - l + 1 <= 1) {
    return;
  }
  int pivot = numbers[r];
  int left = l;
  for (int i = l; i < r; i++) {
    if (numbers[i] < pivot) {
      int temp = numbers[left];
      numbers[left] = numbers[i];
      numbers[i] = temp;
      left++;
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw(i, left - 1);
      SDL_RenderPresent(renderer);
      SDL_Delay(delayTime);
    } else {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      draw(i, left);
      SDL_RenderPresent(renderer);
      SDL_Delay(delayTime);
    }
  }
  numbers[r] = numbers[left];
  numbers[left] = pivot;
  quickSort(l, left - 1);
  quickSort(left + 1, r);

}
void callQuick() {
  const auto start = chrono::high_resolution_clock::now();
  quickSort(0, numbersSize - 1);
  const chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - start;
  std::cout << "Elapsed Time: " << elapsed.count() << " sec\n";
}

int main(int argc, char* argv[]) {
  random_numbers();
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderSetScale(renderer, widthScale, heightScale);
  bool running = true;
  bool is_sorted = false;
  SDL_Event event;
  while (running) {
    while(SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        random_numbers();
        is_sorted = false;
        switch (event.key.keysym.sym) {
          case (SDLK_1):
            cout << "\n-------Selection Sort-------\n";
            selectionSort();
            cout << "-------Selection Sort-------\n";
            is_sorted = true;
            break;
          case(SDLK_2):
            cout << "\n-------Bubble Sort-------\n";
            bubbleSort();
            cout << "-------Bubble Sort-------\n";
            is_sorted = true;
            break;
          case (SDLK_3):
            cout << "\n-------Insertion Sort-------\n";
            insertionSort();
            cout << "-------Insertion Sort-------\n";
            is_sorted = true;
            break;
          case(SDLK_4):
            cout << "\n-------Merge Sort-------\n";
            callMerge();
            cout << "-------Merge Sort-------\n";
            is_sorted = true;
            break;
          case(SDLK_5):
            cout << "\n-------Quick Sort-------\n";
            callQuick();
            cout << "-------Quick Sort-------\n";
            is_sorted = true;
            break;
          case (SDLK_0):
            random_numbers();
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            for (int j = 0; j < numbersSize; ++j) {
              draw();
              SDL_Delay(delayTime);
            }
            SDL_RenderPresent(renderer);
            is_sorted = false;
            break;
        }
      }
    }
    if (is_sorted) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      for (int j = 0; j < numbersSize; ++j) {
        draw();
        SDL_Delay(delayTime);
      }
      SDL_RenderPresent(renderer);
    }
  }

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  SDL_DestroyWindow(window);
  window = nullptr;
  SDL_Quit();

  return 0;
}
