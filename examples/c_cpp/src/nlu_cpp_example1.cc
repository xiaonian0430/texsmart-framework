#include <string>
#include <iostream>
#include <sstream>
#include "texsmart_util.h"
#include "texsmart_nlu_api.h"

using namespace std;
using namespace tencent::ai::texsmart;

void PrintNluOutput(const NluOutput &output)
{
    const wchar_t *norm_text = output.GetNormText(nullptr);
    cout << endl << "Norm text: ";
    Util_PrintUnicodeString(norm_text, true);

    const int buf_len = 4096;
    wchar_t buf[buf_len];
    cout << endl << "Word-level segmentation:" << endl;
    NluTermArray term_list = output.GetWords();
    for(uint32_t idx = 0; idx < term_list.size; idx++)
    {
        const auto &term = term_list.items[idx];
        swprintf(buf, buf_len, L"\t%ls\t(%u, %u)\t%ls", term.str, term.offset, term.len, term.tag);
        Util_PrintUnicodeString(buf, true);
    }

    cout << endl << "Phrase-level segmentation:" << endl;
    term_list = output.GetPhrases();
    for (uint32_t idx = 0; idx < term_list.size; idx++)
    {
        const auto &term = term_list.items[idx];
        swprintf(buf, buf_len, L"\t%ls\t(%u, %u)\t%ls", term.str, term.offset, term.len, term.tag);
        Util_PrintUnicodeString(buf, true);
    }

    cout << endl << "Entities:" << endl;
    NluEntityArray entity_list = output.GetEntities();
    for(uint32_t idx = 0; idx < entity_list.size; idx++)
    {
        const auto &entity = entity_list.items[idx];
        swprintf(buf, buf_len, L"\t%ls\t(%u, %u)\t(%ls,%ls,%u,%ls)\t%ls",
            entity.str, entity.offset, entity.len, entity.type.name,
            entity.type.i18n, entity.type.flag, entity.type.path,
            entity.meaning);
        Util_PrintUnicodeString(buf, true);
    }
}

bool NluExample(const string &data_dir)
{
    cout << "Initializing the NLU engine (about 10 seconds)..." << endl;
    NluEngine engine;
    int worker_count = 4;
    bool ret = engine.Init(data_dir.c_str(), worker_count);
    if (!ret) {
        cout << "Failed to initialize the NLU engine" << endl;
        return false;
    }

    cout << "=== Parse a piece of English text ===" << endl;
    wstring text = L"John Smith stayed in San Francisco last month.";
    NluOutput output;
    ret = engine.ParseText(output, text.c_str(), (int)text.size());
    if (!ret) {
        cout << "Error occurred in parsing text" << endl;
        return false;
    }

    PrintNluOutput(output);

    cout << "=== Parse Chinese text ===" << endl;
    text = L"上个月30号，南昌王先生在自己家里边看流浪地球边吃煲仔饭。";
    ret = engine.ParseText(output, text.c_str(), (int)text.size());
    if (!ret) {
        cout << "Error occurred in parsing text" << endl;
        return false;
    }

    PrintNluOutput(output);
    return ret;
}

int main(int argc, const char *argv[])
{
    string data_dir = "../../../../data/nlu/kb/";
    if (argc > 1) {
        data_dir = argv[1];
    }

    bool ret = NluExample(data_dir);
    return ret ? 0 : -1;
};
