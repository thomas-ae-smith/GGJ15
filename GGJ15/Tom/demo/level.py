import pygame
import state, bird

class Level(state.State):

	## Constructor.
	def __init__(self, sprites):
		# Call the parent class (Group) constructor
		state.State.__init__(self, sprites)

		self.cellWidth = 50
		self.halfWidth = self.cellWidth / 2
		self.gridX = 12
		self.gridY = 12
		self.grid = pygame.sprite.Sprite()
		self.grid.image = pygame.Surface([self.gridX*self.cellWidth, self.gridX*self.cellWidth])
		self.grid.image.set_colorkey((0,0,0))
		self.grid.rect = self.grid.image.get_rect()
		self.grid.rect.x = self.grid.rect.y = self.halfWidth

		for i in xrange(0,self.gridX+1):
			pygame.draw.line(self.grid.image, (255,0,0), (i* self.cellWidth, 0), (i*self.cellWidth, self.grid.rect.bottom) )
		for i in xrange(0,self.gridY+1):
			pygame.draw.line(self.grid.image, (255,0,0), (0, i* self.cellWidth), (self.grid.rect.right, i*self.cellWidth) )


		bird1 = bird.Bird((1,0),0,0)
		bird2 = bird.Bird((1,-1),0,450)

		self.add([self.grid,bird1, bird2])


	def update(self, *args):
		# Call the parent class (Group) update
		pygame.sprite.Group.update(self, *args)

	def gridToWorld(x,y):
		return (self.grid.x + (x * self.cellWidth) +self.halfWidth,
				self.grid.y + (y * self.cellWidth) +self.halfWidth)


'''bird 0 6 (1, 0)
bird 20 5 (-1, 0)
bird 10 8 (0, -1)
bird 16 0 (-1, 1)
. . . . . . . . . . . . . . . . b . . . . 
. . . . . . . . . . . . . . . z . . . . . 
. . . . . . . . . . . . . . z . . . . . . 
. . . . . . . . . . . . . z . . . . . . . 
. . . . . . . . . . . . z . . . . . . . . 
. G a a a a a a a a a o a a a a a a a a b 
b d d d d d d d d d o . . . . . . . . . . 
. . . . . . . . . . w . . . . . . . . . . 
. . . . . . . . . . b . . . . . . . . . . '''

'''bird 0 2 (1, 0)
bird 12 5 (-1, 0)
bird 2 0 (0, 1)
bird 8 0 (0, 1)
bird 0 12 (1, -1)
bird 3 12 (1, -1)
bird 12 12 (-1, -1)
. . b . . . . . b . . . . . . . 
. . x . . . . . x . . . . . . . 
b d o . . . . . x . . . G . . . 
. . . c . . . . x . . e . . . . 
. . . . c . . . o d o . . . . . 
. . . . . c . e . . o a b . . . 
. . . . . . o . . e . . . . . . 
. . . . . e . q e . . . . . . . 
. . . . e . . e q . . . . . . . 
. . . e . . e . . q . . . . . . 
. . e . . e . . . . q . . . . . 
. e . . e . . . . . . q . . . . 
b . . b . . . . . . . . b . . . '''