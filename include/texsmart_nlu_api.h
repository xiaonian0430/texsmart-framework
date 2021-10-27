#pragma once

#include <stdint.h>
#ifndef __cplusplus
#   include <stdbool.h>
#endif

#if defined _WIN32
#   ifdef TEXSMART_EXPORTS
#        define TEXSMART_API __declspec(dllexport)
#   else
#       ifdef __GNUC__
#           define TEXSMART_API __attribute__ ((dllimport))
#       else
#           define TEXSMART_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#       endif
#   endif
#else
#   if __GNUC__ >= 4
#       define TEXSMART_API __attribute__ ((visibility ("default")))
#   else
#       define TEXSMART_API
#   endif
#endif

#ifdef __cplusplus    //if used by C++ code
extern "C" {          //we need to export the C interface
namespace tencent {
namespace ai {
namespace texsmart {
#endif

typedef struct TextNormOptions
{
    //traditional to simplified Chinese
    bool restore_case;
    bool cht_to_chs;
    bool to_lower;
    bool char_to_norm_form;

#   ifdef __cplusplus //if used by C++ code
    TextNormOptions()
    {
        Clear();
    }

    void Clear()
    {
        restore_case = false;
        cht_to_chs = false;
        to_lower = false;
        char_to_norm_form = false;
    }
#   endif
} TextNormOptions;

#define Nlu_AsciiSegMode_Simple 0
#define Nlu_AsciiSegMode_Whole 1
#define Nlu_AsciiSegMode_Std 2

typedef struct WordSegOptions
{
    bool enable;
    uint32_t ascii_seg_mode;
    bool ascii_seg_lm_mode;
    bool ascii_seg_lm_pinyin;
    bool ascii_seg_lm_comb;

    bool use_customized_spec;
    bool enable_phrase;
    bool person_as_one_word;
    bool location_as_one_word;
    bool organization_as_one_word;

#   ifdef __cplusplus //if used by C++ code
    WordSegOptions()
    {
        Clear();
    }

    void Clear()
    {
        enable = true;
        ascii_seg_mode = Nlu_AsciiSegMode_Std;
        ascii_seg_lm_mode = true;
        ascii_seg_lm_pinyin = true;
        ascii_seg_lm_comb = false;

        use_customized_spec = true;
        enable_phrase = true;
        person_as_one_word = false;
        location_as_one_word = false;
        organization_as_one_word = false;
    }
#   endif
} WordSegOptions;

typedef struct PosTaggingOptions
{
    bool enable;
    const wchar_t *alg;

#   ifdef __cplusplus //if used by C++ code
    PosTaggingOptions()
    {
        Clear();
    }

    void Clear()
    {
        enable = true;
        alg = nullptr;
    }
#   endif
} PosTaggingOptions;

typedef struct NerOptions
{
    bool enable;
    const wchar_t *alg;
    bool enable_deep_learning;
    bool enable_ne_adjustment;
    bool enable_fine_grained_ner;
    bool enable_deep_representation;

#   ifdef __cplusplus //if used by C++ code
    NerOptions()
    {
        Clear();
    }

    void Clear()
    {
        enable = true;
        alg = nullptr;
        enable_deep_learning = false;
        enable_ne_adjustment = false;
        enable_fine_grained_ner = true;
        enable_deep_representation = true;
    }
#   endif
} NerOptions;

typedef struct FnrOptions
{
    bool enable;

#   ifdef __cplusplus //if used by C++ code
    FnrOptions()
    {
        Clear();
    }

    void Clear()
    {
        enable = false;
    }
#   endif
} FnrOptions;

typedef struct SrlOptions
{
    bool enable;

#   ifdef __cplusplus //if used by C++ code
    SrlOptions()
    {
        Clear();
    }

    void Clear()
    {
        enable = false;
    }
#   endif
} SrlOptions;

typedef struct SyntacticParsingOptions
{
    bool enable;

#   ifdef __cplusplus //if used by C++ code
    SyntacticParsingOptions()
    {
        Clear();
    }

    void Clear()
    {
        enable = false;
    }
#   endif
} SyntacticParsingOptions;

typedef struct NluOptions
{
    TextNormOptions text_norm;
    WordSegOptions word_seg;
    PosTaggingOptions pos_tagging;
    NerOptions ner;
    FnrOptions fnr;
    SrlOptions srl;
    SyntacticParsingOptions syntactic_parsing;

    bool enable_additional_rule;

#   ifdef __cplusplus //if used by C++ code
    NluOptions()
    {
        Clear();
    }

    void Clear()
    {
        text_norm.Clear();
        word_seg.Clear();
        pos_tagging.Clear();
        ner.Clear();
        fnr.Clear();
        srl.Clear();
        syntactic_parsing.Clear();

        enable_additional_rule = true;
    }
#   endif
} NluOptions;

#define Nlu_TokenType_Basic 0
#define Nlu_TokenType_Number 1
#define Nlu_TokenType_Punct 2

typedef struct NluToken
{
    const wchar_t *str;
    uint32_t offset;
    uint32_t type;
} NluToken;

typedef struct NluTokenArray
{
    uint32_t size;
    const NluToken *items;
} NluTokenArray;

typedef struct NluTerm
{
    const wchar_t *str; //term string
    uint32_t offset;    //offset (character-level) in the text
    uint32_t len;       //length (number of characters)
    uint32_t start_token;
    uint32_t token_count;
    const wchar_t *tag; //part-of-speech tag
    uint32_t tag_id;    //tag id
} NluTerm;

typedef struct NluEntityType
{
    const wchar_t *name;
    const wchar_t *i18n;
    uint32_t flag;
    const wchar_t *path;
} NluEntityType;

typedef struct NluEntityTypeArray
{
    uint32_t size;
    const NluEntityType *items;
} NluEntityTypeArray;

typedef struct NluEntity
{
    const wchar_t *str; //term string
    uint32_t offset;    //offset (character-level) in the text
    uint32_t len;       //length (number of characters)
    uint32_t start_token;
    uint32_t token_count;
    NluEntityType type;
    NluEntityTypeArray alt_types;
    const wchar_t *meaning; //semantic meaning of this entity in the current context
} NluEntity;

typedef struct NluTermArray
{
    uint32_t size;
    const NluTerm *items;
} NluTermArray;

typedef struct NluEntityArray
{
    uint32_t size;
    const NluEntity *items;
} NluEntityArray;

typedef struct NluOutputMessage
{
    const wchar_t *code;
    const wchar_t *text;
} NluOutputMessage;

#ifdef __cplusplus
class TEXSMART_API NluOutput
{
public:
    NluOutput();
    virtual ~NluOutput();
    void Clear();

    const wchar_t* GetNormText(int *str_len) const;
    NluTokenArray GetTokens() const;
    NluTermArray GetWords() const;
    NluTermArray GetPhrases() const;
    NluEntityArray GetEntities() const;

    //error or warning message
    NluOutputMessage Message() const;

private:
    void *data_ = nullptr;

    //disable the copy constructor and the assignment function
    NluOutput(const NluOutput &rhs) = delete;
    NluOutput& operator = (const NluOutput &rhs) = delete;
    friend class NluEngine;
};
#endif //def __cplusplus

typedef struct TextPair
{
    const wchar_t *str1;
    const wchar_t *str2;

#   ifdef __cplusplus //if used by C++ code
    TextPair()
    {
        Clear();
    }

    void Clear()
    {
        str1 = nullptr;
        str2 = nullptr;
    }
#   endif
} TextPair;

typedef struct TextMatchingInput
{
    uint32_t size;
    TextPair *text_pair_list;
    const wchar_t *options_str;

#   ifdef __cplusplus //if used by C++ code
    TextMatchingInput()
    {
        Clear();
    }

    void Clear()
    {
        size = 0;
        text_pair_list = nullptr;
        options_str = nullptr;
    }
#   endif
} TextMatchingInput;

#ifdef __cplusplus
class TEXSMART_API TextMatchingOutput
{
public:
    TextMatchingOutput();
    virtual ~TextMatchingOutput();
    void Clear();

    uint32_t Size() const;
    float ScoreAt(uint32_t idx) const;

    //error or warning message
    NluOutputMessage Message() const;

private:
    void *data_ = nullptr;

    //disable the copy constructor and the assignment function
    TextMatchingOutput(const TextMatchingOutput &rhs) = delete;
    TextMatchingOutput& operator = (const TextMatchingOutput &rhs) = delete;
    friend class NluEngine;
};
#endif //def __cplusplus

//thread safe after initialization:
//functions ParseText and ParseUtf8Text can be called in multiple threads
#ifdef __cplusplus
class TEXSMART_API NluEngine
{
public:
    NluEngine();
    virtual ~NluEngine();
    void Clear();

    bool Init(const char *data_dir, int worker_count = 1);
    const wchar_t* Version() const;

    bool ParseText(NluOutput &output, const wchar_t *str, int len);
    bool ParseText(NluOutput &output, const wchar_t *str, int len, const wchar_t *options);
    bool ParseText(NluOutput &output, const wchar_t *str, int len, const NluOptions &opt);

    bool ParseUtf8Text(NluOutput &output, const char *str, int len);
    bool ParseUtf8Text(NluOutput &output, const char *str, int len, const char *options);
    bool ParseUtf8Text(NluOutput &output, const char *str, int len, const NluOptions &opt);

    bool MatchText(TextMatchingOutput &output, const TextMatchingInput &input) const;
    bool MatchText(TextMatchingOutput &output, const wchar_t *str1,
        const wchar_t *str2) const;
    bool MatchText(TextMatchingOutput &output, const wchar_t *str1,
        const wchar_t *str2, const wchar_t *options) const;
    bool MatchUtf8Text(TextMatchingOutput &output, const char *str1,
        const char *str2) const;
    bool MatchUtf8Text(TextMatchingOutput &output, const char *str1,
        const char *str2, const char *options) const;

private:
    void *data_ = nullptr;

private:
    //disable the copy constructor and the assignment function
    NluEngine(const NluEngine &rhs) = delete;
    NluEngine& operator = (const NluEngine &rhs) = delete;
};
#endif //def __cplusplus

typedef void* NluEngineHandle;
typedef void* NluOutputHandle;
typedef void* NluTermHandle;
typedef void* NluEntityHandle;
typedef void* NluEntityTypeHandle;
typedef void* TextMatchingOutputHandle;

TEXSMART_API NluEngineHandle Nlu_CreateEngine(const char *data_dir, int worker_count);
TEXSMART_API void Nlu_DestroyEngine(NluEngineHandle engine_handle);

TEXSMART_API void Nlu_InitOptions(NluOptions *opt);
TEXSMART_API NluOutputHandle Nlu_ParseText(NluEngineHandle engine_handle, const wchar_t *str, int len);
TEXSMART_API NluOutputHandle Nlu_ParseUtf8Text(NluEngineHandle engine_handle, const char *str, int len);
TEXSMART_API NluOutputHandle Nlu_ParseTextExt(NluEngineHandle engine_handle,
    const wchar_t *str, int len, const wchar_t *options);
TEXSMART_API NluOutputHandle Nlu_ParseUtf8TextExt(NluEngineHandle engine_handle,
    const char *str, int len, const char *options);
TEXSMART_API void Nlu_DestroyOutput(NluOutputHandle *output_handle);

TEXSMART_API const wchar_t* Nlu_GetNormText(const NluOutputHandle output_handle, int *str_len);
TEXSMART_API NluTokenArray Nlu_GetTokens(const NluOutputHandle output_handle);
TEXSMART_API NluTermArray Nlu_GetWords(const NluOutputHandle output_handle);
TEXSMART_API NluTermArray Nlu_GetPhrases(const NluOutputHandle output_handle);
TEXSMART_API NluEntityArray Nlu_GetEntities(const NluOutputHandle output_handle);

/// Get information of words or phrases, without explicitly using NluTermArray or NluTerm
TEXSMART_API uint32_t Nlu_GetWordCount(const NluOutputHandle output_handle);
TEXSMART_API const NluTermHandle Nlu_GetWord(const NluOutputHandle output_handle, uint32_t idx);
TEXSMART_API uint32_t Nlu_GetPhraseCount(const NluOutputHandle output_handle);
TEXSMART_API const NluTermHandle Nlu_GetPhrase(const NluOutputHandle output_handle, uint32_t idx);
TEXSMART_API const wchar_t* Nlu_TermStr(const NluTermHandle handle); //for a word or phrase
TEXSMART_API uint32_t Nlu_TermOffset(const NluTermHandle handle); //for a word or phrase
TEXSMART_API uint32_t Nlu_TermLen(const NluTermHandle handle); //for a word or phrase
TEXSMART_API const wchar_t* Nlu_TermTag(const NluTermHandle handle); //for a word or phrase

/// Get information of entities, without explicitly using NluEntityArray or NluEntity
TEXSMART_API uint32_t Nlu_GetEntityCount(const NluOutputHandle output_handle);
TEXSMART_API const NluEntityHandle Nlu_GetEntity(const NluOutputHandle output_handle, uint32_t idx);
TEXSMART_API const wchar_t* Nlu_EntityStr(const NluEntityHandle handle);
TEXSMART_API uint32_t Nlu_EntityOffset(const NluEntityHandle handle);
TEXSMART_API uint32_t Nlu_EntityLen(const NluEntityHandle handle);
TEXSMART_API const NluEntityTypeHandle Nlu_EntityType(const NluEntityHandle handle);
TEXSMART_API uint32_t Nlu_EntityAltTypeCount(const NluEntityHandle handle);
TEXSMART_API const NluEntityTypeHandle Nlu_EntityAltType(const NluEntityHandle handle, uint32_t idx);
TEXSMART_API const wchar_t* Nlu_EntityMeaning(const NluEntityHandle handle);
TEXSMART_API const wchar_t* Nlu_EntityTypeName(const NluEntityTypeHandle handle);
TEXSMART_API const wchar_t* Nlu_EntityTypeI18n(const NluEntityTypeHandle handle);
TEXSMART_API uint32_t Nlu_EntityTypeFlag(const NluEntityTypeHandle handle);
TEXSMART_API const wchar_t* Nlu_EntityTypePath(const NluEntityTypeHandle handle);

TEXSMART_API TextMatchingOutputHandle Nlu_MatchText(NluEngineHandle engine_handle,
    const wchar_t *str1, const wchar_t *str2, const wchar_t *options);
TEXSMART_API TextMatchingOutputHandle Nlu_MatchTextExt(NluEngineHandle engine_handle,
    const TextMatchingInput *input);
TEXSMART_API void Nlu_DestroyTextMatchingOutput(TextMatchingOutputHandle *output_handle);
TEXSMART_API uint32_t Nlu_TextMatchingOutputSize(TextMatchingOutputHandle handle);
TEXSMART_API float Nlu_TextMatchingScoreAt(TextMatchingOutputHandle handle, uint32_t idx);

#ifdef __cplusplus    //if used by C++ code
} //end of texsmart
} //end of ai
} //end of tencent
} //extern "C"
#endif
