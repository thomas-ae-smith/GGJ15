#!/usr/bin/python

import re
import sys

unary_term = re.compile("(\w+)\(([\d\w]+)\)")
binary_term = re.compile("(\w+)\(([\d\w]+),([\d\w]+)\)")
trinary_term = re.compile("(\w+)\(\"?([\d\w]+)\"?,([\d\w]+),([\d\w]+)\)")

vectors = { 'q': ('-1','-1'),
            'w': ('0','-1'),
            'e': ('1','-1'),
            'd': ('1','0'),
            'c': ('1','1'),
            'x': ('0','1'),
            'z': ('-1','1'),
            'a': ('-1','0')
            }

def output_string(facts):
  data = {'height':0, 'width':0, 'birds': [], 'goals':[], 'changes':[]}

  for fact in facts:
    if fact[0] == 'h':
      m = unary_term.match(fact)
      if m:
        functor, h = m.groups()
        if functor == 'height':
          data['height'] = h
    elif fact[0] == 'w':
      m = unary_term.match(fact)
      if m:
        functor, w = m.groups()
        if functor == 'width':
          data['width'] = w
    elif fact[0] == 'b':
      m = trinary_term.match(fact)
      if m:
        functor, x, y, v = m.groups()
        if functor == 'bird':
          data['birds'] += [x,y,vectors[v][0],vectors[v][1]]
    elif fact[0] == 'g':
      m = binary_term.match(fact)
      if m:
        functor, x, y = m.groups()
        if functor == 'goal':
          data['goals']+=[x,y]
    elif fact[0] == 'c':
      m = binary_term.match(fact)
      if m:
        functor, x, y = m.groups()
        if functor == 'change':
          data['changes']+=[x,y]

  # print data
  print data['height'], data['width'], len(data['birds'])/4, " ".join(data['birds']), len(data['changes'])/2, " ".join(data['changes']), len(data['goals'])/2, " ".join(data['goals'])
def display_maze(facts):
  """turn a list of ansprolog facts into a nice ascii-art maze diagram"""
  max_x = 8
  max_y = 8
  char = {}
  
  for fact in facts:
    m = trinary_term.match(fact)
    if m:
      functor, a, b, c = m.groups()
      if functor == "charAt":
        x, y = int(b), int(c)
        pos = (x,y)
        max_x, max_y = max(x, max_x), max(y, max_y)
        # print m.groups()
        # char[pos] = 'o' if (pos in char and char[pos] == 'o') else c
        char[pos] = a if not (pos in char) else (char[pos] if (char[pos] == 'b' or char[pos] == 'o') else a)
      elif functor == "bird":
        print 'bird', a, b, vectors[c]

  def code(x,y):
    """decide how a maze cell should be tpyeset"""
    pos = (x,y)
    if pos in char:
        return char[pos]
    else:
      return "."

  for y in range(0,max_y+1):
    print "".join([code(x,y)+' ' for x in range(0,max_x+1)])

def main():
  """look for lines that contain logical facts and try to turn each of those
  into a maze"""
  for line in sys.stdin.xreadlines():
    line = line.strip()
    if line:
      if line[0].islower():
        facts = line.split(' ')
        print facts
        display_maze(facts)
        output_string(facts)
      else:
        # print "% " + line
        pass

if __name__ == "__main__":
  main()