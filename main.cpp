#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Minerals{
private:
    double carb, protein, sodium, fiber, sugar;
    string category, description;
    unsigned int finder, finder2; // used for parsing "description"

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

            //parse to get description
            finder = line.find('"');
            //some descriptions have quotes and other do not
            if(finder){
                description = line.substr(finder+1);
                finder2 = description.find('"');
                description = description.substr(0, finder2);
            }
            else{
                getline(inputString, description, ',');
            }
          //  cout << "category: " << category << " description : " << description << endl;

            //parse to get carbohydrates -> work in progress
//            string temp;
//            for (int i = 0; i < 6; i++) {
//                getline(inputString, temp, ',');
//            }

            // Extract the number after the 6th comma
            //getline(inputString, temp, ',');
            //int number = stoi(temp);


        }
   }


};
int main() {
    Minerals nutrition;

    nutrition.parsing();
    return 0;
}
