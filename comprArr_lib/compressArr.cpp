#include <iostream>
#include <vector>
#include "compressArr.h"
using namespace std;

void compressArr(float frame[32*24],int ori_w,int height,int width,int16_t data[20*15])
{

  vector<int16_t> arr;
    for(int hei = 0; hei<height;hei++){
      for(int i = ori_w*hei; i < width + ori_w*hei; i++){

        arr.push_back(frame[i]);
        
      } 
    }
    for(int i = 0;i<arr.size();i++){
      data[i] = arr.at(i);
    }
   
}

