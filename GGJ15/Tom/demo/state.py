import pygame


class State(pygame.sprite.RenderUpdates):

	## Constructor.
	def __init__(self, sprites):
		# Call the parent class (RenderUpdates) constructor
		pygame.sprite.RenderUpdates.__init__(self, sprites)


	def update(self, *args):
		# Call the parent class (RendeUpdates) update
		pygame.sprite.RenderUpdates.update(self, *args)