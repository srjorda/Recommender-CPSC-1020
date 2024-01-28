#include "BookRecommender.h"


//  custom comparison function  ************************************************
//  input: two pairs of <string, double>
//  output: boolean, used for sorting vectors of pairs
bool compare(pair<string, double> pair1, pair<string, double> pair2) {
    if(pair1.second == pair2.second)        // if they're the same average,
        return pair1.first < pair2.first;   // then chooses first alphaetically
    return pair1.second > pair2.second;
}


//  constructor  ***************************************************************
//  input: name of input fileName
//  sets up all member variables for the recommender system
BookRecommender::BookRecommender(string fileName) {
    // necessary variables
    string inUser, inBook, inStr;
    int inInt, i;
    
    // input file opened using passed file name
    ifstream inFile;
    inFile.open(fileName);
    if (inFile.is_open() == false) {
        cout << "Error opening input file. Goodbye!" << endl;
        exit(0);
    }
    
    // reading all info into sets and "mega map"
    set<string> userSet, bookSet;
    map<string, map<string, int>> ubrRatings;   // the mega map in question
    while (getline(inFile, inUser)) {   // user name read
        getline(inFile, inBook);        // book name read
        getline(inFile, inStr);         // rating read
        
        // remove carriage return character in user and book
        inUser.erase(remove(inUser.begin(), inUser.end(), '\r'), inUser.end());
        inBook.erase(remove(inBook.begin(), inBook.end(), '\r'), inBook.end());
        
        inInt = stoi(inStr);            // rating converted to int
        userSet.insert(inUser);         // name of user added to set
        bookSet.insert(inBook);         // name of book added to set
        // rating stored in association with book title and with user
        ubrRatings[inUser][inBook] = inInt; 
    }
    
//  users vector finalized
    for(auto x : userSet)
        users.push_back(x);
        
//  books vector finalized
    for(auto x : bookSet)
        books.push_back(x);
    
//  ratedBooks map finalized 
    for(auto u : users)                      
        for(auto b : books)
            ratedBooks[u].push_back(ubrRatings[u][b]); 
    
//  averages map finalized
    for(auto b : bookSet) {                     // for each book,
        i = 0;                                  // reset the count and
        for(auto u : userSet) {                 // go through each user.
            if(ubrRatings[u][b] != 0) {         // if score is non-zero,
                averages[b] += ubrRatings[u][b]; // add it to the total and
                i++;                            // increment count of ratings
            }
        }
        averages[b] /= ((i==0)?(1):(i));         // average, will not divide by 0
    }
}


//  printRecommend  *************************************************************
//  input: username of desired user to base recommendations on
//  output: prints these recommendations to screen
void BookRecommender::printRecommend(string userName) {
    // checks to see if the user exists
    if(count(users.begin(), users.end(), userName) == false)
        throw userName;
    // map of user names and similarity created
    map<string, double> simMap;
    for(auto u : users)
        simMap[u] = getSimilarity(userName, u);
        
    // copy map into a vector of pairs and sort, remove chosen user from list
    vector<pair<string,double>> vector(simMap.begin(), simMap.end());
    sort(vector.begin(), vector.end(), compare);
    vector.erase(vector.begin());
    
    // creates a simulation of the user based on similar users
    map<string, double> simUser;
    for(int i = 0; i < books.size(); i++) {
        int j = 0;  // sum up number of non-zero ratings
        if(ratedBooks[vector[0].first][i] != 0) { j++; }
        if(ratedBooks[vector[1].first][i] != 0) { j++; }
        if(ratedBooks[vector[2].first][i] != 0) { j++; }
        simUser[books[i]] = (ratedBooks[vector[0].first][i] 
                            + ratedBooks[vector[1].first][i]
                            + ratedBooks[vector[2].first][i])
                            / ((j==0)?(1):(j));     // will not divide by zero
    }
    
    // sorts the map as a vector to find the best books
    std::vector<pair<string,double>> bestBooks(simUser.begin(), simUser.end());
    sort(bestBooks.begin(), bestBooks.end(), compare);

    for (auto item : bestBooks) {
        if(item.second > 0) {
            cout << item.first << " "
                 << fixed << setprecision(2) << item.second << endl;
        }
    }
}


//  printAverages  *************************************************************
//  output: prints averages vector to screen
void BookRecommender::printAverages() {  
    // copy rating map into a vector of pairs
    vector<pair<string,double>> vector(averages.begin(), averages.end());
    // sort the vector according to the rating in descending order
    sort(vector.begin(), vector.end(), compare);
    // print out the vector
    for (auto item : vector)
        cout << item.first << " " 
             << fixed << setprecision(2) << item.second << endl;
}


//  getters  *******************************************************************
//  gives the average for a desired book
double BookRecommender::getAverage(string bookTitle)
    { return averages[bookTitle]; }
    
//  gives the similarity value between two users
double BookRecommender::getSimilarity(string userName1, string userName2) {
    double sim = 0;
    for(int i = 0; i < books.size(); i++) {
        sim += ratedBooks[userName1][i] * ratedBooks[userName2][i];
    }
    return sim;
}

//  returns the number of books (size of the books vector)
int BookRecommender::getBookCount()
    { return books.size(); }
    
//  returns the number of users (size of the users vector)
int BookRecommender::getUserCount()
    { return users.size(); }
    
//  returns the rating by a specific user of a specific book 
double BookRecommender::getUserBookRating(string userName, string bookTitle) { 
    int i = 0;
    for(auto x : books) {
        if(x == bookTitle)
            return ratedBooks[userName][i];
        i++;
    }
    return 0;
}
