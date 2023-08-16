__all__ = ['temp']

# Don't look below, you will not understand this Python code :) I don't.

from js2py.pyjs import *
# setting scope
var = Scope( JS_BUILTINS )
set_global_object(var)

# Code follows:
var.registers(['inputWords', 'fs', 'path', 'output', 'editDistance1', 'WORD_COUNTS', 'corpus', 'getWordCounts', 'correct', 'alphabet'])
@Js
def PyJsHoisted_getWordCounts_(text, this, arguments, var=var):
    var = Scope({'text':text, 'this':this, 'arguments':arguments}, var)
    var.registers(['wordsArray', 'i', 'resultObj', 'text'])
    var.put('wordsArray', var.get('text').callprop('toLowerCase').callprop('match', JsRegExp('/[a-z]+/g')))
    var.put('resultObj', Js({}))
    #for JS loop
    var.put('i', Js(0.0))
    while (var.get('i')<var.get('wordsArray').get('length')):
        try:
            if var.get('resultObj').callprop('hasOwnProperty', var.get('wordsArray').get(var.get('i'))):
                (var.get('resultObj').put(var.get('wordsArray').get(var.get('i')),Js(var.get('resultObj').get(var.get('wordsArray').get(var.get('i'))).to_number())+Js(1))-Js(1))
            else:
                var.get('resultObj').put(var.get('wordsArray').get(var.get('i')), Js(1.0))
        finally:
                (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    return var.get('resultObj')
PyJsHoisted_getWordCounts_.func_name = 'getWordCounts'
var.put('getWordCounts', PyJsHoisted_getWordCounts_)
@Js
def PyJsHoisted_editDistance1_(word, this, arguments, var=var):
    var = Scope({'word':word, 'this':this, 'arguments':arguments}, var)
    var.registers(['j', 'i', 'newWord', 'results', 'r', 'word'])
    var.put('word', var.get('word').callprop('toLowerCase').callprop('split', Js('')))
    var.put('results', Js([]))
    #for JS loop
    var.put('i', Js(0.0))
    while (var.get('i')<=var.get('word').get('length')):
        try:
            #for JS loop
            var.put('j', Js(0.0))
            while (var.get('j')<var.get('alphabet').get('length')):
                try:
                    var.put('newWord', var.get('word').callprop('slice'))
                    var.get('newWord').callprop('splice', var.get('i'), Js(0.0), var.get('alphabet').get(var.get('j')))
                    var.get('results').callprop('push', var.get('newWord').callprop('join', Js('')))
                finally:
                        (var.put('j',Js(var.get('j').to_number())+Js(1))-Js(1))
        finally:
                (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    if (var.get('word').get('length')>Js(1.0)):
        #for JS loop
        var.put('i', Js(0.0))
        while (var.get('i')<var.get('word').get('length')):
            try:
                var.put('newWord', var.get('word').callprop('slice'))
                var.get('newWord').callprop('splice', var.get('i'), Js(1.0))
                var.get('results').callprop('push', var.get('newWord').callprop('join', Js('')))
            finally:
                    (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    if (var.get('word').get('length')>Js(1.0)):
        #for JS loop
        var.put('i', Js(0.0))
        while (var.get('i')<(var.get('word').get('length')-Js(1.0))):
            try:
                var.put('newWord', var.get('word').callprop('slice'))
                var.put('r', var.get('newWord').callprop('splice', var.get('i'), Js(1.0)))
                var.get('newWord').callprop('splice', (var.get('i')+Js(1.0)), Js(0.0), var.get('r').get('0'))
                var.get('results').callprop('push', var.get('newWord').callprop('join', Js('')))
            finally:
                    (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    #for JS loop
    var.put('i', Js(0.0))
    while (var.get('i')<var.get('word').get('length')):
        try:
            #for JS loop
            var.put('j', Js(0.0))
            while (var.get('j')<var.get('alphabet').get('length')):
                try:
                    var.put('newWord', var.get('word').callprop('slice'))
                    var.get('newWord').put(var.get('i'), var.get('alphabet').get(var.get('j')))
                    var.get('results').callprop('push', var.get('newWord').callprop('join', Js('')))
                finally:
                        (var.put('j',Js(var.get('j').to_number())+Js(1))-Js(1))
        finally:
                (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    return var.get('results')
PyJsHoisted_editDistance1_.func_name = 'editDistance1'
var.put('editDistance1', PyJsHoisted_editDistance1_)
@Js
def PyJsHoisted_correct_(word, this, arguments, var=var):
    var = Scope({'word':word, 'this':this, 'arguments':arguments}, var)
    var.registers(['editDistance2Words', 'correctWord2', 'editDistance1Words', 'i', 'correctWord', 'maxCount', 'word', 'maxCount2'])
    if var.get('WORD_COUNTS').contains(var.get('word')):
        return var.get('word')
    var.put('maxCount', Js(0.0))
    var.put('correctWord', var.get('word'))
    var.put('editDistance1Words', var.get('editDistance1')(var.get('word')))
    var.put('editDistance2Words', Js([]))
    #for JS loop
    var.put('i', Js(0.0))
    while (var.get('i')<var.get('editDistance1Words').get('length')):
        try:
            var.put('editDistance2Words', var.get('editDistance2Words').callprop('concat', var.get('editDistance1')(var.get('editDistance1Words').get(var.get('i')))))
        finally:
                (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    #for JS loop
    var.put('i', Js(0.0))
    while (var.get('i')<var.get('editDistance1Words').get('length')):
        try:
            if var.get('WORD_COUNTS').contains(var.get('editDistance1Words').get(var.get('i'))):
                var.get('console').callprop('log', var.get('editDistance1Words').get(var.get('i')), var.get('WORD_COUNTS').get(var.get('editDistance1Words').get(var.get('i'))))
                if (var.get('WORD_COUNTS').get(var.get('editDistance1Words').get(var.get('i')))>var.get('maxCount')):
                    var.put('maxCount', var.get('WORD_COUNTS').get(var.get('editDistance1Words').get(var.get('i'))))
                    var.put('correctWord', var.get('editDistance1Words').get(var.get('i')))
        finally:
                (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    var.get('console').callprop('log', Js('========================================================================'))
    var.put('maxCount2', Js(0.0))
    var.put('correctWord2', var.get('correctWord'))
    #for JS loop
    var.put('i', Js(0.0))
    while (var.get('i')<var.get('editDistance2Words').get('length')):
        try:
            if var.get('WORD_COUNTS').contains(var.get('editDistance2Words').get(var.get('i'))):
                var.get('console').callprop('log', var.get('editDistance2Words').get(var.get('i')), var.get('WORD_COUNTS').get(var.get('editDistance2Words').get(var.get('i'))))
                if (var.get('WORD_COUNTS').get(var.get('editDistance2Words').get(var.get('i')))>var.get('maxCount2')):
                    var.put('maxCount2', var.get('WORD_COUNTS').get(var.get('editDistance2Words').get(var.get('i'))))
                    var.put('correctWord2', var.get('editDistance2Words').get(var.get('i')))
        finally:
                (var.put('i',Js(var.get('i').to_number())+Js(1))-Js(1))
    if (var.get('word').get('length')<Js(6.0)):
        if (var.get('maxCount2')>(Js(100.0)*var.get('maxCount'))):
            return var.get('correctWord2')
        return var.get('correctWord')
    else:
        if (var.get('maxCount2')>(Js(4.0)*var.get('maxCount'))):
            return var.get('correctWord2')
        return var.get('correctWord')
    pass
PyJsHoisted_correct_.func_name = 'correct'
var.put('correct', PyJsHoisted_correct_)
var.put('path', var.get('require')(Js('path')))
var.put('fs', var.get('require')(Js('fs')))
var.put('corpus', var.get('String')(var.get('fs').callprop('readFileSync', var.get('path').callprop('join', var.get('__dirname'), Js('./corpus')))))
var.get('console').callprop('log', Js('\nInitializing spellchecker!\n'))
pass
var.put('WORD_COUNTS', var.get('getWordCounts')(var.get('corpus')))
var.put('alphabet', Js('abcdefghijklmnopqrstuvwxyz'))
pass
pass
var.put('inputWords', var.get('process').get('argv').callprop('slice', Js(2.0)))
@Js
def PyJs_anonymous_0_(word, this, arguments, var=var):
    var = Scope({'word':word, 'this':this, 'arguments':arguments}, var)
    var.registers(['correction', 'word'])
    var.put('correction', var.get('correct')(var.get('word')))
    if PyJsStrictEq(var.get('correction'),var.get('word')):
        return ((Js(' - ')+var.get('word'))+Js(' is spelled correctly.'))
    else:
        if PyJsStrictEq(var.get('correction',throw=False).typeof(),Js('undefined')):
            return ((Js(' - ')+var.get('word'))+Js(" didn't get any output from the spellchecker."))
        else:
            return ((((Js(' - ')+var.get('word'))+Js(' should be spelled as '))+var.get('correction'))+Js('.'))
PyJs_anonymous_0_._set_name('anonymous')
var.put('output', var.get('inputWords').callprop('map', PyJs_anonymous_0_))
var.get('console').callprop('log', var.get('output').callprop('join', Js('\n\n')))
var.get('console').callprop('log', Js('\nFinished!'))
pass


# Add lib to the module scope
temp = var.to_python()