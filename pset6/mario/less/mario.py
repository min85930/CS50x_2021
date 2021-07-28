from cs50 import get_int


def main():
    # Get user input height
    while True:
        height = get_int("Height: ")
        if height <= 8 and height >= 1:
            break

    # Print mario bricks
    for i in range(height):
        print(" " * (height - i - 1), end='')
        print("#" * (i + 1))


if __name__ == "__main__":
    main()
