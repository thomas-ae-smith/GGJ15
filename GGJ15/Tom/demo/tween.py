import pygame

class Tween:

	def __init__(self, target, targetValue, timeMillis, active=False):
		self.target = target
		self.getStartValue()
		self.targetValue = targetValue
		self.startTime = pygame.time.get_ticks()
		self.duration = timeMillis
		self.active = active
		print 'New Tween here'

	def update(self):
		if not self.active:
			return
		timePassed = pygame.time.get_ticks() - self.startTime
		if timePassed > self.duration:
			self.finishTween()
			active = False
			if hasattr(self.target, 'tweenFinished'):
				print 'Calling callback'
				self.target.tweenFinished(self)
		else:
			self.updateFunction(timePassed)

	def restart(self):
		diff = self.targetValue - self.startValue
		self.getStartValue()
		self.targetValue = self.startValue + diff
		self.startTime = pygame.time.get_ticks()
		self.active = True

class linearXTween(Tween):

	def getStartValue(self):
		self.startValue = self.target.rect.x

	def updateFunction(self, timePassed):
		self.target.rect.x = self.startValue + (timePassed / float(self.duration)) * (self.targetValue - self.startValue)

	def finishTween(self):
		self.target.rect.x = self.targetValue

class linearYTween(Tween):

	def getStartValue(self):
		self.startValue = self.target.rect.y

	def updateFunction(self, timePassed):
		self.target.rect.y = self.startValue + (timePassed / float(self.duration)) * (self.targetValue - self.startValue)

	def finishTween(self):
		self.target.rect.y = self.targetValue

class linearATween(Tween):

	def getStartValue(self):
		self.startValue = self.target.alpha

	def updateFunction(self, timePassed):
		self.target.alpha = self.startValue + (timePassed / float(self.duration)) * (self.targetValue - self.startValue)

	def finishTween(self):
		self.target.alpha = self.targetValue
