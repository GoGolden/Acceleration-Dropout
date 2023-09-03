#include <cmath>
#include<ctime>
#include <random>
#include <cstdlib> 
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;
using std::bitset;

std::random_device rd;
std::mt19937 gen(rd());

const double e = 2.7182818284590452353602874713527; 

void float_to_binary(double number, int *bin, int bit){
  
  for(int i = 0; i < bit; i++){
    if(number * 2 >= 1){
      number = number * 2 - 1;
      bin[i] = 1;
    }
    else{
      number = number * 2;
      bin[i] = 0;
    }
  }
}

double* dropout(int n, double p, int bit, double *input_nums)
{
  int dropout_nums[n];
  int bin[bit];
  int mask;
  float_to_binary(p,bin,bit);

  uint64_t bound = 1ULL << n;
  std::uniform_int_distribution<uint64_t> distribution(0, bound-1);
  
  uint64_t ans = bound - 1;
  std::vector<uint64_t> rand_nums(bit);
  for (int j = 0; j < bit; j++) {
    rand_nums[j] = distribution(gen); 
    if(bin[bit-j-1] == 1){
      ans = ans & rand_nums[j];
    }
    else{
      ans = ans | rand_nums[j];
    }
  }

  for(int i = 0; i < n; i ++){
    dropout_nums[i] = ans>>i&1;
    input_nums[i] *= dropout_nums[i];
  }
    mask = ans;
    return input_nums;
}
