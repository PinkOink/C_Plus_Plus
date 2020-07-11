#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
  ifstream in("in.txt");//(argv[1]);
  ofstream out("out.txt");

  size_t width = 5;// stoul(argv[2]);
  string str;
  vector<string> words;

  while (getline(in, str)) {
    istringstream strstream(str);
    string word;

    while (strstream >> word) {
      words.push_back(word);
      while (words.back().size() > width) {
        word = words.back().substr(width - 1, words.back().size() - width + 1);
        words.back().erase(width - 1, words.back().size() - width + 1);
        words.back() += '-';
        words.push_back(word);
      }
    }

    while (!words.empty()) {

      size_t CurrentLineLength = 0;
      size_t NumberOfWords = 0;

      while(NumberOfWords < words.size()) {
        if (CurrentLineLength + words[NumberOfWords].size() + !!NumberOfWords > width)
          break;
        else {
          CurrentLineLength += words[NumberOfWords].size() + !!NumberOfWords;
          if (NumberOfWords)
            words[NumberOfWords] = ' ' + words[NumberOfWords];
          NumberOfWords++;
        }
      }

      out << string((width - CurrentLineLength) / 2, ' ');
      for (size_t i = 0; i < NumberOfWords; ++i)
        out << words[i];
      out << endl;

      words.erase(words.begin(), words.begin() + NumberOfWords);
    }
  }

  in.close();
  out.close();
  return 0;
}