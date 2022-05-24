import board
import analogio
import time

# Built-in light sensor allows for easy reading of light level.
pin = analogio.AnalogIn(board.A7)

def getRes():
    # A high light value (such as a laser) will return above 64 000.
    if (pin.value > 64000):
        return 1
    return 0

# Clear the Screen
print("\n\n\n\n\n\n\n\n\n\n\n\n")

# Save the phrase to a list so that it can all be printed in one line at the end.
phrase = []


while True:
    res = getRes()
    if (res == 1):
        time.sleep(0.11) # Wait for a bit then begin the listening process.
        byte = [] # Variable to store the byte.
        for _ in range(8): # Each byte is 8 bits.
            byte.append(getRes())
            time.sleep(0.05)
        byte_str = ""
        for bit in byte:
            byte_str += str(bit)
        byte_int = int(byte_str,2) # Convert the byte to an integer and then into a character according to ASCII rules.
        if (byte_int == 10):  # 10 is the end byte (just something that Arduinos do automatically), show the saved phrase.
            print("".join(phrase))
            phrase = [] # Clear the phrase for the next phrase.
        else:
            phrase.append(chr(byte_int))
        time.sleep(0.75) # The Arduino will wait for a bit before listening for the next byte.