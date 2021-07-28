from cs50 import get_string


def count_letters(text):
    # count letters, words, sentences
    letter = 0
    word = 0
    sentence = 0

    for c in text:
        if c.isalpha():
            letter += 1
        elif c.isspace():
            word += 1
        elif c in ['!', '?', '.']:
            sentence += 1
    if word > 0:
        word += 1

    return (letter, word, sentence)


def print_grade(index):
    # Print out grade level
    if round(index) < 1:
        print("Before Grade 1")
    elif round(index) >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def main():
    # Get input text from user
    text = get_string("Text: ")

    letter, word, sentence = count_letters(text)

    # Coleman-Liau index
    L = letter / word * 100
    S = sentence / word * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # Print out grade
    print_grade(index)


if __name__ == "__main__":
    main()