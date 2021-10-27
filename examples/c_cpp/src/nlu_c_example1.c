#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <wchar.h>
#include <string.h>
#include "texsmart_util.h"
#include "texsmart_nlu_api.h"

#ifndef nullptr
#   define nullptr NULL
#endif

void PrintNluOutput(const NluOutputHandle output)
{
    int str_len = 0;
    const wchar_t *norm_str = Nlu_GetNormText(output, &str_len);
    printf("Norm text:\n");
    Util_PrintUnicodeString(norm_str, true);

    printf("Word-level segmentation:\n");
    NluTermArray term_list = Nlu_GetWords(output);
    uint32_t idx = 0;
    for (; idx < term_list.size; idx++)
    {
        const NluTerm *term = &term_list.items[idx];
        printf("\t");
        Util_PrintUnicodeString(term->str, false);
        printf("\t(%u, %u)\t", term->offset, term->len);
        Util_PrintUnicodeString(term->tag, false);
        printf("\n");
    }
    printf("\n");

    printf("Phrase-level segmentation:\n");
    term_list = Nlu_GetPhrases(output);
    for (idx = 0; idx < term_list.size; idx++)
    {
        const NluTerm *term = &term_list.items[idx];
        printf("\t");
        Util_PrintUnicodeString(term->str, false);
        printf("\t(%u, %u)\t", term->offset, term->len);
        Util_PrintUnicodeString(term->tag, false);
        printf("\n");
    }
    printf("\n");

    NluEntityArray entity_list = Nlu_GetEntities(output);
    printf("Entities:\n");
    for (idx = 0; idx < entity_list.size; idx++)
    {
        const NluEntity *entity = &entity_list.items[idx];
        printf("\t");
        Util_PrintUnicodeString(entity->str, false);
        printf("\t(%u, %u)\t(", entity->offset, entity->len);
        Util_PrintUnicodeString(entity->type.name, false);
        printf(",");
        Util_PrintUnicodeString(entity->type.i18n, false);
        printf(",%u,", entity->type.flag);
        Util_PrintUnicodeString(entity->type.path, false);
        printf(")\t");
        Util_PrintUnicodeString(entity->meaning, false);
        printf("\n");
    }
}

bool NluExample(const char *data_dir)
{
    printf("Creating and initializing the NLU engine (about 10 seconds)...\r\n");
    int worker_count = 4;
    NluEngineHandle engine_handle = Nlu_CreateEngine(data_dir, worker_count);
    if (engine_handle == nullptr)
    {
        printf("Failed to initialize the NLU engine\n");
        return false;
    }

    printf("=== Parse a piece of English text ===\n");
    const wchar_t *text = L"John Smith stayed in San Francisco last month.";
    NluOutputHandle output = Nlu_ParseText(engine_handle, text, (int)wcslen(text));
    if (output == nullptr) {
        printf("Error occurred in parsing text\n");
        return false;
    }

    PrintNluOutput(output);
    Nlu_DestroyOutput(output);

    printf("=== Parse Chinese text ===\n");
    text = L"上个月30号，南昌王先生在自己家里边看流浪地球边吃煲仔饭";
    output = Nlu_ParseText(engine_handle, text, (int)wcslen(text));
    if (output == nullptr) {
        printf("Error occurred in parsing text\n");
        return false;
    }

    PrintNluOutput(output);
    Nlu_DestroyOutput(output);

    Nlu_DestroyEngine(engine_handle);
    return true;
}

int main(int argc, const char *argv[])
{
    char data_dir[1024] = "../../../../data/nlu/kb/";
    if (argc > 1) {
        strcpy(data_dir, argv[1]);
    }

    bool ret = NluExample(data_dir);
    return ret ? 0 : -1;
};
