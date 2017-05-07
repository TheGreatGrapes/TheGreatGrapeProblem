#include <stdio.h>
#include <iostream>
#include <math.h>  
//using namespace std;
#include "CarC.h"
#include "MapW.h"

using namespace std;


//int *fillarr(int arr[2], int length);

int main(int argc, char **argv)
{
    //int a[2]={2,0};
    CarC c;
    //cout<<c.Acc;
    //int *loc1;
    MapW m;
    
    //m.Path1(c,0.0);
    c.moveCar(m,0.0);
    
    //cout<< loc1[0]<<","<<loc1[1];
    

    /*int b[2];
    int *c;
    
    c= fillarr(b,3);
    cout<<c[0]<<c[1];
}

int *fillarr(int arr[2], int x){
        
        arr[0]= x+1;
        arr[1]=x+2;
        return arr;
*/

}