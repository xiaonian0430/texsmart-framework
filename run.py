# encoding: utf-8
"""
@author: Xiao Nian
@contact: xiaonian030@163.com
@time: 2019-12-31 14:00
"""

import sys
import os.path
import uuid
from config.config import HTTP_SERVER
from flask import Flask, jsonify, request

module_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(module_dir + '/lib/')
from tencent_ai_texsmart import *

print('Creating and initializing the NLU engine...')
engine = NluEngine(module_dir + '/data/nlu/kb/', 1)
if engine is None:
    sys.exit()

app = Flask(__name__)
app.debug = False
app.config['JSON_AS_ASCII'] = False


@app.route("/sim")
def sim():
    text_one = request.args.get('text_1', default='')
    text_two = request.args.get('text_2', default='')
    output = engine.match_text(text_one, text_two)
    score = float(output.score_at(0))
    if score < 0:
        score = 0
    return jsonify({
        "score": score,
        "texts": {
            "text_1": text_one,
            "text_2": text_two
        },
        "log_id": str(uuid.uuid1())
    })


if __name__ == '__main__':
    app.run(host=HTTP_SERVER['host'], port=HTTP_SERVER['port'])
