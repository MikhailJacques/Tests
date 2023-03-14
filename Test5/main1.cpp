//
//#include <map>
//#include <mutex>
//#include <vector>
//#include <string>
//#include <thread>
//#include <fstream>
//#include <iostream>
//#include <algorithm>
//
////#include<windows.h>
//// CRITICAL_SECTION file_cs;
//
//using namespace std;
//
//// User input options
//typedef struct
//{
//    unsigned char order;            // a = ascending, d = descending
//    unsigned char spliting_char;    // s = white space, c = coma, n = new line
//} Options;
//
//typedef struct
//{
//    Options options;
//    vector<string> input_files_paths;
//    string output_file_path;
//} Params;
//
//void SpawnReadingThreads(const Params& params);
////void SpawnReadingThreads(const vector<string>& paths);
//void ReadTextFile(const string& file_path);
//
//void SpawnWritingThread(const Params& params);
//void WriteTextFile(const Params& params);
//
//void ReadUserCommands(Options& options);
//void RemoveSpecialCharacters(string& token);
//
//static mutex mtx;
//static map<string, unsigned int> ordered_map;
//
//int main(int argc, char** argv) 
//{
//    Params params = { {'a', 's'}, {}, "" };
//    params.output_file_path.assign("F4.txt");
//
//    // Read in and store command line arguments (no error checking is done!)
//    for (int i = 1; i < argc; ++i)
//    {
//        params.input_files_paths.push_back(string(argv[i]));
//    }
//
//    ReadUserCommands(params.options);
//
//    // InitializeCriticalSection(&file_cs);
//
//    SpawnReadingThreads(params);
//
//    SpawnWritingThread(params);
//
//    cout << "The file F4 has been created.\n";
//
//	return 0;
//}
//
//// This function spawns threads that read words from text files concurrently (one thread per file)
//void SpawnReadingThreads(const Params& params)
////void SpawnReadingThreads(const vector<string>& input_files_paths)
//{
//    vector<thread> threads;
//    threads.reserve(params.input_files_paths.size());
//
//    for (int i = 0; i < params.input_files_paths.size(); i++)
//    {
//        thread th(&ReadTextFile, params.input_files_paths[i]);
//        threads.push_back(move(th));
//    }
//
//    for (thread& th : threads)
//    {
//        if (th.joinable())
//            th.join();
//    }
//}
//
//// This function opens a text file, reads words from it one word at a time, 
//// stores the read word in an opdered map container where it keeps track of its associated count
//// Since the opdered map container is accessed by multiple threads simultaneously it is protected by a mutex
//void ReadTextFile(const string& file_path)
//{
//    if (file_path.empty() == false)
//    {
//        //EnterCriticalSection(&file_cs);
//        //cout << "Thread ID: " << this_thread::get_id() << " processes file: " << file_path << endl;
//        //LeaveCriticalSection(&file_cs);
//
//        ifstream file(file_path);
//
//        if (file.is_open())
//        {
//            string token;
//
//            while (file >> token)
//            {
//                RemoveSpecialCharacters(token);
//
//                if (token.empty() == false)
//                {
//                    mtx.lock();
//                    ordered_map[token]++;
//                    mtx.unlock();
//                }
//            }
//
//            file.close();
//        }
//    }
//}
//
//// This function spawns a thread that writes to a text file
//void SpawnWritingThread(const Params& params)
//{
//    thread th(&WriteTextFile, params);
//
//    if (th.joinable())
//        th.join();
//}
//
//// This function reads opens/creates a new text file, reads the words from an ordered map while keeping track of the most frequent word
//// and writes the read words to the previously opened text file while separating them by a user-defined delimeting character
//void WriteTextFile(const Params& params)
//{
//    ofstream output_file(params.output_file_path, ios::out);
//
//    if (output_file.is_open())
//    {
//        string most_frequent_word, delimeter;
//        unsigned int most_frequent_word_cnt = 1;
//
//        switch (params.options.spliting_char)
//        {
//            case 's': 
//
//                delimeter.assign(" ");  // 34
//                break;    
//
//            case 'c': 
//
//                delimeter.assign(",");  // 44
//                break;   
//
//            case 'n': 
//
//                delimeter.assign("\n"); // 92 + 110
//                break;    
//        }
//
//        if (params.options.order == 'a')
//        {
//            for (auto const& pair : ordered_map)
//            {
//                if (most_frequent_word_cnt < pair.second)
//                {
//                    most_frequent_word.assign(pair.first);
//                    most_frequent_word_cnt = pair.second;
//                }
//
//                output_file << pair.first << delimeter;
//            }
//        }
//        else // params.options.order = 'd'
//        {
//            for (auto it = ordered_map.rbegin(); it != ordered_map.rend(); it++)
//            {
//                if (most_frequent_word_cnt < it->second)
//                {
//                    most_frequent_word.assign(it->first);
//                    most_frequent_word_cnt = it->second;
//                }
//
//                output_file << it->first << delimeter;
//            }
//        }
//
//        // Note: This program prints the delimiting character after the last word, which it should NOT do.
//        output_file << "\nThe most frequent word in the text is: '"
//            << most_frequent_word << "', count: " << most_frequent_word_cnt;
//
//        output_file.close();
//    }
//}
//
//// This function reads in user commands entered via the command line. 
//// It validates each command and stores them in the Options argument
//// Output: Valid commands 
//void ReadUserCommands(Options& options)
//{
//    bool go = false;
//    string user_input;
//
//    options.order = ' ';
//    options.spliting_char = ' ';
//
//    cout << "Valid options: \n"
//        << "    sort[-a, -d]\n"
//        << "    split[-s, -c, -n]\n"
//        << "    go\n" << endl;
//
//    cout << "Enter your options: \n";
//    getline(cin, user_input);
//
//    do
//    {
//        if (user_input.compare("sort -a") == 0)
//        {
//            options.order = 'a';
//        }
//        else if (user_input.compare("sort -d") == 0)
//        {
//            options.order = 'd';
//        }
//        else if (user_input.compare("split -s") == 0)
//        {
//            options.spliting_char = 's';
//        }
//        else if (user_input.compare("split -c") == 0)
//        {
//            options.spliting_char = 'c';
//        }
//        else if (user_input.compare("split -n") == 0)
//        {
//            options.spliting_char = 'n';
//        }
//        else if (user_input.compare("go") == 0)
//        {
//            if ((options.order != ' ') && (options.spliting_char != ' '))
//            {
//                go = true;
//            }
//            else
//            {
//                cout << "Please select sort and split options first." << endl;
//            }
//        }
//        else
//        {
//            cout << "Invalid entry! Please try again.\n"
//                << "Valid options: \n"
//                << "    sort[-a, -d]\n"
//                << "    split[-s, -c, -n]\n"
//                << "    go\n"
//                << "Enter your options: \n";
//        }
//
//        if (go == false)
//        {
//            getline(cin, user_input);
//        }
//
//    } while (go == false);
//}
//
//// This function removes special characters from a string token (word) and converts all alpabetic characters to lower case
//// Output: A string token that consists only of alpabetic characters in lower case
//void RemoveSpecialCharacters(string& token)
//{
//    for (unsigned int i = 0; i < token.size(); i++)
//    {
//        // if (!((token[i] >= 'A' && token[i] <= 'Z') || (token[i] >= 'a' && token[i] <= 'z')))
//        // if (!((token[i] >= 65 && token[i] <= 90) || (token[i] >= 97 && token[i] <= 122)))
//        if ((token[i] < 'A' || token[i] > 'Z') && (token[i] < 'a' || token[i] > 'z'))
//        {
//            token.erase(i, 1);
//            i--;
//        }
//        else
//        {
//            //if (token[i] <= 'Z' && token[i] >= 'A')
//            //    token[i] = token[i] - ('Z' - 'z');
//
//            token[i] = tolower(token[i]);
//        }
//    }
//}