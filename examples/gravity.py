"""Showcase of a elastic spiderweb (drawing with pyglet)

It is possible to grab one of the crossings with the mouse
"""

__version__ = "$Id:$"
__docformat__ = "reStructuredText"

import math

import pyglet

import pymunk
from pymunk.vec2d import Vec2d

config = pyglet.gl.Config(sample_buffers=1, samples=2, double_buffer=True)
window = pyglet.window.Window(config=config, vsync = False)
space = pymunk.Space()

space.gravity = 0,0

c = Vec2d(window.width /2., window.height / 2.)
cb = pymunk.Body(1,1)
cb.mass = 1
cb.position = c

x = Vec2d(window.width /4., window.height / 4.)
xb = pymunk.Body(1,1)
xb.mass = 1
xb.position = x
xb.velocity = 15,-4

space.add(cb)
space.add(xb)
j = pymunk.Gravitation(cb, xb, 1e4)
space.add(j)

### ALL SETUP DONE

def update(dt):
    # Note that we dont use dt as input into step. That is because the
    # simulation will behave much better if the step size doesnt change
    # between frames.
    r = 10
    for x in range(r):
        space.step(1./30./r)

pyglet.clock.schedule_interval(update, 1/30.)

selected = None
selected_joint = None

fps_display = pyglet.clock.ClockDisplay()

@window.event
def on_draw():
    pyglet.gl.glClearColor(240,240,240,255)
    window.clear()

    fps_display.draw()

    # web crossings / bodies
    pyglet.gl.glColor3f(.8,0,0)
    a = []
    for b in [cb, xb]:
        a += [b.position.x, b.position.y]
    pyglet.gl.glPointSize(5)
    pyglet.graphics.draw(len(a)//2, pyglet.gl.GL_POINTS, ('v2f',a))

pyglet.app.run()
