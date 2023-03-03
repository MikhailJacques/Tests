//
//#include <map>
//#include <mutex>
//#include <vector>
//#include <string>
//#include <thread>
//#include <fstream>
//#include <iostream>
//#include <algorithm>
//#include <future>
//#include <iterator>
//
//using namespace std;
//
// User input options
//typedef struct
//{
//    unsigned char order;            // a = ascending, d = descending
//    unsigned char spliting_char;    // s = white space, c = coma, n = new line
//} Options;
//
//typedef struct
//{
//    Options options;
//    vector<string> files_paths;
//    string output_file_path;
//} Params;
//
//
//void ProcessTextFiles(const vector<string>& paths);
//void ReadTextFile(const string& path);
//
//void SpawnWritingThread(const Params& params);
//void WriteTextFile(const Params& params);
//
//void ReadUserInput(Options& options);
//void RemoveSpecialCharacters(string& token);
//void RemoveSpecialCharacters2(string& token);
//
//static mutex mtx;
//static map<string, unsigned int> ordered_map;
//
//int main(int argc, char** argv)
//{
//    Params params = { {'a', 's'}, {}, "" };
//    params.output_file_path.assign("F4.txt");
//
//     No error checking is performed
//    for (int i = 1; i < argc; ++i)
//    {
//        params.files_paths.push_back(string(argv[i]));
//    }
//
//    ReadUserInput(params.options);
//
//    ProcessTextFiles(params.files_paths);
//
//    SpawnWritingThread(params);
//
//    return 0;
//}
//
//void ProcessTextFiles(const vector<string>& paths)
//{
//    for (const auto& path : paths)
//    {
//        std::async(std::launch::async, ReadTextFile, path);
//    }
//}
//
//void ReadTextFile(const string& file_path)
//{
//    if (file_path.empty() == false)
//    {
//        ifstream file(file_path);
//
//        if (file.is_open())
//        {
//            string token;
//
//            while (file >> token)
//            {
//                 RemoveSpecialCharacters(token);
//                RemoveSpecialCharacters2(token);
//
//                if (token.empty() == false)
//                {
//                    transform(token.begin(), token.end(), token.begin(), ::tolower);
//
//                    lock_guard<mutex> lock(mtx); // RAII, exeption safe
//
//                    ordered_map[token]++;
//                }
//            }
//
//            file.close();
//        }
//    }
//}
//
//void SpawnWritingThread(const Params& params)
//{
//    thread th(&WriteTextFile, params);
//
//    if (th.joinable())
//        th.join();
//}
//
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
//            case 's': delimeter.assign(" "); break;     // 34
//            case 'c': delimeter.assign(","); break;     // 44
//            case 'n': delimeter.assign("\n"); break;    // 92 + 110
//        }
//
//        if (params.options.order == 'a')
//        {
//            for (const auto& pair : ordered_map)
//            {
//                if (most_frequent_word_cnt < pair.second)
//                {
//                    most_frequent_word.assign(pair.first);
//                    most_frequent_word_cnt = pair.second;
//                }
//
//                // Note: In the ascending order the program prints the delimiting character after the last word
//                output_file << pair.first << delimeter;
//            }
//
//             Using structured bindings
//            for (const auto&[word, cnt] : ordered_map)
//            {
//                if (most_frequent_word_cnt < cnt)
//                {
//                    most_frequent_word.assign(word);
//                    most_frequent_word_cnt = cnt;
//                }
//
//                 Note: In the ascending order the program prints the delimiting character after the last word
//                output_file << word << delimeter;
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
//                output_file << it->first;
//
//                if (std::next(it) != ordered_map.rend())
//                {
//                    output_file << delimeter;
//                }
//            }
//        }
//
//        output_file << "\n\nThe most frequent word in the text is: '"
//            << most_frequent_word << "', count: " << most_frequent_word_cnt;
//
//        output_file.close();
//    }
//}
//
//void ReadUserInput(Options& options)
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
//            getline(cin, user_input);
//
//    } while (go == false);
//}
//
//void RemoveSpecialCharacters(string& token)
//{
//    for (int i = 0; i < token.size(); i++)
//    {
//        if (token[i] < 'A' || token[i] > 'Z' && token[i] < 'a' || token[i] > 'z')
//        {
//            token.erase(i, 1);
//            i--;
//        }
//    }
//}
//
//void RemoveSpecialCharacters2(string& token)
//{
//     Remove special characters
//    token.erase(remove_if(token.begin(), token.end(), [](char c) {
//        return !isalpha(c);
//        }), token.end());
//
//     Convert to lowercase
//    transform(token.begin(), token.end(), token.begin(), [](unsigned char c) {
//        return tolower(c);
//        });
//}