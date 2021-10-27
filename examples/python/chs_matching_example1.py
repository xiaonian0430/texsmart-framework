
#!/usr/bin/env python
#encoding=utf-8
import sys
import os.path
module_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(module_dir+'/../../lib/')
from tencent_ai_texsmart import *

print('Creating and initializing the NLU engine...')
engine = NluEngine(module_dir + '/../../data/nlu/kb/', 1)
if engine is None:
    sys.exit()

print(u'=== Text Matching ===')
str1 = u"我非常喜欢这只小狗";
str2 = u"我很爱这条狗";
output = engine.match_text(str1, str2)
if output is None or output.size() < 1:
    print(u'Error occurred in text matching')
    sys.exit()

print(u'text1: {0}'.format(str1))
print(u'text2: {0}'.format(str2))
print(u'Matching score: {0}'.format(output.score_at(0)))
