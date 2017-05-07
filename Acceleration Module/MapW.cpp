#include <stdio.h>
#include <iostream>
#include <math.h>  
#include "CarC.h"
//#include "MapW.h"
using namespace std;


MapW::MapW()
{
}

MapW::~MapW()
{
}

//int* MapW::Path1(CarC obj,int v, int acc){
 
void MapW::Path1(CarC obj,float v) {   
    //while(obj.xPos<50)
    //{
            do
            {
            v=v+obj.Acc;
            obj.yPos=0;
            obj.xPos=obj.xPos+v;
            Pos[0]=obj.xPos;
            Pos[1]=obj.yPos;
            //MapW::count++;
            //return Pos;
             cout<<"Position= ("<<obj.xPos<<"   ,   "<<obj.yPos<<"),  v="<<v<<endl; 
            }while(obj.xPos<50.0/3.0);
            
            do{
                obj.yPos=0;
            obj.xPos=obj.xPos+v;
            Pos[0]=obj.xPos;
            Pos[1]=obj.yPos;
            //MapW::count++;
            //return Pos;
            cout<<"Position= ("<<obj.xPos<<"   ,   "<<obj.yPos<<"),  v="<<v<<endl; 
            }while(obj.xPos>=50.0/3.0 && obj.xPos<(100.0/3.0));
                
            do{
            v=v-obj.Acc;
            obj.yPos=0;
            obj.xPos=obj.xPos+v;
            Pos[0]=obj.xPos;
            Pos[1]=obj.yPos;
            //MapW::count++;
            //return Pos;
            cout<<"Position= ("<<obj.xPos<<"   ,   "<<obj.yPos<<"),  v="<<v<<endl; 
                
            }//while(obj.xPos>=100.0/3.0 && obj.xPos<3*(50.0/3.0));
            while(v>=0);
    //}     
 
        
    
    /*while(obj.xPos>=25 && obj.xPos<50)
        {
            v=v-acc;
            obj.yPos=0;
            obj.xPos=obj.xPos+v;
            MapW::Pos[0]=obj.xPos;
            MapW::Pos[1]=obj.yPos;
           cout<<obj.xPos<<"'"<<obj.yPos<<" v="<<v<<endl;  
            //return MapW::Pos;
        }
    
    while (obj.xPos>=50 && obj.xPos<75)
        {
            v=v+acc;
            obj.yPos=0;
            obj.xPos=obj.xPos+v;
            MapW::Pos[0]=obj.xPos;
            MapW::Pos[1]=obj.yPos;
            cout<<obj.xPos<<"'"<<obj.yPos<<" v="<<v<<endl;  
            //return MapW::Pos;
        }  
        
    while(obj.xPos>=75 && obj.xPos<100)
        {
            v=v-acc;
            obj.yPos=0;
            obj.xPos=obj.xPos+v;
            MapW::Pos[0]=obj.xPos;
            MapW::Pos[1]=obj.yPos;
            cout<<obj.xPos<<"'"<<obj.yPos<<" v="<<v<<endl;  
            //return MapW::Pos;
        }*/
        
      
}










