from cs50 import get_string


def main():
    # Get user input a name
    name = get_string("What is your name?\n")
    # then say hello
    print("Hello, " + name)


if __name__ == "__main__":
    main()