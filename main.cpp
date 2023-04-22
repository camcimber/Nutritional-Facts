#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Minerals{
private:
    //string carb, protein, sodium, fiber, sugar;
    string category, description;
    unsigned int finder, finder2; // used for parsing "description"

public:

   void parsing(){
        ifstream inputFile;
        inputFile.open("nutritional-facts.csv");

        string line = "";
        while(getline(inputFile, line)){

            stringstream inputString(line);
            getline(inputString, category, ',');

            //parse to get description
            getline(inputString, description, ',');

            //some descriptions have quotes and other do not
            if (description.front() == '"') {
                finder = line.find('"');
                description = line.substr( finder + 1);
                finder2 = description.find('"');
                description = description.substr(0, finder2);
            }

            //parse to get carbohydrates
            string carb = "";
            for (int i = 0; i < 6; i++) {
                getline(inputString, carb, ',');
            }

            //parse for cholesterol -> in progress, not printing correct value
            string cholesterol = "";
            for (int i = 0; i < 7; i++) {
                getline(inputString, cholesterol, ',');
            }
            cout << cholesterol << endl;

        }
   }


};
int main() {
    Minerals nutrition;

    nutrition.parsing();
    return 0;
}
