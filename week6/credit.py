from utils import get_credit_car_num

credit_card_number = get_credit_car_num("Enter Credit Card Number: ")
credit_cards = {
    "AmericanExpress": ["34", "37"],
    "MasterCard": [str(i) for i in range(51, 56)],
    "Visa": ["4"]
}

def check_sum(credit_number):
    sum = 0
    for number in range(len(credit_number)):
        int_num = int(credit_number[number])
        if number % 2:
            sum += int_num 
        else:
            int_num = int_num * 2 if int_num * 2 < 9 else int_num * 2 - 9
            sum += int_num
    return sum

credit_sum = check_sum(credit_card_number)

if not credit_sum % 10:
    first_two = credit_card_number[:2]
    length = len(credit_card_number)
    if (length == 13 or length == 16) and first_two[0] in credit_cards["Visa"]:
        print("Visa Card")
    elif length == 15 and first_two in credit_cards["AmericanExpress"]:
        print("American Express")
    elif length == 16 and first_two in credit_cards["MasterCard"]:
        print("Master Card")
    else:
        print("Valid Credit Card Number")
else:
    print("Not Valid Credit Card Number")

