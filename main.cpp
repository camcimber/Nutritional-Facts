#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Minerals{
private:
    double carb, protein, sodium, fiber, sugar;
    string category, description;

public:
   Minerals(){
       carb = 0.0;
       protein = 0.0;
       sodium = 0.0;
       fiber = 0.0;
       sugar = 0.0;
   }
   void parsing(){
        ifstream inputFile;
        inputFile.open("nutritional-facts.csv");

        string line = "";
        while(getline(inputFile, line)){

            stringstream inputString(line);
            getline(inputString, category, ',');

        }
   }


};
int main() {
    Minerals nutrition;
    return 0;
}
