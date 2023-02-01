
from manim import *


class SquareToCircle(Scene):
    def construct(self):
        circle = Circle()  # create a circle
        circle.set_fill(PINK, opacity=0.5)  # set color and transparency

        square = Square()  # create a square
        square.rotate(PI / 4)  # rotate a certain amount

        self.play(Create(square), run_time=3)  # animate the creation of the square
        self.play(Transform(square, circle), run_time=2)  # interpolate the square into the circle
        self.play(FadeOut(square), run_time=3)  # fade out animation
