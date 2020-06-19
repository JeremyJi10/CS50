from cs50 import get_int

def main():
    num = get_int("Number: ")
    num_str = str(num)
    length = len(num_str)

    if checksum(num, length) % 10 != 0:
        print("INVALID")
    else:
        if length == 15 and num_str[0:2] in ["34", "37"]:
            print("AMEX")
        elif length == 16 and int(num_str[0:2]) in range(51, 56):
            print("MASTERCARD")
        elif length in [13, 16] and num_str[0] == "4":
            print("VISA")
        else:
            print("INVALID")

#check if the input satisfies Luhn’s Algorithm
def checksum(card_number, num_length):

    Luhn_sum = 0

    for i in range(1, num_length + 1):
        #get the currently last digit
        digit = card_number % 10

        if i % 2 != 0:
            Luhn_sum += digit
        else:
            Luhn_sum += digit * 2 - 9 * ((digit * 2) // 10)

        #delete the currently last digit
        card_number = (card_number - digit) / 10

    return Luhn_sum


main()