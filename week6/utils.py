def get_height(prompt):
    while True:
        try:
           height = int(input(prompt))
           if 1 <= height <= 8:
               return height
        except ValueError:
            print("The Height Should Be between 1 and 8 both included")

def get_int(prompt):
    while True:
        try: 
            number = int(input(prompt))
            if (number > 0):
                return number
        except ValueError:
            print("Enter Valid Number!")

def get_credit_car_num(prompt):
    while True:
        credit_num = input(prompt)
        if 13 <= len(credit_num) <= 16 and credit_num.isnumeric():
            return credit_num
        else:
            print("Enter A valid Credit Card Number!")