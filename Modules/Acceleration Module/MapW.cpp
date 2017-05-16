#include <stdio.h>
#include <iostream>
#include <math.h>  
#include "CarC.h"
#include "MapW.h"
using namespace std;

MapW::MapW()
{
}

MapW::~MapW()
{
}
 
void MapW::Path1(CarC obj,float v) {   
         do
            {
            v=v+obj.Acc;
            obj.yPos=0;
            obj.xPos=obj.xPos+v;
            
           
             cout<<"Position= ("<<obj.xPos<<"   ,   "<<obj.yPos<<"),  v="<<v<<endl; 
            }while(obj.xPos<50.0/3.0);
            
            do{
                obj.yPos=0;
                obj.xPos=obj.xPos+v;
                
            
                cout<<"Position= ("<<obj.xPos<<"   ,   "<<obj.yPos<<"),  v="<<v<<endl; 
                } while(obj.xPos>=50.0/3.0 && obj.xPos<(100.0/3.0));
                
            do{
                v=v-obj.Acc;
                obj.yPos=0;
                obj.xPos=obj.xPos+v;
                cout<<"Position= ("<<obj.xPos<<"   ,   "<<obj.yPos<<"),  v="<<v<<endl; 
                
                }
                while(v>=0);
   
    }










