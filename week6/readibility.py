def main():
    story = input("Text: ")

    if len(story) < 1:
        print("Enter Story")
        return
    
    counts = {
        "words": 1,
        "letters": 0,
        "sentences": 0
    }

    end_of_sentence = ["!", "?", "."]

    for letter in story:
        if letter in end_of_sentence:
            counts["sentences"] += 1
        elif letter.isalpha():
            counts["letters"] += 1
        elif letter == " ":
            counts["words"] += 1

    l = (counts["letters"] / counts["words"]) * 100
    s = (counts["sentences"] / counts["words"]) * 100

    co_li_in = round(0.0588 * l - 0.296 * s - 15.8)

    if co_li_in < 1:
        print("Before Grade 1")
    elif co_li_in >= 16:
        print("Grade 16+")
    else:
        print("Grade", co_li_in)


if __name__ == "__main__":
    main()