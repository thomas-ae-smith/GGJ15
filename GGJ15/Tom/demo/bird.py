import pygame
import random, math
import point

BLUE = 0, 0, 255


class Bird(pygame.sprite.Sprite):

	angles = {(1,0):0, (1,1): 315, (0,1): 270, (-1,1): 225, (-1,0):180, (-1,-1):135, (0,-1):90, (1,-1):45, (0,0):45}

	## Constructor. Pass in x, y and dir
	def __init__(self, level, velX, velY, x, y):
		# Call the parent class (Sprite) constructor
		pygame.sprite.Sprite.__init__(self)

		## Pseudo-constants
		self.speed = 4

		self.level = level
		self.level.add(self)
		self.level.birds.append(self)
		self.velX = velX
		self.velY = velY
		# Create a surface for the bird

		self.image = pygame.Surface([level.cellWidth, level.cellWidth])
		self._drawBird(level.cellWidth)

		## Start asleep
		self.awake = False
		self.flocking = False
		self.fleeing = False
		self.free = False

		# Fetch the rectangle object that has the dimensions of the image
		# Update the position of this object by setting the values of rect.x and rect.y
		self.moveTo(x,y)

		## DEBUG: Fake a click to get things moving
		#self.clicked()

	## Move so that the point is at the location specified
	def moveTo(self, x, y):
		# self.rect.x = x - 40	##FIXME: magic numbers based on drawing code, will break
		# self.rect.y = y - 25
		self.rect.center = (x,y)

	## Called by Group.update()
	def update(self, mouse):
		## Update eye to point to mouse
		## And location based on awake && vel?
		if self.awake and hasattr(self, 'point'):
			# if not self.flocking:
			# 	self.moveTo(*(self.point.rect.topleft))
			# else:
			self.calculateFlocking()
			self.rect.x += self.velX
			self.rect.y += self.velY

		mousevecx = mouse[0] - self.rect.centerx
		mousevecy = mouse[1] - self.rect.centery

		def normalize(x,y):
			mag = math.sqrt(x*x + y*y)
			x /= mag
			y /= mag
			return (x,y)

		mousevecx,mousevecy = normalize(mousevecx,mousevecy)
		localVelX, localVelY = normalize(self.velX,self.velY)
		## dot product
		a1 = mousevecx*localVelX + mousevecy*localVelY

		a2x = mousevecx - a1*localVelX 
		a2y = mousevecy - a1*localVelY  #deliberate 

		eyevecx = a1
		eyevecy = math.sqrt(a2x*a2x + a2y*a2y)

		# print localVelX*a2y - localVelY*a2x
		eyevecy *= -1 if 0 > (localVelX*a2y - localVelY*a2x) else 1

		pygame.draw.circle(self.reference, (255,255,255), (self.rect.width/2,self.rect.height/2), 3)
		pygame.draw.circle(self.reference, (0,0,0), (self.rect.width/2+int(round(eyevecx)),self.rect.height/2+int(round(eyevecy))), 1)
		if self.fleeing or self.free or self.flocking or not self.awake:
			self.image = pygame.transform.rotate(self.reference, -math.degrees(math.atan2(self.velY, self.velX)))

	def calculateFlocking(self):

		## Move towards percieved centre of nearby birds
		v1x = v2x = v1y = v2y = 0
		xVals = [b.rect.centerx for b in self.point.birds if b != self]
		if xVals:
			v1x = ((sum(xVals) / float(len(xVals))) - self.rect.centerx)/float(1000.0)
		yVals = [b.rect.centery for b in self.point.birds if b != self]
		if yVals:
			v1y = ((sum(yVals) / float(len(yVals))) - self.rect.centery)/float(1000.0)

		if self.fleeing:
			self.free = True
			v1x *= -100
			v1y *= -100

		cx = cy = 0
		for b in self.level.birds:
		 	if b != self:
		 		dist = (b.rect.centerx - self.rect.centerx)*(b.rect.centerx - self.rect.centerx) + (b.rect.centery - self.rect.centery) * (b.rect.centery - self.rect.centery)
				if dist < 10000:
					cx -= (b.rect.centerx - self.rect.centerx) * 0.01 * 10000 / dist
					cy -= (b.rect.centery - self.rect.centery) * 0.01 * 10000 / dist

		xVels = [b.velX for b in self.point.birds if b != self]
		if xVels:
			v2x = (sum(xVels) / float(len(xVels)))/12.0
		yVels = [b.velY for b in self.point.birds if b != self]
		if yVels:
			v2y = (sum(yVels) / float(len(yVels)))/12.0

		vlim = 4
		self.velX = (self.velX * (0.7 + 0.5 * random.random())) + v1x + cx + v2x + ((self.point.rect.centerx - self.rect.centerx) / 15.0)
		if abs(self.velX) > vlim:
                        self.velX = (self.velX / abs(self.velX)) * vlim
		self.velY = (self.velY * (0.7 + 0.5 * random.random())) + v1y + cy + v2y + ((self.point.rect.centery - self.rect.centery) / 15.0)
		if abs(self.velY) > vlim:
                        self.velY = (self.velY / abs(self.velY)) * vlim


	## Handle mouse clicks
	def clicked(self):
		if not self.awake:
			self.awake = True
			pygame.draw.circle(self.reference, (255,255,255), (self.rect.width/2,self.rect.height/2), 3)
			pygame.draw.circle(self.reference, (0,0,0), (self.rect.width/2+1,self.rect.height/2), 1)
			self.image = pygame.transform.rotate(self.reference, Bird.angles[(self.velX,self.velY)])
			self.point = point.Point(self.level, [self], self.velX, self.velY, self.rect.centerx, self.rect.centery)


	def _drawBird(self, cellWidth):
		self.image.fill((255,0,255))
		# pygame.draw.polygon(self.image, BLUE, [[0,0], [40,25], [0,50], [0,38], [16,28], [16,22], [0,12]], 0)
		pygame.draw.polygon(self.image, BLUE, [[0,0], [cellWidth*0.8,cellWidth*0.5], 
												[0,cellWidth], [0,cellWidth*0.75], 
												[cellWidth*0.3,cellWidth*0.6], [cellWidth*0.3,cellWidth*0.4],
												[0,cellWidth*0.2]], 0)
		self.image.set_colorkey((255,0,255))
		self.rect = self.image.get_rect()

		pygame.draw.circle(self.image, (255,255,255), (self.rect.width/2,self.rect.height/2), 3)
		pygame.draw.circle(self.image, (0,0,0), (self.rect.width/2+1,self.rect.height/2), 1)
		self.reference = self.image.copy()
		self.rotate(self.velX, self.velY)

	def rotate(self, velX, velY):
		if velX == 0 and velY == 0:
			self.free = True
		else:
			self.image = pygame.transform.rotate(self.reference, Bird.angles[(velX,velY)])

