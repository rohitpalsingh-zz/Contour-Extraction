
using namespace std;


class contour {

   
  public :
          contour();
         // Reads the input file grids into original_matrix and NCOLS, NROWS, XLLCORNER, YLLCORNER, CELLSIZE, NODATA_VALUE 
          void readfile (char* filename); 
         //Write to a file Region Segment in a counter clockwise order for regions with holes.
          void region_seg_list_output(char *s);

  private : 
          struct cell
          {
           int intensity;    // This holds the intesity value of the cell.
           bool visited;     // This keep track of the visited and Un visited cells.
           bool pairleft;        // This flag is meant for boundary cells.  If true means that a boundary of a outer cycle has a pair of boundarycells at that vertical level. 
           bool pairright;
           bool holeleft;
           bool holeright;         // This is to indicate holes inside a outercycle. 
           };

          cell** original_matrix;  // Original matrix
          int NCOLS ;  // number of coloumn
          int NROWS ;  // number of rows
          float XLLCORNER;  // western most x coordinate
          float YLLCORNER;  // southern most y coordinate 
          float CELLSIZE;   // one side of a square cell
          int NODATA_VALUE; // missing or not applicable data value
          // List the outercycle coordinates in counter-clockwise order.
          void get_outercycle(int i, int j,int regionid,std::ofstream& outfile, bool ishole);
          // Hunt for hole cycles at each vertical level. If there is one calls the below function.
          void get_holecycles(int i, int j,std::ofstream& outfile);    
          };



