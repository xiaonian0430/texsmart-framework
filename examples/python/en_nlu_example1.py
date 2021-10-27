
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

print('=== Parse a piece of English text ===')
output = engine.parse_text(u"John Smith stayed in San Francisco last month.")
print('Word-level segmentation results:')
for word in output.words():
    print(u'\t%s\t(%d,%d)\t%s' % (word.str, word.offset, word.len, word.tag))
print('Phrase-level segmentation results:')
for phrase in output.phrases():
    print(u'\t%s\t(%d,%d)\t%s' % (phrase.str, phrase.offset, phrase.len, phrase.tag))
print('NER results:')
for entity in output.entities():
    type_str = u'({0},{1},{2},{3})'.format(entity.type.name, entity.type.i18n, entity.type.flag, entity.type.path)
    print(u'\t%s\t(%d, %d)\t%s\t%s' % (entity.str, entity.offset, entity.len, type_str, entity.meaning))
