// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "AlgorithmsStrings.h"

namespace Forradia
{

    void AlgorithmsStrings::Split(const std::string& in, std::vector<std::string>* out, std::string token)
    {

        out->clear();

        std::string temp;

        for (unsigned int i = 0; i < in.size(); i++)
        {
            std::string test = in.substr(i, token.size());

            if (test == token)
            {
                if (!temp.empty())
                {
                    out->push_back(temp);
                    temp.clear();
                    i += token.size() - 1;
                }
                else
                {
                    out->push_back("");
                }
            }
            else if (i + token.size() >= in.size())
            {
                temp += in.substr(i, token.size());
                out->push_back(temp);

                break;
            }
            else
            {
                temp += in[i];
            }
        }
    }

    std::string AlgorithmsStrings::Tail(const std::string& in)
    {
        size_t tokenStart = in.find_first_not_of(" \t");
        size_t spaceStart = in.find_first_of(" \t", tokenStart);
        size_t tailStart = in.find_first_not_of(" \t", spaceStart);
        size_t tailEnd = in.find_last_not_of(" \t");

        if (tailStart != std::string::npos && tailEnd != std::string::npos)
            return in.substr(tailStart, tailEnd - tailStart + 1);
        else if (tailStart != std::string::npos)
            return in.substr(tailStart);

        return "";
    }

    std::string AlgorithmsStrings::FirstToken(const std::string& in)
    {
        if (!in.empty())
        {
            size_t token_start = in.find_first_not_of(" \t");
            size_t token_end = in.find_first_of(" \t", token_start);

            if (token_start != std::string::npos && token_end != std::string::npos)
                return in.substr(token_start, token_end - token_start);
            else if (token_start != std::string::npos)
                return in.substr(token_start);
        }

        return "";
    }

}