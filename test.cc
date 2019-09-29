#include <iostream>
#include <time.h>
#include "contour.h"
using namespace std;


int main () {

 char inputfilename[200];
 char outputfilename[200];
 clock_t t1,t2;
 contour rf ;
 cout<<"Enter the input filename::";
 cin>>inputfilename;
 cout<<"Enter the Output filename ::";
 cin>>outputfilename;
 cout<<"Reading a EsriFile format"<<endl;
 rf.readfile(inputfilename);
 cout<<"Reading complete"<<endl;
 cout<<"Outputting Segment Regions and Holes "<<endl;
 t1=clock();
 rf.region_seg_list_output(outputfilename); 
 t2=clock();
 cout<<"Outputting Segment Regions and Holes done"<<endl;
 float diff ((float)t2-(float)t1);
 cout<<"Total time :: "<<diff/CLOCKS_PER_SEC<<endl;
}
 
 

  
