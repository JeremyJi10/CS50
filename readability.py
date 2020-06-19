text = input("Text: ").lower()

letters = 0
words = 0
sentences = 0

for i in text:
    if ord(i) >= 97 and ord(i) <= 122:
        letters += 1
    if letters != 0 and i == " ":
        words += 1
    if i in ["!", ".", "?"]:
        sentences += 1

#count the last word which is not followed by a space
words += 1

read_level = 0.0588 * (letters / words * 100) - 0.296 * (sentences / (words / 100)) - 15.8

if read_level < 1:
    print("Before Grade 1")
elif read_level > 16:
    print("Grade 16+")
else:
    print(f"Grade {round(read_level)}")