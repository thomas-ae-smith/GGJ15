#!/usr/bin/python

import re
import sys

binary_term = re.compile("(\w+)\(([\d\w]+),([\d\w]+)\)")
trinary_term = re.compile("(\w+)\(\"?([\d\w]+)\"?,([\d\w]+),([\d\w]+)\)")

def display_maze(facts):
  """turn a list of ansprolog facts into a nice ascii-art maze diagram"""
  max_x = 1
  max_y = 1
  char = {}
  
  for fact in facts:
    m = trinary_term.match(fact)
    if m:
      functor, c, x, y = m.groups()
      if functor == "charAt":
        x, y = int(x), int(y)
        pos = (x,y)
        max_x, max_y = max(x, max_x), max(y, max_y)
        print m.groups()
        char[pos] = c

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
      else:
        # print "% " + line
        pass

if __name__ == "__main__":
  main()