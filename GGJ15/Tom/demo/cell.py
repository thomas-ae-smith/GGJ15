import pygame
import tween


class Cell(pygame.sprite.Sprite):

	## Constructor. Pass in x, y and dir
	def __init__(self, level, points, x, y):
		# Call the parent class (Sprite) constructor
		pygame.sprite.Sprite.__init__(self)

		# print 'Cell created ', self

		self.level = level
		self.level.add(self)
		self.level.cells.append(self)

		self.points = points
		self.alpha = 0
		self.fading = False

		# Create a surface for the bird
		self.image = pygame.Surface([level.cellWidth,level.cellWidth])
		# self.image = self.image.convert_alpha()
		self.rect = self.image.get_rect()
		self.image.fill((255,0,255))
		self.image.set_colorkey((255,0,255))
		pygame.draw.circle(self.image,(255,255,255), self.rect.center, level.halfWidth)
		self.image.set_alpha(self.alpha)

		# Fetch the rectangle object that has the dimensions of the image
		# Update the position of this object by setting the values of rect.x and rect.y
		self.moveTo(x,y)

		self.tweenQ = []
		self.setupTweens()

	def setupTweens(self):
		pass


	def tweenFinished(self, tween):
		# for p in self.level.points:
		# 	if p != self and abs(p.rect.x - self.rect.x) < 50 and abs(p.rect.y - self.rect.y) < 50:
		# 		print 'collision detected!', self.velX, p.velX, self.velY, p.velY
		# 		for b in p.birds:
		# 			b.point = self
		# 			self.birds.append(b)
		# 		self.velX += p.velX
		# 		self.velY += p.velY
		# 		print 'after combination', self.velX, self.velY
		# 		self.velX = max(min(1, self.velX), -1)
		# 		self.velY = max(min(1, self.velY), -1)
		# 		print 'after squelching', self.velX, self.velY
		# 		for b in self.birds:
		# 			b.rotate(self.velX,self.velY)
		# 			b.flocking = True
		# 		self.level.remove(p)
		# 		self.level.points.remove(p)
		# 		self.tweenQ = []
		# 		self.setupTweens()
		
		# ## If after all that we still have the original finished tween
		if tween in self.tweenQ:
			print 'finished fading'
			self.fading = False
			self.tweenQ.remove(tween)
			if self.tweenQ and not self.tweenQ[0].active:
				self.tweenQ[0].active = True
		# 	tween.restart()
		pass

	## Move so that the point is at the location specified
	def moveTo(self, x, y):
		self.rect.centerx = x
		self.rect.centery = y

	def fadeOut(self):
		print 'trying to fade out'
		self.tweenQ.append(tween.linearATween(self, 0, 1000, not self.fading))
		if not self.fading:
			print 'fading out'
			self.fading = True
	
	def fadeIn(self):
		if not self.fading:
			self.fading = True
			self.tweenQ.append(tween.linearATween(self, 128, 1000, True))

	## Called by Group.update()
	def update(self, mouse):
		# self.rect.x += self.velX * self.speed
		# self.rect.y += self.velY * self.speed
		if self.alpha and not self.points:
			self.fadeOut()
		if self.fading:
			self.image.set_alpha(self.alpha)
		# if self.rect.collidepoint(mouse):
		# 	self.fadeIn()
		map(lambda t: t.update(), self.tweenQ)
		for p in self.level.points:
			if self.rect.collidepoint(p.rect.center) and p not in self.points:
				self.points.append(p)
				self.fadeIn()
				p.cell = self
		for p in self.points:
			if not self.rect.collidepoint(p.rect.center) or not p.birds:
				self.points.remove(p)
				self.fadeOut()
				p.cell = None

	## Handle mouse clicks
	def clicked(self):
		pass