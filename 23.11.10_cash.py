# Python version of Cash which asks the user how much change is owed
# then spits out the minimum number of coins


from cs50 import get_float


while True:
    change = get_float("Change owed: ")
    if change > 0:
        break


# Variables
# Additional resource: https://stackoverflow.com/questions/8725673/multiple-assignment-and-evaluation-order-in-python
total, coins = change * 100, 0

# Counts number of coins
for i in [25, 10, 5, 1]:
    while total >= i:
        total -= i
        coins += 1


# Prints out the result
print(f"{coins}")
