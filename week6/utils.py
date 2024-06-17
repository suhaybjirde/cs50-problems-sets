def get_height(prompt):
    while True:
        try:
           height = int(input(prompt))
           if 1 <= height <= 8:
               return height
        except ValueError:
            print("The Height Should Be between 1 and 8 both included")
