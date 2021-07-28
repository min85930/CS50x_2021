from cs50 import get_int


# Luhn’s Algorithm
def Luhn(number):
    checksum = 0

    for i in range(len(number)):
        if i % 2 == 1:
            checksum += int(number[::-1][i])*2 // 10
            checksum += int(number[::-1][i])*2 % 10
        else:
            checksum += int(number[::-1][i])

    return checksum


def main():
    # Get user input number
    while True:
        number = get_int("Number: ")
        if number > 0:
            number = str(number)
            break

    # Use Luhn’s Algorithm calculate checksum
    checksum = Luhn(number)

    # calculate card length
    cardlenth = len(number)

    # Startwith 2 digits
    Start = int(number[0:2])

    # Print out Card type
    if checksum % 10 == 0:
        if cardlenth == 15 and Start in [34, 37]:
            print("AMEX")
        elif cardlenth == 16 and Start in range(51, 56):
            print("MASTERCARD")
        elif cardlenth in [13, 16] and Start//10 == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()