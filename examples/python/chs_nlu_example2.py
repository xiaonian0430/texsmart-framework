
#!/usr/bin/env python
#encoding=utf-8
import sys
import os.path
module_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(module_dir+'/../../lib/')
from tencent_ai_texsmart import *

print('##################################################')
print('# Example-2: Parsing text using options')
print('##################################################')

print('Stdout encoding: ' + sys.stdout.encoding)
print('Creating and initializing the NLU engine...')
engine = NluEngine(module_dir + '/../../data/nlu/kb/', 1)

#disable fine-grained NER:
print('Options: Enable NER but disable fine-grained NER')
options = '{"ner\":{"enable":true,"fine_grained":false}}'

print(u'=== 解析一个中文句子 ===')
output = engine.parse_text_ext(u"上个月30号，南昌王先生在自己家里边看流浪地球边吃煲仔饭", options)
print(u'Norm text: {0}'.format(output.norm_text()))
print(u'细粒度分词:')
for item in output.words():
    print(u'\t{0}\t{1}\t{2}\t{3}'.format(item.str, item.offset, item.len, item.tag))
print(u'粗粒度分词:')
for item in output.phrases():
    print(u'\t{0}\t{1}\t{2}\t{3}'.format(item.str, item.offset, item.len, item.tag))
print(u'命名实体识别（NER）:')
for entity in output.entities():
    print(u'\t{0}\t({1},{2})\t{3}\t{4}'.format(entity.str, entity.offset, entity.len, entity.type.name, entity.meaning))
