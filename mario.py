from cs50 import get_int

# checking user input for non negative height

while True:
    height = get_int("Height: ")
    if height >= 0 and height <= 23:
        break

# initializing number of space and brick in pyramid

column = height + 1
space = column - 2
brick = column - space
row = 1

# printing pyrmaid for a given height

if height > 0:
    while True:
        print(" " * space, end="")
        print("#" * brick)
        row += 1
        space -= 1
        brick += 1
        if row > height:
            break
else:
    print(end="")