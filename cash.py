from cs50 import get_float

# initialize total change and get input
total = 0
amount = get_float("Change owed: ")
cents = int(amount * 100)
denomination = [1, 5, 10, 25]


def main():
    # calling function to calculate change count and printing the result
    result = change_owed(cents)
    print(result)


def denom(cents):
    # returns the coin denomination
    return denomination.pop()


def change_owed(cents):
    # returns the total count of change
    global total
    if cents == 0:
        return total
    den = denom(cents)
    count = cents // den
    total += count
    # calculating the remain cents
    cents = cents - (count * den)
    # calling function recursively
    return change_owed(cents)


if __name__ == "__main__":
    main()