import pygame
import state, bird, goal, cell

class Level(state.State):

	## Constructor.
	def __init__(self, sprites):
		# Call the parent class (Group) constructor
		state.State.__init__(self, sprites)

		self.cellWidth = 30
		self.halfWidth = self.cellWidth / 2
		self.gridX = 20
		self.gridY = 20
		self.grid = pygame.sprite.Sprite()
		self.grid.image = pygame.Surface([self.gridX*self.cellWidth, self.gridX*self.cellWidth])
		self.grid.image.set_colorkey((0,0,0))
		self.grid.rect = self.grid.image.get_rect()
		self.grid.rect.x = self.grid.rect.y = self.halfWidth
		self.grid.clicked = lambda : None #dummy function for clicks when displayed
		self.birds = []
		self.points = []
		self.cells = []

		for i in xrange(0,self.gridX+1):
			pygame.draw.line(self.grid.image, (255,0,0), (i* self.cellWidth, 0), (i*self.cellWidth, self.grid.rect.bottom) )
		for i in xrange(0,self.gridY+1):
			pygame.draw.line(self.grid.image, (255,0,0), (0, i* self.cellWidth), (self.grid.rect.right, i*self.cellWidth) )


		bird1 = bird.Bird(self, 0,-1,*(self.gridToWorld(11,20)))
		bird2 = bird.Bird(self, 0,1,*(self.gridToWorld(8,0)))
		bird3 = bird.Bird(self, 1,-1,*(self.gridToWorld(0,19)))
		bird4 = bird.Bird(self, -1,1,*(self.gridToWorld(14,0)))
		bird5 = bird.Bird(self, -1,1,*(self.gridToWorld(20,0)))

		goal1 = goal.Goal(self, *(self.gridToWorld(1,11)))

		for i in xrange(1,self.gridX):
			for j in xrange(1,self.gridY):
				cell.Cell(self,[],*self.gridToWorld(i,j))

		# self.add([self.grid,bird1, bird2])


	def update(self, *args):
		# Call the parent class (Group) update
		pygame.sprite.Group.update(self, *args)

	def gridToWorld(self,x,y):
		return (self.grid.rect.x + (x * self.cellWidth) +self.halfWidth,
				self.grid.rect.y + (y * self.cellWidth) +self.halfWidth)


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