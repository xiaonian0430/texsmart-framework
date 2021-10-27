
#!/usr/bin/env python
#encoding=utf-8
import sys
import os.path
module_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(module_dir+'/../../lib/')
from tencent_ai_texsmart import *

print('##################################################')
print('# Example-3: Text normalization')
print('##################################################')

print('Creating and initializing the NLU engine...')
engine = NluEngine(module_dir + '/../../data/nlu/kb/', 1)

options = '{"text_norm":{"restore_case":true},"word_seg":{"enable":false},"ner":{"enable":false}}'

print('=== Parse a piece of English text ===')
input_text = "john smith stayed in san francisco last month."
output = engine.parse_text_ext(input_text, options)

print(u'Input text: %s' % input_text)
print(u'Norm text: %s' % output.norm_text())
