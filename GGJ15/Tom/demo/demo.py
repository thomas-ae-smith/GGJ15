import sys, pygame
import bird, level

pygame.init()

size = width, height = 650, 650
speed = [2, 2]
BLACK = 0, 0, 0
BLUE = 0, 0, 255

screen = pygame.display.set_mode(size)

## Block uninteresting events
# pygame.event.set_blocked([pygame.KEYDOWN, pygame.KEYUP])

ball = pygame.image.load("ball.bmp")
ballrect = ball.get_rect()


allSprites = level.Level([])
# birdrect = ball.get_rect()
# pygame.draw.polygon(bird, BLUE, [[0,0], [40,25], [0,50], [0,38], [16,28], [16,22], [0,12]], 0)
screen.fill(BLACK)
background = screen.copy()

while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
        if event.type == pygame.MOUSEBUTTONUP and event.button == 1: #<Event(6-MouseButtonUp {'button': 1, 'pos': (199, 53)})>
    		sprites_clicked = [sprite for sprite in allSprites if sprite.rect.collidepoint(*(event.pos))]
        	map(lambda s: s.clicked(), sprites_clicked)
    # ballrect = ballrect.move(speed)
    # if ballrect.left < 0 or ballrect.right > width:
    #     speed[0] = -speed[0]
    # if ballrect.top < 0 or ballrect.bottom > height:
    #     speed[1] = -speed[1]
    # screen.blit(ball, ballrect)
    # screen.blit(bird, birdrect)
    allSprites.update((0,0))
    allSprites.clear(screen, background)
    updates = allSprites.draw(screen)
    pygame.display.update(updates)


