boardX = 40
boardY = 12

birds = [{'x':0, 'y': 7, 'xVel': 1, 'yVel': 0, 'start': 0, 'char':'>'},
		 {'x':12, 'y': boardY-1, 'xVel': 0, 'yVel': -1, 'start': 8, 'char': '^'}]

def drawBoard():
	for j in range(0, boardY):
		for i in range(0, boardX):
			drawn = False
			for b in birds:
				if j == b['y'] and i == b['x']:
					if b['x'] == 12 and b['char'] == '>':
						b['char'] = '#'
						b['yVel'] = -1
						birds.pop()
					print(b['char']),
					drawn = True
			if not drawn:
				print('.'),
		print

for t in range(0,20):
	drawBoard()
	for b in birds:
		if t >= b['start']:
			b['x'] += b['xVel']
			b['y'] += b['yVel']
	hello = raw_input()


