#include <iostream>
#include<ctime>
#include <random>
#include <cstdlib> 
#include <vector>
#include <bitset>
using namespace std;
using std::bitset;

std::random_device rd;
std::mt19937 gen(rd());


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

void cpp_dropout(int n, int m){
  // uint64_t bound = 1ULL << n;
  std::uniform_int_distribution<uint64_t> distribution(0, 2);
  for(int j=0; j< m; j++){
    for(int i=0; i<n; i++){
      double rand_num = distribution(gen); 
      // rand_num<0.625;
    }
  }
  return ;
}

// void int_to_binary

static void dropout(double *input_nums, int *bin, int bit, int n, uint64_t bound, int *dropout_nums){
  // std::random_device device;
  // std::mt19937 generator(device());
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
  // std::cout<< binary_ans << std::endl;
  // return binary;
}

// static void dropout(int *bin, int bit, int n, uniform_int_distribution<uint64_t> distribution, std::mt19937 generator, std::bitset<50> binary){
  

//   uint64_t ans = 0;
//   std::vector<uint64_t> rand_nums(bit);
//   for (int j = 0; j < bit; j++) {
//     rand_nums[j] = distribution(generator); 
//     ans = ans ^ bin[j];
//     ans = ans | rand_nums[j];
//     ans = ans ^ bin[j];
//   }
//   //std::bitset<50> binary(ans);
//   // return binary;
// }

// static void dropout(int *bin, int bit, int n, uniform_int_distribution<uint64_t> distribution, std::mt19937 generator, std::bitset<50> binary){
  

//   uint64_t ans = (1ULL << n) - 1 ;
//   std::vector<uint64_t> rand_nums(bit);
//   for (int j = 0; j < bit; j++) {
//     rand_nums[j] = distribution(generator); 
//     if(bin[j] == 1){
//       ans = ans & rand_nums[j];
//     }
//     else{
//       ans = ans | rand_nums[j];
//     }
//   }
//   std::bitset<50> binary_ans(ans);
//   binary = binary_ans;
//   std::cout<< binary_ans << std::endl;
//   // return binary;
// }


int main(){
  clock_t start, end;
  int n = 50;
  int m = 10000000;
  double p = 0.625;
  int bit = 3;
  int bin[3] = {1, 0 ,1};
  uint64_t bound = 1ULL << n;
  std::bitset<50> q;
  double input_nums[n];
  int dropout_nums[n];

  for(int i = 0; i < n; i ++){
    input_nums[i] = 1.00;
  }



  // float_to_binary(p, bin, bit);

  start = clock();

  for(int i = 0; i < m; i++){
    //dropout(bin, bit, n, distribution, gen, q);
    dropout(input_nums,bin, bit, n, bound, dropout_nums);
    
  }

  end = clock();

  double time_taken = double(end - start) / CLOCKS_PER_SEC;  

  std::cout << "Time taken: " << time_taken << " s" << std::endl;

  start = clock();

  cpp_dropout(n, m);

  end = clock();

  double time_taken1 = double(end - start) / CLOCKS_PER_SEC;  

  std::cout << "Cpp Time taken: " << time_taken1 << " s" << std::endl;

  return 0;

}
