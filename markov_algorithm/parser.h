#pragma once

#include"headers.h"


class parser
{
    const string TRANSITION = "->";
    const string FINAL_TRANSITION = "=>";
    const string DEPRECATED_SYMBOLS = "->=";

public:

    parser()
    {
    }

    vector<sub> get_subs(const vector<string>& input)
    {
        vector<sub> subs = vector<sub>();

        for (int i = 0; i < input.size(); i++)
        {
            if (input[i].find(TRANSITION) == string::npos && input[i].find(FINAL_TRANSITION) == string::npos)
                throw invalid_argument("Неверный ввод");

            bool is_final = input[i].find(FINAL_TRANSITION) != string::npos;
            size_t trans_pos = input[i].find(is_final ? FINAL_TRANSITION : TRANSITION);

            string from = trans_pos == (0) ? "" : input[i].substr(0, trans_pos);

            if (from.find_first_of(DEPRECATED_SYMBOLS) != string::npos)
                throw invalid_argument("Неверный ввод");

            string to = trans_pos == (input[i].length() - 1) ? "" : input[i].substr(trans_pos + 2);

            if (to.find_first_of(DEPRECATED_SYMBOLS) != string::npos)
                throw invalid_argument("Неверный ввод");

            subs.push_back({ from,to,is_final });
        }

        return subs;
    }

    string check_word(string& w)
    {
        if (w.find_first_of(DEPRECATED_SYMBOLS) != string::npos)
            throw invalid_argument("Слово содержит запрещенные символы");
        return w;
    }
};