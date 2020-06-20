while True:

    height = input("Height: ")

    try:
        h_int = int(height)

        # check if user typed an integer in required range
        if h_int in range(1, 9) and len(height) == 1:
            for i in range(1, h_int + 1):
                print(" " * (h_int - i) + i * "#" + "  " + i * "#")

            # if user's input is valid, exit the program after printing the pyramid
            break

        else:
            continue

    except:
        continue