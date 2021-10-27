
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

print('Creating and initializing the NLU engine...')
engine = NluEngine(module_dir + '/../../data/nlu/kb/', 1)

#disable fine-grained NER:
print('Options: Enable NER but disable fine-grained NER')
options = '{"ner\":{"enable":true,"fine_grained":false}}'

print('=== Parse a piece of English text ===')
output = engine.parse_text_ext("John Smith stayed in San Francisco last month.", options)
print(u'Norm text: %s' % output.norm_text())
print('Word-level segmentation results:')
for word in output.words():
    print(u'\t%s\t(%d,%d)\t%s' % (word.str, word.offset, word.len, word.tag))
print('Phrase-level segmentation results:')
for phrase in output.phrases():
    print(u'\t%s\t(%d,%d)\t%s' % (phrase.str, phrase.offset, phrase.len, phrase.tag))
print('NER results:')
for entity in output.entities():
    print(u'\t%s\t(%d,%d)\t%s\t%s' % (entity.str, entity.offset, entity.len, entity.type.name, entity.meaning))
