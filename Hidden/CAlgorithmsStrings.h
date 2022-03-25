#pragma once
namespace Forradia
{
class CAlgorithmsStrings
{
public:
    inline void Split(const String& in, std::vector<String>& out, String token)
    {
        out.clear();

        String temp;

        for (auto i = 0; i < int(in.size()); i++)
        {
            String test = in.substr(i, token.size());

            if (test == token)
            {
                if (!temp.empty())
                {
                    out.push_back(temp);
                    temp.clear();
                    i += (int)token.size() - 1;
                }
                else
                {
                    out.push_back("");
                }
            }
            else if (i + token.size() >= in.size())
            {
                temp += in.substr(i, token.size());
                out.push_back(temp);
                break;
            }
            else
            {
                temp += in[i];
            }
        }
    }
    inline String Tail(const String& in)
    {
        size_t tokenStart = in.find_first_not_of(" \t");
        size_t spaceStart = in.find_first_of(" \t", tokenStart);
        size_t tailStart = in.find_first_not_of(" \t", spaceStart);
        size_t tailEnd = in.find_last_not_of(" \t");
        if (tailStart != String::npos && tailEnd != String::npos)
        {
            return in.substr(tailStart, tailEnd - tailStart + 1);
        }
        else if (tailStart != String::npos)
        {
            return in.substr(tailStart);
        }
        return "";
    }
    inline String FirstToken(const std::string& in)
    {
        if (!in.empty())
        {
            size_t token_start = in.find_first_not_of(" \t");
            size_t token_end = in.find_first_of(" \t", token_start);
            if (token_start != String::npos && token_end != String::npos)
            {
                return in.substr(token_start, token_end - token_start);
            }
            else if (token_start != String::npos)
            {
                return in.substr(token_start);
            }
        }
        return "";
    }
};
}
