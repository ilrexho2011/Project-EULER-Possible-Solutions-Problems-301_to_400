#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int height = 201, width = 201;

void writeMatrixToFile(vector<vector<int> > matrix){
     ofstream myFile;
     myFile.open ("ant.txt");
     
     for (int i = 0; i < height; i++){
          for(int j = 0; j < width; j++){
                  myFile << matrix[i][j];
          }
          myFile << endl;
     }
     
     myFile.close();
}

void writeMovementsToFile(string movements){
     ofstream myFile;
     myFile.open ("movements.txt");
     myFile << movements;
     myFile.close();
}

vector<vector<int> > initMatrix(vector<vector<int> > matrix){
    matrix.resize(height);
    for (int i = 0; i < height; ++i)
        matrix[i].resize(width);
    for (int i = 0 ; i < height; ++i)
          for(int j = 0 ; j < width ; ++j)
                  matrix[i][j]=0;         
    return matrix;   
}

long sumMatrix(vector<vector<int> > matrix){
     long sum = 0;
     for (int i = 0; i < height; i++)
          for(int j = 0; j < width; j++)
                  sum += matrix[i][j];
     return sum;     
}

void printMatrix(vector<vector<int> > matrix){
     for (int i = 0; i < height; i++){
          for(int j = 0; j < width; j++){
                  cout << matrix[i][j];
          }
          cout << endl;
     }
}

int main(){
    int posy = (height-1)/2, posx = (width-1)/2, direction = 1;
    long long iterations = 0;
    string movements = "";
    vector<vector<int> > matrix;
    matrix = initMatrix(matrix);
    
    while ((posx >=0 and posy>=0) and (posx<width and posy<height)){
        if (matrix[posy][posx] == 0){
            matrix[posy][posx] = 1;
            direction = (direction) % 4 + 1;
            movements += "R";
        }
        else{
            matrix[posy][posx] = 0;
            direction -= 1;
            if (direction == 0) direction = 4;
            movements += "L";
        }
        switch(direction){
            case 1:
                 posy -= 1;
                 break;
            case 2:
                 posx += 1;
                 break;
            case 3:
                 posy += 1;
                 break;
            case 4:
                 posx -= 1;
        }

        iterations += 1;          
    }

    
    cout << "Sum of the matrix: " << sumMatrix(matrix) << endl;
    cout << iterations << " iterations.";

    writeMatrixToFile(matrix);
    writeMovementsToFile(movements);
    
    cin.get();
	return 0;
}
