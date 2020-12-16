#ifndef ENCODE_HPP_
#define ENCODE_HPP_
#include <vector>
#include <string>

class Encode
{
public:
    static std::string EncodeInput(std::string input_line)
    {
        auto f = [](const std::string& input, const std::string& delimiters, std::vector<std::string>& tokens)
          {
          std::string::size_type lastPos = input.find_first_not_of(delimiters, 0);
          std::string::size_type pos = input.find_first_of(delimiters, lastPos);
          while(std::string::npos != pos || std::string::npos != lastPos)
          {
          tokens.push_back(input.substr(lastPos, pos - lastPos));
          lastPos = input.find_first_not_of(delimiters, pos);
          pos = input.find_first_of(delimiters, lastPos);
          }
          };

          std::vector<std::string> words;
          f(input_line, " ",words);
          std::string result("*");
          result += std::to_string(words.size());
          for(const auto& s : words)
          {
          result += std::string("\r\n$") + std::to_string(s.size()) + std::string("\r\n") + s;
          }

          result += std::string("\r\n");
          return result;
    }
};

#endif
