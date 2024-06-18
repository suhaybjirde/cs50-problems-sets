from utils import get_int

change_owed = get_int("Change Owed: ")
def calculate_change_owed(change_owed):
    coins = dict(quarters=0, dimes=0, nickels=0, pennies=0, total=0)
    while change_owed != 0:
        if change_owed >= 25:
            change_owed -= 25
            coins["total"] += 1
            coins["quarters"] += 1
        elif change_owed >= 10:
            change_owed -= 10
            coins["total"] += 1
            coins["dimes"] += 1
        elif change_owed >= 5:
            change_owed -= 5
            coins["total"] += 1
            coins["nickels"] += 1
        else:
            change_owed -= 1
            coins["total"] += 1
            coins["pennies"] += 1
    return coins
coins = calculate_change_owed(change_owed)
print()
for coin in coins:
    print(f"{coin}: {coins[coin]}")