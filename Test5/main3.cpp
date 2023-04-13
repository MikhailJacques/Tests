//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <thread>
//#include <mutex>
//#include <chrono>
//
//using namespace std;
//
//// Define a struct to hold the data for each file
//struct FileData 
//{
//    string filename;
//    vector<string> words;
//    mutex words_mutex;
//};
//
////struct FileData
////{
////    string filename;
////    vector<string> words;
////    mutex words_mutex;
////
////    // Move constructor
////    FileData(FileData&& other) noexcept
////    {
////        filename = move(other.filename);
////        words = move(other.words);
////    }
////};
//
//// Function to read a file and store the words in a vector
//void read_file(FileData* file_data) 
//{
//    ifstream file(file_data->filename);
//
//    if (file.is_open()) 
//    {
//        string word;
//
//        while (file >> word) 
//        {
//            // Remove punctuation marks
//            // word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
//            // word.erase(remove_if(word.begin(), word.end(), ::isalpha), word.end());
//            word.erase(remove_if(word.begin(), word.end(), [](unsigned char c) { return !isalpha(c); }), word.end());
//
//            // Convert to lowercase
//            transform(word.begin(), word.end(), word.begin(), ::tolower);
//
//            // Add the word to the vector
//            lock_guard<mutex> guard(file_data->words_mutex);
//            file_data->words.push_back(word);
//        }
//    }
//}
//
//// Function to write the combined and sorted words to a file
//void write_file(vector<string> words, string filename, char split_char, bool ascending) 
//{
//    // Sort the words lexicographically
//    if (ascending) 
//    {
//        sort(words.begin(), words.end());
//    }
//    else 
//    {
//        sort(words.rbegin(), words.rend());
//    }
//
//    // Remove duplicates
//    // (removes all but the first element from every consecutive group of equivalent elements from 
//    // the range [first, last) and returns a past-the-end iterator for the new logical end of the range)
//    auto last = unique(words.begin(), words.end());
//    words.erase(last, words.end());
//
//    // Write the words to the file
//    ofstream file(filename);
//
//    if (file.is_open()) 
//    {
//        for (auto word : words) 
//        {
//            file << word << split_char;
//        }
//    }
//}
//
//// Function to get the most frequent word from a vector of words
//string get_most_frequent_word(vector<string> words) 
//{
//    string most_frequent_word;
//    int max_count = 0;
//
//    for (auto word : words) 
//    {
//        int count = count_if(words.begin(), words.end(), [&](string w) { return w == word; });
//
//        if (count > max_count) 
//        {
//            max_count = count;
//            most_frequent_word = word;
//        }
//    }
//
//    return most_frequent_word;
//}
//
//int main(int argc, char* argv[]) 
//{
//    // Get the filenames from the command line arguments
//    vector<string> filenames;
//    for (int i = 1; i < argc; i++) 
//    {
//        filenames.push_back(argv[i]);
//    }
//
//    // Read the files in different threads
//    vector<FileData> files_data(filenames.size());
//    vector<thread> threads;
//
//    for (int i = 0; i < filenames.size(); i++) 
//    {
//        files_data[i].filename = filenames[i];
//        threads.push_back(thread(read_file, &files_data[i]));
//    }
//
//    for (auto& thread : threads) 
//    {
//        thread.join();
//    }
//
//    // Combine the words from all files
//    vector<string> all_words;
//
//    // for (auto file_data : files_data) 
//    for (int i = 0; i < files_data.size(); i++)
//    {
//       // all_words.insert(all_words.end(), file_data.words.begin(), file_data.words.end());
//       all_words.insert(all_words.end(), files_data[i].words.begin(), files_data[i].words.end());
//    }
//
//    // Write the combined and sorted words to a file
//    string output_filename = "F4.txt";
//    char split_char = ' ';
//    bool ascending = true;
//    string sort_option, split_option;
//
//    cout << "enter your options:" << endl;
//    cout << "sort [-a, -d]: ";
//    cin >> sort_option;
//
//    if (sort_option == "-d") 
//    {
//        ascending = false;
//    }
//
//    cout << "split [-s, -c, -n]: ";
//    cin >> split_option;
//
//    if (split_option == "-c") 
//    {
//        split_char = ',';
//    }
//    else if (split_option == "-n") 
//    {
//        split_char = '\n';
//    }
//
//    write_file(all_words, output_filename, split_char, ascending);
//
//    // Get the most frequent word and its count
//    string most_frequent_word = get_most_frequent_word(all_words);
//
//    int count = count_if(all_words.begin(), all_words.end(), [&](string w) { return w == most_frequent_word; });
//
//    // Print the result
//    cout << "The most frequent word in all files is '" << most_frequent_word << "', count: " << count << endl;
//
//    return 0;
//}