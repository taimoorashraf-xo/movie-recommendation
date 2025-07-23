#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct movie {
    string title;
    string genre;
    string mood;
    float rating;
};
const string filename = "movies.txt";
string toLower(string str) {
    for (char& c : str) c = tolower(c);
    return str;
}
void loadmovies(vector<movie>& movies) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file.\n";
        return;
    }
    string title, genre, mood;
    float rating;
    while (getline(file, title, ',') &&
           getline(file, genre, ',') &&
           getline(file, mood, ',') &&
           file >> rating) {
        file.ignore();
        movie m;
        m.title = title;
        m.genre = genre;
        m.mood = mood;
        m.rating = rating;
        movies.push_back(m);
    }
    file.close();
}

void savemovies(const vector<movie>& movies) {
    ofstream file(filename);
    for (int i = 0; i < movies.size(); i++) {
        file << movies[i].title << ","
             << movies[i].genre << ","
             << movies[i].mood << ","
             << movies[i].rating << "\n";
    }
    file.close();
}

void addmovie(vector<movie>& movies) {
    movie m;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, m.title);
    cout << "Enter genre: ";
    getline(cin, m.genre);
    cout << "Enter mood: ";
    getline(cin, m.mood);
    cout << "Enter rating (0–10): ";
    while (!(cin >> m.rating) || m.rating < 0 || m.rating > 10) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid rating. Please enter a number between 0 and 10: ";
    }
    cin.ignore();
    movies.push_back(m);
    cout << "Movie added!\n";
}

void showmovies(const vector<movie>& movies) {
    cout << "\nAll Movies:\n";
    for (int i = 0; i < movies.size(); i++) {
        cout << i + 1 << ". " << movies[i].title
             << " (" << movies[i].genre << ", "
             << movies[i].mood << ", Rating: "
             << movies[i].rating << ")\n";
    }
}

void updatemovie(vector<movie>& movies) {
    string title;
    cout << "Enter title of the movie to update: ";
    getline(cin, title);
    for (int i = 0; i < movies.size(); i++) {
        if (toLower(movies[i].title) == toLower(title)) {
            cout << "Enter new title: ";
            getline(cin, movies[i].title);
            cout << "Enter new genre: ";
            getline(cin, movies[i].genre);
            cout << "Enter new mood: ";
            getline(cin, movies[i].mood);
            cout << "Enter new rating: ";
            while (!(cin >> movies[i].rating) || movies[i].rating < 0 || movies[i].rating > 10) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid rating. Please enter a number between 0 and 10: ";
            }
            cin.ignore();
            cout << "Movie updated!\n";
            return;
        }
    }
    cout << "Movie not found.\n";
}

void deletemovie(vector<movie>& movies) {
    string title;
    cin.ignore();
    cout << "Enter title of the movie to delete: ";
    getline(cin, title);
    for (int i = 0; i < movies.size(); i++) {
        if (toLower(movies[i].title) == toLower(title)) {
            movies.erase(movies.begin() + i);
            cout << "Movie deleted.\n";
            return;
        }
    }
    cout << "Movie not found.\n";
}

void searchbymood(const vector<movie>& movies) {
    string mood;
    cin.ignore();
    cout << "Enter mood: ";
    getline(cin, mood);
    cout << "Movies with mood '" << mood << "':\n";
    for (int i = 0; i < movies.size(); i++) {
        if (toLower(movies[i].mood) == toLower(mood)) {
            cout << "- " << movies[i].title << " (" << movies[i].genre << ", Rating: " << movies[i].rating << ")\n";
        }
    }
}

void searchbygenre(const vector<movie>& movies) {
    string genre;
    cin.ignore();
    cout << "Enter genre: ";
    getline(cin, genre);
    cout << "Movies in genre '" << genre << "':\n";
    for (int i = 0; i < movies.size(); i++) {
        if (toLower(movies[i].genre) == toLower(genre)) {
            cout << "- " << movies[i].title << " (Mood: " << movies[i].mood << ", Rating: " << movies[i].rating << ")\n";
        }
    }
}

void searchbyrating(const vector<movie>& movies) {
    float minRating;
    cout << "Enter minimum rating (0–10): ";
    while (!(cin >> minRating) || minRating < 0 || minRating > 10) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter rating between 0 and 10: ";
    }
    cin.ignore();
    cout << "Movies with rating >= " << minRating << ":\n";
    for (int i = 0; i < movies.size(); i++) {
        if (movies[i].rating >= minRating) {
            cout << "- " << movies[i].title << " (" << movies[i].genre << ", Mood: " << movies[i].mood << ")\n";
        }
    }
}
int main() {
    vector<movie> movies;
    loadmovies(movies);
    int choice;
    while (true) {
        cout << "\nMovie Manager and your personalised recommender when you're too bored to think for yourself :P\n";
        cout << "1. Show All Movies\n";
        cout << "2. Add Movie\n";
        cout << "3. Update Movie\n";
        cout << "4. Delete Movie\n";
        cout << "5. Search by Mood\n";
        cout << "6. Search by Genre\n";
        cout << "7. Search by Rating\n";
        cout << "8. Save and Exit\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }

        switch (choice) {
            case 1: showmovies(movies); break;
            case 2: addmovie(movies); break;
            case 3: updatemovie(movies); break;
            case 4: deletemovie(movies); break;
            case 5: searchbymood(movies); break;
            case 6: searchbygenre(movies); break;
            case 7: searchbyrating(movies); break;
            case 8:
                savemovies(movies);
                cout << "Saved! Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
