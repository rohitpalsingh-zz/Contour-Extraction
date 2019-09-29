#include<iostream> 
#include<stdio.h> 
#include<stdlib.h>  
#include<fstream> 
#include"contour.h"

using namespace std ;

/**********************************************Definition of Public members functions***********************************************/

//Construtorinitialize the value of all variables to zero
   
	contour::contour()
	{
  	    NCOLS = 0 ;
	    NROWS = 0 ;
	    CELLSIZE = 0.0 ;
	    NODATA_VALUE = 0 ;
	    XLLCORNER = 0.0 ;
	    YLLCORNER = 0.0 ;
        }
 
//Function to read Input file into "Input grid Matrix and all the associated variables"
 
	void contour :: readfile ( char *  filename ) 
	  {
	    bool space_flag = false ,decimal_flag= false , negative_flag = false;
	    int row_count = 0 , col_count = 0 ,col =0;	
	    int current_character, num = 1;
	    float decimal_value = 0;
	    FILE  * fp = fopen ( filename ,  "r" );
   
// Reading a file character by character and extract a relevant information
// Store the grid in an original_matrix
// Store all the variables

	     if ( !fp )        
	      {
	      cout<<"FILE NOT FOUND"<<endl ;        
	      }
             else 
	     {
	     while   ( ( current_character= fgetc ( fp ) )  != EOF ) 
	          {
	          if(row_count==2&&col==0)
	             {
	               original_matrix = (cell**) malloc(NROWS*sizeof(cell*));  
	                 for (int i = 0; i < NROWS; i++)  
	                    original_matrix[i] = (cell*) malloc(NCOLS*sizeof(cell)); 
		              for (int i = 0 ;i<NROWS ;i++ ) 
		              	for (int j = 0 ;j<NCOLS ;j++ ) 
                		  {  
                		   original_matrix[i][j].intensity=0;
                		   original_matrix[i][j].visited=false;
                		   original_matrix[i][j].pairleft=false;
                                   original_matrix[i][j].holeleft=false;
                		   original_matrix[i][j].pairright=false;
                                   original_matrix[i][j].holeright=false;
                		  }
                      }

         	  if ( row_count > 5 )
         	    {
         	        if ( col%4 == 0 ) 
                	 {  
                	     if ( current_character == 49 ) 
                	       original_matrix[row_count-6][col_count].intensity = 1 ;
                	     if ( current_character == 50 ) 
                	       original_matrix[row_count-6][col_count].intensity = 2 ;     
                	     if ( current_character == 48 ) 
                	       original_matrix[row_count-6][col_count].intensity = 0 ;
                	     col_count++ ;
	                 } 
        	       col++;
                    }   
          	 else
                   {
	              if(space_flag == true && current_character!= 10 && current_character!= 13)
               		{
// Reading a NCOls variable 
	               if ( row_count == 0)     
	                 {
	                  NCOLS = NCOLS * 10 +   ( current_character- 48 )  ;                              
	                 }
// Reading a NROWS Variable
	               if ( row_count == 1) 
	                 {
	                  NROWS = NROWS * 10 +   ( current_character- 48 )  ;
	                 }
// Reading a XLLCORNER Variable
	               if ( row_count == 2 && current_character!= 46 && current_character!= 45)  
	                 {
	                  if (decimal_flag == false ) 
	                   {
	                    XLLCORNER = XLLCORNER * 10 +   ( current_character- 48 )  ;
	                   }
	                  if (decimal_flag == true  ) 
	                   {
	                    decimal_value= decimal_value* 10  +   ( current_character- 48 )  ;
	                    num*=10; ; 
	                   } 
	                 }
// Reading a YLLCORNER Variable 
	               if ( row_count == 3 && current_character!= 46 && current_character!= 45)     
	                 { 
	                  if (decimal_flag == false) 
	                   {
	                    YLLCORNER =  YLLCORNER * 10 +   ( current_character- 48 )  ;
	                   }
	                  if (decimal_flag == true) 
	                   {
	                    decimal_value= decimal_value* 10  +   ( current_character- 48 )  ;
	                    num*=10; ; 
	                   } 
	                 }
// Reading  a CELLSIZE Variable
	               if ( row_count == 4 && current_character!= 46 && current_character!= 45)  
	                 {
	                  if (decimal_flag == false ) 
	                   {
	                    CELLSIZE = CELLSIZE * 10 +   ( current_character- 48 )  ;
	                   }
	                  if (decimal_flag == true) 
	                   {
	                    decimal_value= decimal_value* 10  +   ( current_character- 48 )  ;
	                    num*=10; 
	                   } 
	                 }             
// Reading a NODATA_VALUE Variable
	               if ( row_count == 5 && current_character!= 45)   
	                { 
	                 NODATA_VALUE = NODATA_VALUE * 10 +   ( current_character- 48 )  ;
	                }
	               }
// Set the corresponding flag to true
	               if ( current_character== 46 ) 
	                 {
	                  decimal_flag= true ;
	                 } 
	               if ( current_character== 32 ) 
	                 {
	                  space_flag = true ;
	                 }
	               if ( current_character== 45 ) 
	                 {
	                  negative_flag = true ;
	                 }
	              
// Adding sign (NODATA_VALUE) and decimal parts to a XLLCORNER, YLLCORNER, CELLSIZE
	               if ( current_character== 10)                                                                       
	                {
	                 if ( row_count == 2 ) 
	                  {
	                   XLLCORNER = XLLCORNER  +   ( decimal_value/num )  ;
	                   if ( negative_flag == true ) 
	                    XLLCORNER =  - XLLCORNER ; 
	                  }
	                 if ( row_count == 3 ) 
	                  {
	                   YLLCORNER = YLLCORNER  +   ( decimal_value/num )  ;
	                   if ( negative_flag == true ) 
	                    YLLCORNER =  - YLLCORNER ;
	                  }   
	                 if ( row_count == 4 ) 
	                  {
	                   CELLSIZE = CELLSIZE  +   ( decimal_value/num )  ;
	                  }
	                 if ( row_count == 5 ) 
	                  {
	                   if ( negative_flag == true )                
                    NODATA_VALUE =  - NODATA_VALUE ;
	                  }
	                }
	              }
// Setting and Resetting all the variables before starting with next row.
	           if(current_character== 10)             
	             {
	              space_flag = false ;
	              negative_flag = false ;
	              decimal_flag= false ;
	              decimal_value= 0 ;
	              col_count = 0 ;   
	              col=0;  
	              num = 1 ;
	              row_count++ ;              
	             }
	        }
	     }
	  fclose ( fp ) ;
	}


// Outputs the segment list of Regions and Holes
	
       void contour :: region_seg_list_output(char * s)
	{
         ofstream outfile;
         int regionid=0,t,pkg;
         outfile.open (s);  
         
         if (!outfile.is_open())
         {
           cout << "Error opening file";
         }
          for (int i =0 ;i<NROWS; i++ ) 
           for (int j = 0 ;j<NCOLS; j++ ) 
	     {
	      if(original_matrix[i][j].visited==false)
               { 
                 get_outercycle(i,j,regionid,outfile,false);        // Private Function to list the outercyclecoordinates in counterclockwise order
                 get_holecycles(i,j,outfile);                 // Private Function to list the holecycles(if any) inside the above outercycle
                 regionid++;  
               }
             }

        }



/************************************************************Definition of Private Member Functions************************************************/


// This function traverses the outercycle cells and write to file the co-ordinates of outercycle in counter-clockwise order.

// Another role of this function is to set a pair flags( defined in documentation) and visited flags(defined in documentation).


       void contour :: get_outercycle(int i, int j, int regionid,std::ofstream& outfile,bool ishole)
            {
                
                int p,q,cdirection=2,pdirection=0,INTENSITYLEVEL=0,m,cont=0 ,c=0;
                INTENSITYLEVEL=original_matrix[i][j].intensity;
                
                if(ishole)
                 { 
                  outfile<<"\n"<<"HOLE ID :: "<<regionid<<"\n";
                  outfile<<"HOLE COORDINATES ::  { ("<<XLLCORNER+(j*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-i)*CELLSIZE)<<") ";      
                 }
                else
                 {
                  outfile<<"\n"<<"REGION ID :: "<<regionid<<"\n";
                  outfile<<"INTENSITYLEVEL :: "<<INTENSITYLEVEL<<"\n";
                  outfile<<"REGION COORDINATES ::  { ("<<XLLCORNER+(j*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-i)*CELLSIZE)<<") ";   
                 }  
               p=i;
               q=j;
               pdirection=0; 
               cdirection=2;
            // do while loop.. loops around the outercycle when the loop is complete it terminates 
               do   
                {
            // logic to set the flags while traversing a direction is different for all directions.
            // Variable c and m whereever used is used to single out the first cell in that direction.
                      if(cdirection==2)
                        { m=p; 
                          while(p<NROWS-1) 
                              { 
                               if (original_matrix[p+1][q].intensity!=INTENSITYLEVEL||(m!=p&&q>0&&original_matrix[p][q-1].intensity==INTENSITYLEVEL))
                                   break;
                                 else
                                 {  
// First If is for the first cell in this direction and else part is for the rest except last.
                                  original_matrix[p][q].pairleft = true;                                                                          
                                 }
                               p++;
                              }
                            
// This is for the last cell in this direction. 
                         }
                      else if(cdirection==3)
                         { m=q;
                            
                            while( q>0)
                              {
                               if (original_matrix[p][q-1].intensity!=INTENSITYLEVEL||(m!=q&&p>0&&original_matrix[p-1][q].intensity==INTENSITYLEVEL))
                                   break;
                                 
                                q--;  
                              }
                        } 
                       else if(cdirection==1)
                         { m=q;
                            while(q<NCOLS-1)
                              {
                               if (original_matrix[p][q+1].intensity!=INTENSITYLEVEL||(m!=q&&p<NROWS-1&&original_matrix[p+1][q].intensity==INTENSITYLEVEL))
                                   break;  
                                 
                               q++;
                             }
                         } 
                       else if(cdirection==4)
                         { m=p;
                           c=0;
                             while(p>0)
                              {
                          if (original_matrix[p-1][q].intensity!=INTENSITYLEVEL||(m!=p&&q<NCOLS-1&&original_matrix[p][q+1].intensity==INTENSITYLEVEL))
                                   break; 
                                else
                                 { 
// This is for the first cell in this direction and else is for the rest except last.
                                   if(c==1)
                                   original_matrix[p][q].pairright=true; 
                                   c=1;
                                 }  
                                p--;
                              }
                              original_matrix[p][q].pairright=true; 
                           } 
          // Setting new direction based on previous direction and new surrounding cells
                       pdirection=cdirection;

                       if(pdirection==2)
                         {
                            if(q!=0&&original_matrix[p][q-1].intensity==INTENSITYLEVEL)
                            cdirection=3;
                            else if(q!=NCOLS-1&&original_matrix[p][q+1].intensity==INTENSITYLEVEL)
                            cdirection=1;
                         }
                       else if(pdirection==3)
                          {
                            if(p!=0&&original_matrix[p-1][q].intensity==INTENSITYLEVEL)
                            cdirection=4;
                            else if(p!=NROWS-1&&original_matrix[p+1][q].intensity==INTENSITYLEVEL)
                            cdirection=2;
                          }
                       else if(pdirection==4)
                         {
                            if(q!=NCOLS-1&&original_matrix[p][q+1].intensity==INTENSITYLEVEL)
                            cdirection=1;
                            else if(q!=0&&original_matrix[p][q-1].intensity==INTENSITYLEVEL)
                            cdirection=3;
                          }
                       else if(pdirection==1)
                          {
                            if(p!=NROWS-1&&original_matrix[p+1][q].intensity==INTENSITYLEVEL)
                            cdirection=2;
                            else if(p!=0&&original_matrix[p-1][q].intensity==INTENSITYLEVEL)
                            cdirection=4;
                          }
             // This is the case when there is a U turn. Happens when we did't find any cell in the surroundings  .     
                     if(pdirection==cdirection)
                          {
                           if(pdirection==1)
                           {  outfile<<"("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p-1)*CELLSIZE)<<") ("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ";
                             cdirection=3;
                           }
                          else  if(pdirection==2)
                           {
                           outfile<<"("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p-1)*CELLSIZE)<<") ("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p-1)*CELLSIZE)<<") ";
                             cdirection=4; 
                           }
                          else  if(pdirection==3)
                           {
                            if(!(p==i&&q==j))
                           outfile<<"("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p-1)*CELLSIZE)<<") ";
                             else
                           outfile<<"("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") "; 
                            cdirection=1; 
                           }
                          else  if(pdirection==4)
                           {
                           outfile<<"("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ";
                             cdirection=2; 
                          }                
                        }
                       else
                         {
                     if((pdirection==1&&cdirection==4)||(pdirection==4&&cdirection==1))
                          outfile<<"("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p-1)*CELLSIZE)<<") ";
                     if((pdirection==2&&cdirection==1)||(pdirection==1&&cdirection==2)) 
                          outfile<<"("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p-1)*CELLSIZE)<<") "; 
                     if((pdirection==3&&cdirection==2)||(pdirection==2&&cdirection==3)) 
                          outfile<<"("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ";
                     if((pdirection==4&&cdirection==3)||(pdirection==3&&cdirection==4)) 
                          outfile<<"("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ";
                       }
              // This condition is for a special inverted L like shapes where starting point is traversed more than two times without ending the loop.
//////////////////////
//     
//     ||||||||
//     ||              This type of shape
//     || 
//     ||
//
/////////////////////     
                   if((pdirection==4||pdirection==2)&&cdirection==1&&p==i&q==j)
                           cont=1;
                   else
                           cont=0;
                   }  
                while(!(p==i&&q==j&&cont==0));
                 
   // This is for wrap around.

                if(cdirection==4)
                  outfile<<"("<<XLLCORNER+((q+1)*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<") ("<<XLLCORNER+(q*CELLSIZE)<<" , "<<YLLCORNER+((NROWS-p)*CELLSIZE)<<")  }\n\n";
                else
                  outfile<<"  }\n\n";


            }


// This function loop around exactly the same way as the above function do. But it do some thing in addition. It make use of the pair flag( set in above function ) to scan horizontly the inside of the cycle at that vertical height to figure out the holes(if any) at that vertical level.
// And it repeats this for every vertical level.  
// Here c is used to avoid a special case.

    void contour :: get_holecycles(int i, int j,std::ofstream& outfile)
       {

       int holeid=0,p,q,cdirection=2,pdirection=0,INTENSITYLEVEL=0,m,cont=0,x=0;
                INTENSITYLEVEL=original_matrix[i][j].intensity;
               p=i;
               q=j;
               pdirection=0; 
               cdirection=2;
                 do
                {
// When cdirection is 2 means we are going through vertical level downward and only during this direction we check the horizontal insides of outercycle at that vertical level 
// 
                      if(cdirection==2)   
                        { m=p; 
                            while(p<NROWS-1)
                              {  
                               if (original_matrix[p+1][q].intensity!=INTENSITYLEVEL||(m!=p&&q>0&&original_matrix[p][q-1].intensity==INTENSITYLEVEL))
                                  break;
                                 else
                                 {      
                                  if(original_matrix[p][q].pairleft==true&&original_matrix[p][q].pairright==false)
                                     { x=q;
                                        do 
                                         {
//   This condition is to skip the already identified hole regions. 
                                              if(original_matrix[p][x].holeleft==true)
                                                 { 
                                                  do
                                                    {
                                                    x++;
                                                    }    
                                                  while(!(original_matrix[p][x].holeright==true&&original_matrix[p][x].holeleft==false));
                                                 }
                                              if(original_matrix[p][x].intensity!=INTENSITYLEVEL)
                                                 {
//  This is where we have identified an hole and we call a function to list its coordinates.
                                                 get_outercycle(p,x,holeid,outfile,true);
                                                 holeid++;
                                                     while(!(original_matrix[p][x].holeright==true&&original_matrix[p][x].holeleft==false))
                                                     {
                                                      x++;
                                                     } 
                                                   
                                                 }
                                         if(original_matrix[p][x].pairright==false)
                                            x++; 
                                         original_matrix[p][x].visited = true;
                                         }
                                       while(original_matrix[p][x].pairright==false);
                                     }
                                 }
                               p++;
                              }                         
                          } 
                      else if(cdirection==3)
                         { m=q;
                               while( q>0)
                              {
                               if (original_matrix[p][q-1].intensity!=INTENSITYLEVEL||(m!=q&&p>0&&original_matrix[p-1][q].intensity==INTENSITYLEVEL))
                                   break;
                                q--;
                             
                              }
                         
                          } 
                       else if(cdirection==1)
                         { m=q;
                             while(q<NCOLS-1)
                              {
                          if (original_matrix[p][q+1].intensity!=INTENSITYLEVEL||(m!=q&&p<NROWS-1&&original_matrix[p+1][q].intensity==INTENSITYLEVEL))
                                   break;  
                               q++;
                               }
                          } 
                       else if(cdirection==4)
                         { m=p;
                              while(p>0)
                              {
                          if (original_matrix[p-1][q].intensity!=INTENSITYLEVEL||(m!=p&&q<NCOLS-1&&original_matrix[p][q+1].intensity==INTENSITYLEVEL))
                                   break; 
                               
                                p--;
                              }
                           } 

                       pdirection=cdirection;

                       if(pdirection==2)
                         {
                            if(q!=0&&original_matrix[p][q-1].intensity==INTENSITYLEVEL)
                            cdirection=3;
                            else if(q!=NCOLS-1&&original_matrix[p][q+1].intensity==INTENSITYLEVEL)
                            cdirection=1;
                         }
                       else if(pdirection==3)
                          {
                            if(p!=0&&original_matrix[p-1][q].intensity==INTENSITYLEVEL)
                            cdirection=4;
                            else if(p!=NROWS-1&&original_matrix[p+1][q].intensity==INTENSITYLEVEL)
                            cdirection=2;
                          }
                       else if(pdirection==4)
                         {
                            if(q!=NCOLS-1&&original_matrix[p][q+1].intensity==INTENSITYLEVEL)
                            cdirection=1;
                            else if(q!=0&&original_matrix[p][q-1].intensity==INTENSITYLEVEL)
                            cdirection=3;
                          }
                       else if(pdirection==1)
                          {
                            if(p!=NROWS-1&&original_matrix[p+1][q].intensity==INTENSITYLEVEL)
                            cdirection=2;
                            else if(p!=0&&original_matrix[p-1][q].intensity==INTENSITYLEVEL)
                            cdirection=4;
                          }
                    
                     if(pdirection==cdirection)
                          {
                           if(pdirection==1)
                            cdirection=3;
                           else  if(pdirection==2)
                            cdirection=4; 
                           else  if(pdirection==3)
                            cdirection=1; 
                           else  if(pdirection==4)
                            cdirection=2; 
                           }
                      
                 
                   if((pdirection==4||pdirection==2)&&cdirection==1&&p==i&&q==j)
                      cont=1;
                    else
                      cont=0;
                    
                 }  
                while(!(p==i&&q==j&&cont==0));
              
       }

//Thats All ..Thank You For Viewing
