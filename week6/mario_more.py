from utils import get_height

height = get_height("Height: ")

for i in range(1, height + 1):
    loop = height + i + 2
    for j in range(loop, 0, -1):
        # i bet you will never understand this! hhhh 
        # even i my self may not understand it if i come to this sometime in the future
        if j <= (i * 2) + 2 - (i) and j > (i * 2) + 2 - (i) - 2:
            print(" ", end="")
        elif j <= (i * 2) + 2:
            print("#", end="")
        else:
            print(" ", end="")
    print()
    
