import pygame
import tween


class Point(pygame.sprite.Sprite):

	## Constructor. Pass in x, y and dir
	def __init__(self, level, birds, velX, velY, x, y):
		# Call the parent class (Sprite) constructor
		pygame.sprite.Sprite.__init__(self)

		print 'Point created ', self

		## Pseudo-constants
		self.speed = 4

		self.level = level
		self.level.add(self)
		self.level.points.append(self)

		self.birds = birds

		self.cell = None

		self.velX = velX
		self.velY = velY

		# Create a surface for the bird
		self.image = pygame.Surface([1, 1])
		self.image.fill((255,255,255))
		self.image.set_colorkey((255,255,255))

		# Fetch the rectangle object that has the dimensions of the image
		# Update the position of this object by setting the values of rect.x and rect.y
		self.rect = self.image.get_rect()
		self.moveTo(x,y)

		self.tweenQ = []
		self.setupTweens()

	def setupTweens(self):
		if self.velX and self.velY:
			self.tweenQ.append(tween.linearXTween(self, self.rect.x + self.velX*30, 1414, True))
			self.tweenQ.append(tween.linearYTween(self, self.rect.y + self.velY*30, 1414, True))	
		elif self.velX:
			self.tweenQ.append(tween.linearXTween(self, self.rect.x + self.velX*30, 1000, True))
		elif self.velY:
			self.tweenQ.append(tween.linearYTween(self, self.rect.y + self.velY*30, 1000, True))


	def tweenFinished(self, tween):
		for p in self.level.points:
			if p != self and abs(p.rect.centerx - self.rect.centerx) < 50 and abs(p.rect.centery - self.rect.centery) < 50:
				print 'collision detected!', self.velX, p.velX, self.velY, p.velY
				for b in p.birds:
					b.point = self
					self.birds.append(b)
				p.birds = []
				self.velX += p.velX
				self.velY += p.velY
				print 'after combination', self.velX, self.velY
				self.velX = max(min(1, self.velX), -1)
				self.velY = max(min(1, self.velY), -1)
				print 'after squelching', self.velX, self.velY
				for b in self.birds:
					b.rotate(self.velX,self.velY)
					b.flocking = True
				self.level.remove(p)
				self.level.points.remove(p)
				if p.cell:
					p.cell.points = []
					p.cell.fadeOut()
					p.cell = None
				self.tweenQ = []
				self.setupTweens()
		
		## If after all that we still have the original finished tween
		if tween in self.tweenQ:
			tween.restart()

	## Move so that the point is at the location specified
	def moveTo(self, x, y):
		self.rect.x = x
		self.rect.y = y

	## Called by Group.update()
	def update(self, mouse):
		# self.rect.x += self.velX * self.speed
		# self.rect.y += self.velY * self.speed
		map(lambda t: t.update(), self.tweenQ)

	## Handle mouse clicks
	def clicked(self):
		pass