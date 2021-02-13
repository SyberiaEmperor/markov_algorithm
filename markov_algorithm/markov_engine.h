#pragma once

#include"headers.h"

struct sub
{
    string from;
    string to;
    bool is_final;
};


class markov_engine
{
    const int MAX_OPERATIONS = 10000;

    vector<sub> system;

public:

    markov_engine(const vector<sub>& s) : system(s) {}
    markov_engine() : system(vector<sub>()) {}

    string apply_word(string word)
    {
        bool finish = false;
        int count = 0;

        while (!finish)
        {
            int i = 0;

            for (i = 0; i < system.size(); i++)
            {
                int off_set = word.find(system[i].from);

                if (off_set != string::npos)
                {
                    word.replace(off_set, system[i].from.length(), system[i].to);

                    cerr << word << endl;

                    count++;
                    finish = system[i].is_final;
                    break;
                }
            }

            if (count >= MAX_OPERATIONS)
                throw invalid_argument("ѕревышено максимальное число операций");

            if (i == system.size())
                finish = true;

        }

        return word;
    }

    void set_system(const vector<sub>& s)
    {
        system = s;
    }
};