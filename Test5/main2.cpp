
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <future>
#include <iterator>

using namespace std;

// User input options
typedef struct
{
    unsigned char order;            // a = ascending, d = descending
    unsigned char spliting_char;    // s = white space, c = coma, n = new line
} Options;

typedef struct
{
    Options options;
    vector<string> files_paths;
    string output_file_path;
} Params;

void ReadTextFiles(const vector<string>& paths);
void ReadTextFile(const string& path);

void SpawnWritingThread(const Params& params);
void WriteTextFile(const Params& params);

void ReadUserCommands(Options& options);
void RemoveSpecialCharacters(string& token);

static mutex mtx;
static map<string, unsigned int> ordered_map;

int main(int argc, char** argv)
{
    Params params = { {'a', 's'}, {}, "" };
    params.output_file_path.assign("F4.txt");

    // Read in and store command line arguments (no error checking is done!)
    for (int i = 1; i < argc; ++i)
    {
        params.files_paths.push_back(string(argv[i]));
    }

    ReadUserCommands(params.options);

    ReadTextFiles(params.files_paths);

    SpawnWritingThread(params);

    cout << "The file F4 has been created.\n";

    return 0;
}

// This function utilizes the C++ async function template that is used to execute the ReadTextFile function asynchronously, 
// meaning a new thread is created to execute the ReadTextFile function while the main program continues to run.
// The std::future object that is returned can be used to check the state of the asynchronous task, get its result, or wait for its completion.
void ReadTextFiles(const vector<string>& paths)
{
    for (const auto& path : paths)
    {
        std::async(std::launch::async, ReadTextFile, path);
    }
}

// This function opens a text file, reads words from it one word at a time, 
// stores the read word in an opdered map container where it keeps track of its associated count
// Since the opdered map container is accessed by multiple threads simultaneously it is protected by a mutex
void ReadTextFile(const string& file_path)
{
    if (file_path.empty() == false)
    {
        ifstream file(file_path);

        if (file.is_open())
        {
            string token;

            while (file >> token)
            {
                RemoveSpecialCharacters(token);

                if (token.empty() == false)
                {
                    lock_guard<mutex> lock(mtx); // RAII, exeption safe
                    ordered_map[token]++;
                }
            }

            file.close();
        }
    }
}

// This function spawns a thread that writes to a text file
void SpawnWritingThread(const Params& params)
{
    thread th(&WriteTextFile, params);

    if (th.joinable())
        th.join();
}

// This function reads opens/creates a new text file, reads the words from an ordered map while keeping track of the most frequent word
// and writes the read words to the previously opened text file while separating them by a user-defined delimeting character
void WriteTextFile(const Params& params)
{
    ofstream output_file(params.output_file_path, ios::out);

    if (output_file.is_open())
    {
        string most_frequent_word, delimeter;
        unsigned int most_frequent_word_cnt = 1;

        switch (params.options.spliting_char)
        {
            case 's':

                delimeter.assign(" ");  // 34
                break;

            case 'c':

                delimeter.assign(",");  // 44
                break;

            case 'n':

                delimeter.assign("\n"); // 92 + 110
                break;
        }

        if (params.options.order == 'a')
        {
            // Using structured bindings
            for (const auto&[word, cnt] : ordered_map)
            {
                if (most_frequent_word_cnt < cnt)
                {
                    most_frequent_word.assign(word);
                    most_frequent_word_cnt = cnt;
                }

                // Note: In the ascending order the program prints the delimiting character after the last word, which it should NOT do.
                output_file << word << delimeter;
            }
        }
        else // params.options.order = 'd'
        {
            for (auto it = ordered_map.rbegin(); it != ordered_map.rend(); it++)
            {
                if (most_frequent_word_cnt < it->second)
                {
                    most_frequent_word.assign(it->first);
                    most_frequent_word_cnt = it->second;
                }

                output_file << it->first;

                // Determine whether or not to print the delimiting character
                // Check to see whether the next element is the last one in the map
                if (std::next(it) != ordered_map.rend())
                {
                    output_file << delimeter;
                }
            }
        }

        output_file << "\n\nThe most frequent word in the text is: '"
            << most_frequent_word << "', count: " << most_frequent_word_cnt;

        output_file.close();
    }
}

// This function reads in user commands entered via the command line. 
// It validates each command and stores them in the Options argument
// Output: Valid commands 
void ReadUserCommands(Options& options)
{
    bool go = false;
    string user_input;

    options.order = ' ';
    options.spliting_char = ' ';

    cout << "Valid options: \n"
        << "    sort[-a, -d]\n"
        << "    split[-s, -c, -n]\n"
        << "    go\n" << endl;

    cout << "Enter your options: \n";
    getline(cin, user_input);

    do
    {
        if (user_input.compare("sort -a") == 0)
        {
            options.order = 'a';
        }
        else if (user_input.compare("sort -d") == 0)
        {
            options.order = 'd';
        }
        else if (user_input.compare("split -s") == 0)
        {
            options.spliting_char = 's';
        }
        else if (user_input.compare("split -c") == 0)
        {
            options.spliting_char = 'c';
        }
        else if (user_input.compare("split -n") == 0)
        {
            options.spliting_char = 'n';
        }
        else if (user_input.compare("go") == 0)
        {
            if ((options.order != ' ') && (options.spliting_char != ' '))
            {
                go = true;
            }
            else
            {
                cout << "Please select sort and split options first." << endl;
            }
        }
        else
        {
            cout << "Invalid entry! Please try again.\n"
                << "Valid options: \n"
                << "    sort[-a, -d]\n"
                << "    split[-s, -c, -n]\n"
                << "    go\n"
                << "Enter your options: \n";
        }

        if (go == false)
            getline(cin, user_input);

    } while (go == false);
}

// This function removes special characters from a string token (word) and converts all alpabetic characters to lower case
// Output: A string token that consists only of alpabetic characters in lower case
void RemoveSpecialCharacters(string& token)
{
    // Remove elements satisfying predicate "not alphabetic character"
    // remove_if() - transforms the range [first, last) into a range with all the elements for which pred returns true removed and 
    //               returns an iterator to the new end of that range.
    // Note: Use empty capture closure because no variables are used by lambda which means it can only access variables that are local to it.
    // std::string::iterator new_end = remove_if(token.begin(), token.end(), [](unsigned char c) { return !isalpha(c); });

    // Compact/compress the token (if necessary)
    // erase() - erases the sequence of characters in the range [first, last).
    // token.erase(new_end, token.end());

    token.erase(remove_if(token.begin(), token.end(), [](unsigned char c) { return !isalpha(c); }), token.end());

    // Convert the token to lowercase (if necessary)
    // transform() - applies an operation sequentially to the elements of one (1) or two (2) ranges and 
    // stores the result in the range that begins at result.
    // transform(token.begin(), token.end(), token.begin(), [](unsigned char c) { return tolower(c); });

    if (token.empty() == false)
    {
        transform(token.begin(), token.end(), token.begin(), ::tolower);
    }
}