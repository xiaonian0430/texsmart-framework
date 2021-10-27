#include <string>
#include <iostream>
#include <sstream>
#include "texsmart_util.h"
#include "texsmart_nlu_api.h"

using namespace std;
using namespace tencent::ai::texsmart;

bool TextMatchingExample(const string &data_dir)
{
    cout << "Initializing the NLU engine (about 10 seconds)..." << endl;
    NluEngine engine;
    int worker_count = 4;
    bool ret = engine.Init(data_dir.c_str(), worker_count);
    if (!ret) {
        cout << "Failed to initialize the NLU engine" << endl;
        return false;
    }

    cout << "=== Text matching (Chinese text) ===" << endl;
    const wchar_t *str1 = L"我非常喜欢这只小狗";
    const wchar_t *str2 = L"我很爱这条狗";

    TextMatchingOutput output;
    ret = engine.MatchText(output, str1, str2);
    if (!ret || output.Size() < 1)
    {
        cout << "Error occurred in text matching" << endl;
        return false;
    }

    float score = output.ScoreAt(0);
    cout << "text-1: ";
    Util_PrintUnicodeString(str1, true);
    cout << "text-2: ";
    Util_PrintUnicodeString(str2, true);
    cout << "Matching score: " << score << endl;

    return ret;
}

int main(int argc, const char *argv[])
{
    string data_dir = "../../../../data/nlu/kb/";
    if (argc > 1) {
        data_dir = argv[1];
    }

    bool ret = TextMatchingExample(data_dir);
    return ret ? 0 : -1;
};
