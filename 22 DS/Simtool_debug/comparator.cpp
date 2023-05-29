#include <iostream>
#include <fstream>
#include <windows.h>
using std::cin, std::cout, std::endl;
using std::ifstream;
using std::string;
void SetColor(WORD forecolor = 4, WORD backgroudcolor = 0)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, forecolor | backgroudcolor);
}
void cut_space(string &s)
{
    for (auto i = s.begin(); i != s.end(); i++)
        if (*i == ' ' && (i == s.begin() || *(i - 1) == ' ' || i + 1 == s.end()))
            s.erase(i--);
}
int max_diffs = 10;
int main(int argc, char **argv)
{
    if (argc > 4 || argc < 3)
        return cout << "Error: Wrong number of arguments." << endl, 1;
    ifstream fin1(argv[1]);
    ifstream fin2(argv[2]);
    if (argc == 4)
        max_diffs = atoi(argv[3]);
    if (!fin1.is_open())
        return cout << "Error: Cannot open file " << argv[1] << endl, 1;
    if (!fin2.is_open())
        return cout << "Error: Cannot open file " << argv[2] << endl, 1;
    int line = 0, flag = 0;
    while (!fin1.eof() && !fin2.eof())
    {
        string expected, found;
        getline(fin1, expected);
        getline(fin2, found);
        line++;
        cut_space(expected);
        cut_space(found);
        if (expected != found)
        {
            if (flag++ == max_diffs)
            {
                cout << "Too many differences." << endl;
                SetColor(7, 0);
                return 0;
            }
            SetColor(4, 0);
            cout << "Difference at line " << line << endl;
            SetColor(7, 0);
            cout << "Expected: " << expected << endl;
            cout << "Found:    " << found << endl;
            cout << "          ";
            SetColor(4, 0);
            auto i = expected.begin(), j = found.begin();
            for (; i != expected.end() && j != found.end(); i++, j++)
                cout << (*i == *j ? ' ' : '^');
            for (; i != expected.end(); i++)
                cout << '^';
            for (; j != found.end(); j++)
                cout << '^';
            cout << endl;
        }
    }
    auto &fin = fin1.eof() ? fin2 : fin1;
    string s;
    while (getline(fin, s))
        if (!s.empty())
        {
            SetColor(4, 0);
            cout << "Different number of lines." << endl;
            SetColor(7, 0);
            cout << "The surplus line is: " << s << endl;
            return 0;
        }
    SetColor(2, 0);
    if (!flag)
        cout << "Same" << endl;
    SetColor(7, 0);
    return 0;
}