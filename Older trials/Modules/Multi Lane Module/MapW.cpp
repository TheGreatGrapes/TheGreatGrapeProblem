#include <stdio.h>
#include <iostream>
#include <math.h>  
#include "CarC.h"
#include "MapW.h"
#include <vector>
using namespace std;

MapW::MapW()
{
}

MapW::~MapW()
{
}

//ignore function Path1//
void MapW::Path1(CarC obj1, CarC obj2, float v1, float v2) {   
/*   
            do{
                v1=v1+obj1.Acc;
                obj1.yPos=0;
                obj1.xPos=obj1.xPos+v1;
                obj1.time=obj1.time+1;
                cout<< "Position car1("<<obj1.xPos<<" , "<<obj1.yPos<<"),  v_car1="<<v1<< "  Time= "<< obj1.time<< endl;
                }while(obj1.xPos<50.0/3.0 );
                
            do{
                obj1.yPos=0;
                obj1.xPos=obj1.xPos+v1;
                obj1.time=obj1.time+1;
                cout<< "Position car1("<<obj1.xPos<<" , "<<obj1.yPos<<"),  v_car1="<<v1<<"  Time= "<< obj1.time<< endl;                
                } while(obj1.xPos<(100.0/3.0));
                
            do{
                v1=v1-obj1.Acc;
                obj1.yPos=0;
                obj1.xPos=obj1.xPos+v1;
                obj1.time=obj1.time+1;
                cout<< "Position car1("<<obj1.xPos<<" , "<<obj1.yPos<<"),  v_car1="<<v1<<"  Time= "<< obj1.time<< endl;                
                } while(v1>0 && obj1.xPos<50.0 );
                
             cout<<endl;
             cout<<endl;
                
            do{
                v2=v2+obj2.Acc;
                obj2.yPos=0;
                obj2.xPos=obj2.xPos+v2;
                obj2.time=obj2.time+1;
                
                cout<< "Position car2("<<obj2.xPos<<" , "<<obj2.yPos<<"),  v_car2="<<v2<<"  Time= "<< obj2.time<< endl;  
                }while(obj2.xPos<50.0/3.0);
   
   
            do{
                obj2.yPos=0;
                obj2.xPos=obj2.xPos+v2;
                obj2.time=obj2.time+1;
                
                cout<< "Position car2("<<obj2.xPos<<" , "<<obj2.yPos<<"),  v_car2="<<v2<<"  Time= "<< obj2.time<< endl;           
                } while(obj2.xPos>=50.0/3.0 && obj2.xPos<(100.0/3.0));
                
             do{
                v2=v2-obj2.Acc;
                obj2.yPos=0;
                obj2.xPos=obj2.xPos+v2;
                obj2.time=obj2.time+1;
            
                cout<< "Position car2("<<obj2.xPos<<" , "<<obj2.yPos<<"),  v_car2="<<v2<<"  Time= "<< obj2.time<< endl;            
                } while(v2>=0 || obj2.xPos<=50.0 );
                */

    }
  

//Path with multiple lanes//  
void MapW::Path(vector<CarC*> c){
      
      time= 0;   //initialising the time counter
            do{
                time=time+1;
                cout<< "time: "<<time<<" ";
                
                for(int i=0;i<c.size();i++){   //Looping through each car
                    
                    if(c[i]->xPos<50.0/3.0)        //acceleration part for car c[i]
                        {
                        c[i]->Vin=c[i]->Vin+ c[i]->Acc;
                        c[i]->yPos=0;
                        c[i]->xPos=c[i]->xPos+c[i]->Vin;
                        //obj1.time=obj1.time+1;
                        cout<< "Position car:"<<i+1<<"("<<c[i]->xPos<<" , "<<c[i]->yPos<<"),  v_car= "<<c[i]->Vin<<" "<<endl;    
                        }
                    else if (c[i]->xPos<(100.0/3.0))   //cruising part for car c[i]
                        {
                        c[i]->yPos=0;
                        c[i]->xPos=c[i]->xPos+c[i]->Vin;
                        //c[i]->time=c[i]->time+1;
                        cout<< "Position car:"<<i+1<<"("<<c[i]->xPos<<" , "<<c[i]->yPos<<"),  v_car= "<<c[i]->Vin<<" "<<endl; 
                        }
                    else if (c[i]->Vin>0 && c[i]->xPos<50.0)   //deceleration part for car c[i]
                        {
                        c[i]->Vin=c[i]->Vin-c[i]->Acc;
                        c[i]->yPos=0;
                        c[i]->xPos=c[i]->xPos+c[i]->Vin;
                        //c[i]->time=c[i]->time+1;
                        cout<< "Position car:"<<i+1<<"("<<c[i]->xPos<<" , "<<c[i]->yPos<<"),  v_car= "<<c[i]->Vin<<" "<<endl; 
                        }
                    }
            } while (time<55);     //simulation time (55 units in this case)

        }
        
      
    
    






