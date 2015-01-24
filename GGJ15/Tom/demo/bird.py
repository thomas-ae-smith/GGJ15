import pygame

BLUE = 0, 0, 255


class Bird(pygame.sprite.Sprite):

	## Constructor. Pass in x, y and dir
	def __init__(self, vel, x, y):
		# Call the parent class (Sprite) constructor
		pygame.sprite.Sprite.__init__(self)

		## Pseudo-constants
		self.speed = 4

		self.velX, self.velY = vel
		# Create a surface for the bird
		self.image = pygame.Surface([50, 50])
		self._drawBird((0,0))

		## Start asleep
		self.awake = False

		# Fetch the rectangle object that has the dimensions of the image
		# Update the position of this object by setting the values of rect.x and rect.y
		self.rect = self.image.get_rect()
		self.rect.x = x
		self.rect.y = y

	## Called by Group.update()
	def update(self, mouse):
		## Update eye to point to mouse
		## And location based on awake && vel?
		if self.awake:
			self.rect.x += self.velX * self.speed
			self.rect.y += self.velY * self.speed

	## Handle mouse clicks
	def clicked(self):
		self.awake = True

	def _drawBird(self, mouse):
		pygame.draw.polygon(self.image, BLUE, [[0,0], [40,25], [0,50], [0,38], [16,28], [16,22], [0,12]], 0)