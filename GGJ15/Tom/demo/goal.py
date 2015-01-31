import pygame, math
import tween


class Goal(pygame.sprite.Sprite):

	## Constructor. Pass in x, y and dir
	def __init__(self, level, x, y):
		# Call the parent class (Sprite) constructor
		pygame.sprite.Sprite.__init__(self)

		print 'Goal created ', self

		self.level = level
		self.level.add(self)
		self.birds = []

		# Create a surface for the goal
		self.image = pygame.Surface([level.cellWidth*3, level.cellWidth*3], pygame.SRCALPHA, 32)
		self.image = self.image.convert_alpha()
		self.rect = self.image.get_rect()
		self.drawGoal()
		# self.image.fill((255,255,255))

		# Fetch the rectangle object that has the dimensions of the image
		# Update the position of this object by setting the values of rect.x and rect.y
		self.moveTo(x,y)

		self.tweenQ = []
		self.setupTweens()

	def setupTweens(self):
		pass

	def drawGoal(self):
		mult = 5
		cutin = int(mult*math.sin(math.radians(pygame.time.get_ticks()/10)))
		print int(mult*math.sin(math.radians(pygame.time.get_ticks()/10)))
		self.image.fill(0)
		# pygame.draw.rect(self.image, (255,255,255), self.rect)
		self.drawGlow(mult, cutin)
		pygame.draw.ellipse(self.image, (139,69,18), (30,40,30,15 ))
		pygame.draw.ellipse(self.image, (255,215,0), (35+cutin/4,30,20,25 ))
		pygame.draw.ellipse(self.image, (139,69,18), (30,45,30,15 ))

	def drawGlow(self, mult, cutin):
		cellWidth = self.level.cellWidth
		pygame.draw.ellipse(self.image, (255,215,0,32), (mult+cutin, mult+cutin, (cellWidth*1.5-mult-cutin)*2, (cellWidth*1.5-mult-cutin)*2))
		pygame.draw.ellipse(self.image, (255,215,0,64), (mult+cutin+0.25*cellWidth, mult+cutin+0.25*cellWidth, (cellWidth*1.25-mult-cutin)*2, (cellWidth*1.25-mult-cutin)*2))
		pygame.draw.ellipse(self.image, (255,215,0,96), (mult+cutin+0.5*cellWidth, mult+cutin+0.5*cellWidth, (cellWidth*1-mult-cutin)*2, (cellWidth*1-mult-cutin)*2))
		pygame.draw.ellipse(self.image, (255,215,0,128), (mult+cutin+0.75*cellWidth, mult+cutin+0.75*cellWidth, (cellWidth*0.75-mult-cutin)*2, (cellWidth*0.75-mult-cutin)*2))
		# pygame.draw.circle(self.image, (255,215,0,32), self.rect.center, int(self.level.cellWidth*1.5) - cutin)
		# pygame.draw.circle(self.image, (255,215,0,64), self.rect.center, int(self.level.cellWidth*1.25) - cutin)
		# pygame.draw.circle(self.image, (255,215,0,96), self.rect.center, int(self.level.cellWidth*1) - cutin)
		# pygame.draw.circle(self.image, (255,215,0,128), self.rect.center, int(self.level.cellWidth*0.75) - cutin)


	def tweenFinished(self, tween):
		
		
		## If after all that we still have the original finished tween
		if tween in self.tweenQ:
			tween.restart()

	## Move so that the point is at the location specified
	def moveTo(self, x, y):
		self.rect.centerx = x
		self.rect.centery = y

	## Called by Group.update()
	def update(self, mouse):
		# self.rect.x += self.velX * self.speed
		# self.rect.y += self.velY * self.speed
		# map(lambda t: t.update(), self.tweenQ)
		self.drawGoal()


		for p in self.level.points:
			if abs(p.rect.x - self.rect.centerx) < 50 and abs(p.rect.y - self.rect.centery) < 50:
				print 'collision detected!'
				for b in p.birds:
					b.point = self
					self.birds.append(b)
				for b in self.birds:
					b.fleeing = True
				self.level.remove(p)
				self.level.points.remove(p)


	## Handle mouse clicks
	def clicked(self):
		pass