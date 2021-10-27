
#!/usr/bin/env python
#encoding=utf-8
import sys
import os.path
module_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(module_dir+'/../../lib/')
from tencent_ai_texsmart import *

print('##################################################')
print('# Example-1: Parsing text (with default options)')
print('##################################################')

print('Creating and initializing the NLU engine...')
engine = NluEngine(module_dir + '/../../data/nlu/kb/', 1)

print(u'=== 解析一个中文句子 ===')
output = engine.parse_text(u"上个月30号，南昌王先生在自己家里边看流浪地球边吃煲仔饭")
print(u'细粒度分词:')
for item in output.words():
    print(u'\t{0}\t{1}\t{2}\t{3}'.format(item.str, item.offset, item.len, item.tag))
print(u'粗粒度分词:')
for item in output.phrases():
    print(u'\t{0}\t{1}\t{2}\t{3}'.format(item.str, item.offset, item.len, item.tag))
print(u'命名实体识别（NER）:')
for entity in output.entities():
    type_str = u'({0},{1},{2},{3})'.format(entity.type.name, entity.type.i18n, entity.type.flag, entity.type.path)
    print(u'\t{0}\t({1},{2})\t{3}\t{4}'.format(entity.str, entity.offset, entity.len, type_str, entity.meaning))
