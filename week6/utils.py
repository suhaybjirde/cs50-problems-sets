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