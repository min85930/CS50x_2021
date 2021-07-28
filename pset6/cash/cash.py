from cs50 import get_float


def main():
    # Get user input dollars
    while True:
        dollars = get_float("Change owed: ")
        if dollars >= 0:
            break

    # Convert dollars to integer
    cents = round(dollars * 100)
    coins = 0

    # Calculate minimum number of coins
    while cents != 0:
        # Greedy Algorithms
        if (cents - 25) >= 0:
            cents -= 25
        elif (cents - 10) >= 0:
            cents -= 10
        elif (cents - 5) >= 0:
            cents -= 5
        elif (cents - 1) >= 0:
            cents -= 1

        coins += 1

    print(coins)


if __name__ == "__main__":
    main()