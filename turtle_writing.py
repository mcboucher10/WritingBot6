import turtle, math

screen = turtle.Screen()
screen.title("Turtle Writing Bot")

scale = 5

t = turtle.Turtle()
t.speed = 10

letters = [
    # A
    "P1L2F3R2F4L2F2L1D1L1F2L1D1L1F2L2F4R2F3P0L2F1",

    # B
    "L2P1F6R2F3R1D1R1F1R1D1R1F3L4F3R1D1R1F1R1D1R1F3P0R4F5",

    # C
    "F4L4P1F3R1D1R1F4R1D1R1F3P0R2F6L2F1",

    # D
    "L2P1F6R2F3R1D1R1F4R1D1R1F3P0R4F5",

    # E
    "L2P1F6R2F4R4F4L2F3L2F3R4F3L2F3L2F4P0F1",

    # F
    "L2P1F6R2F4R4F4L2F3L2F3P0R2F3L2F2",

    # G
    "F4L2F6L2P1F3L1D1L1F4L1D1L1F2L1D1L1F1L2F2P0L2F2L2F3"
]
    
def pendown():
    t.pendown()

def penup():
    t.penup()

def forward(distance):
    t.forward(distance * scale)

def left(angle):
    deg = angle * 180 / math.pi
    t.left(deg)

def right(angle):
    deg = angle * 180 / math.pi
    t.right(deg)

# ------------------------------------------------------------------------

def point_to_point(rotation,p0,p1):
    dx = p1[0] - p0[0]
    dy = p1[1] - p0[1]

    dist = math.hypot(dx,dy)
    angle = math.atan2(dy,dx)
    delta = angle - rotation
    delta = (delta + math.pi) % (2*math.pi) - math.pi

    left(delta)
    forward(dist)

    return angle

def write_letter(letter):
    commands = letters[ord(letter) - ord('A')]
    for i in range(0,len(commands),2):
        command = commands[i:i+2]
        strength = int(command[1])
        if command[0] == 'L':
            left(math.pi / 4 * strength)
        elif command[0] == 'R':
            right(math.pi / 4 * strength)
        elif command[0] == 'F':
            forward(strength)
        elif command[0] == 'D':
            forward(1.41 * strength)
        elif command == 'P1':
            pendown()
        elif command == "P0":
            penup()

penup()

for letter in input("Enter text to write: ").upper():
    write_letter(letter)

turtle.done()
