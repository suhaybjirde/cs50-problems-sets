from utils import get_height

height = get_height("Height: ")
for i in range(1, height + 1):
    for j in range(height, 0, -1):
        if j <= i:
            print("#", end="")
        else:
            print(" ", end="")
    print()
     