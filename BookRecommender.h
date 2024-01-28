#ifndef BOOKRECOMMENDER_H_
#define BOOKRECOMMENDER_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

class BookRecommender {
    private:
        vector<string> books;
        vector<string> users;
        map<string, vector<double>> ratedBooks;
        map<string, double> averages;
        
    public:
        BookRecommender() = default;
        BookRecommender(string fileName);
 
        void printRecommend(string userName);
        void printAverages();      
 
        double getAverage(string bookTitle);
        double getSimilarity(string userName1, string userName2);
        int getBookCount();
        int getUserCount();
        double getUserBookRating(string userName, string bookTitle);
};
  

#endif
