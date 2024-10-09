// STT:
// Full Name: Nguyễn An Đức
// Student ID: 22520268
// Session 01 - Exercise 01
// Notes or Remarks: ......

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//----------------QUESTION 1-------------------
struct Song {
    string songName;
    Song *nextSong;
    Song *prevSong;

    Song(string s) : songName(s), nextSong(nullptr), prevSong(nullptr) {}
};

struct Playlist {
    Song *firstSong;
    Song *lastSong;

    Playlist() : firstSong(nullptr), lastSong(nullptr) {}

    void ADD(string s) {
        Song *newSong = new Song(s);
        if (!firstSong) {
            firstSong = newSong;
            lastSong = newSong;
            firstSong->nextSong = firstSong;
            firstSong->prevSong = firstSong;
        }
        else {
            newSong->prevSong = lastSong;
            lastSong->nextSong = newSong;
            firstSong->prevSong = newSong;
            newSong->nextSong = firstSong;
            lastSong = newSong;
        }
    }

    void NEXT() {
        if (firstSong) {
            firstSong = firstSong->nextSong;
        }
    }

    void PREV() {
        if (firstSong) {
            firstSong = firstSong->prevSong;
        }
    }

    void REMOVE(string s)
    {
        if (!firstSong) {
            return;
        }

        Song *current = firstSong;

        if (firstSong == lastSong && firstSong->songName == s) {
            delete firstSong;
            firstSong = nullptr;
            lastSong = nullptr;
            return;
        }

        while (true) {
            if (current->songName == s) {
                if (current == firstSong) {
                    firstSong = current->nextSong;
                    if (firstSong != nullptr) {
                        firstSong->prevSong = lastSong;
                        lastSong->nextSong = firstSong;
                    }
                }
                else if (current == lastSong) {
                    lastSong = current->prevSong;
                    lastSong->nextSong = firstSong;
                    firstSong->prevSong = lastSong;
                }
                else {
                    current->prevSong->nextSong = current->nextSong;
                    current->nextSong->prevSong = current->prevSong;
                }
                delete current;
                return;
            }
            current = current->nextSong;

            if (current == firstSong) {
                break;
            }
        }
    }

    void DISPLAY() {
        if (!firstSong) {
            return;
        }
        
        Song *current = firstSong;
        do {
            cout << current->songName << endl;
            current = current->nextSong;
        } while (current != firstSong);
    }
};

void operation(Playlist &list) {
    string oper;
    cin >> oper;

    if (oper == "ADD") {
        string s;
        cin >> s;
        list.ADD(s);
    }
    else if (oper == "NEXT") {
        list.NEXT();
    }
    else if (oper == "PREV") {
        list.PREV();
    }
    else if (oper == "REMOVE") {
        string s;
        cin >> s;
        list.REMOVE(s);
    }
    else if (oper == "DISPLAY") {
        list.DISPLAY();
    }
    else {
        cout << "Invalid operation." << endl;
        operation(list);
    }
}

void Question1()
{
    Playlist list;
    int nOper;
    cin >> nOper;

    for (int i = 0; i < nOper; i++) {
        operation(list);
    }
}

/* 
1. How would you handle edge cases, such as trying to remove a song that doesn’t exist?

In my implementation, if the song to be removed doesn’t exist in the playlist, the REMOVE function will traverse the list and check each song. If it reaches back to the firstSong without finding a match, it will simply exit the function. This approach ensures that the function handles the case of a non-existent song gracefully without causing any errors or crashes.

2. How can you efficiently loop back to the start or end of the list?

In my playlist structure, the linked list is circular. When the firstSong is set to the nextSong of the current song in the NEXT function, if we reach the end of the list, we naturally loop back to the start because the nextSong of the last song points back to firstSong. Similarly, in the PREV function, navigating backwards will wrap around to the last song when we go before the firstSong. This circular structure allows for efficient looping in both directions without needing additional checks for bounds.

3. What data structure(s) would you use to implement this playlist, and why?

I chose a doubly linked list as the underlying data structure for the playlist. This allows for efficient insertions and deletions of songs at any position. The doubly linked aspect enables easy traversal both forwards and backwards, which is essential for the NEXT and PREV operations. Additionally, the circular nature of the list allows seamless navigation from the last song back to the first, which aligns with how playlists are typically used.

4. How would you ensure that operations like NEXT and PREV are efficient, given the constraints?

To ensure efficiency in the NEXT and PREV operations, I keep track of the firstSong, which allows for constant time complexity O(1) for both operations. Since the list is circular, moving to the next or previous song does not require iterating through the entire list; I simply update the pointer to the appropriate song. This structure allows both operations to be performed quickly, regardless of the number of songs in the playlist.
*/


//----------------QUESTION 2-------------------
struct Page {
    string URL;
    Page *next;
    Page *prev;

    Page(string url) : URL(url), next(nullptr), prev(nullptr) {}
};

class BrowserHistory {
    Page *head;
    Page *tail;
    Page *current;

public:
    BrowserHistory(string homepage) {
        head = new Page(homepage);
        tail = head;
        current = head;
    }

    void visit(string url) {
        Page *newPage = new Page(url);
        current->next = newPage;
        newPage->prev = current;
        current = newPage;
        tail = newPage;
    }

    string back(int steps) {
        while (steps > 0 && current->prev) {
            current = current->prev;
            steps--;
        }
        return current->URL;
    }

    string forward(int steps) {
        while (steps > 0 && current->next) {
            current = current->next;
            steps--;
        }
        return current->URL;
    }
};

void Question2() {
    vector<string> commands;
    vector<string> params;

    cout << "Enter commands (type 0 to end):" << endl;
    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "0") break;
        commands.push_back(cmd);
    }

    cout << "Enter parameters for each command:" << endl;
    for (size_t i = 0; i < commands.size(); i++) {
        string param;
        cin >> param;
        params.push_back(param);
    }

    BrowserHistory browser(params[0]);
    vector<string> output;
    output.push_back("null");

    for (size_t i = 1; i < commands.size(); i++) {
        if (commands[i] == "visit") {
            browser.visit(params[i]);
            output.push_back("null");
        } else if (commands[i] == "back") {
            output.push_back(browser.back(stoi(params[i])));
        } else if (commands[i] == "forward") {
            output.push_back(browser.forward(stoi(params[i])));
        }
    }

    for (const auto &url : output) {
        cout << url << " ";
    }
}

//----------------QUESTION 3-------------------
struct AuthToken {
    string id;
    int expiryTime;
    AuthToken *next;
    AuthToken(string tokenId, int expiration) : id(tokenId), expiryTime(expiration), next(nullptr) {}
};

struct AuthManager {
    int ttl;
    AuthToken *head;

    AuthManager(int timeToLive) : ttl(timeToLive), head(nullptr) {}

    void createToken(string tokenId, int currentTime) {
        int expiration = currentTime + ttl;
        AuthToken *newToken = new AuthToken(tokenId, expiration);
        newToken->next = head;
        head = newToken;
    }

    void extendToken(string tokenId, int currentTime) {
        AuthToken *current = head;
        while (current != nullptr) {
            if (current->id == tokenId && current->expiryTime > currentTime) {
                current->expiryTime = currentTime + ttl;
                return;
            }
            current = current->next;
        }
    }

    int countActiveTokens(int currentTime) {
        int activeCount = 0;
        AuthToken *current = head;
        while (current != nullptr) {
            if (current->expiryTime > currentTime) {
                activeCount++;
            }
            current = current->next;
        }
        return activeCount;
    }
};

void Question3() {
    vector<string> commands;
    string command;
    
    cout << "Enter commands (type 0 to end):" << endl;
    while (cin >> command) {
        if (command == "0") break;
        commands.push_back(command);
    }

    cout << "Enter parameters for each command:" << endl;

    AuthManager *manager = nullptr;

    if (commands[0] != "AuthenticationManager") {
        cout << "The first command must be AuthenticationManager.";
        return;
    } else {
        int ttl;
        cin >> ttl;
        manager = new AuthManager(ttl);
        cout << "null ";
    }

    for (size_t i = 1; i < commands.size(); i++) {
        if (commands[i] == "generate" || commands[i] == "renew") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime;
            if (commands[i] == "generate") {
                manager->createToken(tokenId, currentTime);
                cout << "null ";
            } else {
                manager->extendToken(tokenId, currentTime);
                cout << "null ";
            }
        } else if (commands[i] == "countUnexpiredTokens") {
            int currentTime;
            cin >> currentTime;
            cout << manager->countActiveTokens(currentTime) << " ";
        }
    }
}

int main()
{
    cout << "Select a problem to run (1-3): ";
    int option;
    cin >> option;

    switch (option) {
    case 1:
        Question1();
        break;
    case 2:
        Question2();
        break;
    case 3:
        Question3();
        break;
    default:
        break;
    }
    return 0;
}