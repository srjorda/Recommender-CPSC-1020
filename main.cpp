/*******************************************************************************
File: main.cpp
Name: Samuel Jordan
Proj: Project 4: Recommender
Due : Saturday, April 22, 2023
Desc: A program that reads the name of a ratings file from the command line, 
      then takes people's book ratings and makes book recommendations for them 
      based on similar users. The user has 3 options: averages, recommend, quit.
Time: 4 hours 30 min
*******************************************************************************/
#include "BookRecommender.h"

int main(int argc, char* argv[]) {
    // recommender system set up using command line argument file
    BookRecommender recommender(argv[1]);
    string choice;
    
    do {
        getline(cin, choice);
         //cout << "********** " << choice << " ***********" << endl;
        while(choice != "recommend" 
              && choice != "averages" && choice != "averages "
              && choice != "quit")
            getline(cin, choice);
        
        if(choice == "recommend") {
            getline(cin, choice);
            //cout << "********** " << choice << " ***********" << endl;
            try
                { recommender.printRecommend(choice); }
            catch(string s)
                { recommender.printAverages(); }
        }
        
        if(choice == "averages" || choice == "averages ") {
            recommender.printAverages();
        }
        
    } while(choice != "quit");
    
    return 0;
}
