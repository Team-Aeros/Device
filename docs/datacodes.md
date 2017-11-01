# Data codes
## 1. Introduction
Transmissions sent to and by the controle room application have a specific format. Since it is easier to send numbers, all transmission have a certain prefix of 2 characters. These characters determine how the script should read the next numbers.

## 2. List of data codes
```
BINARY INSTRUCTION      ACTION                      COMPLETE
0001 xxxx               set setting                 no
0010 xxxx               roll up                     yes
0011 xxxx               roll down                   yes
0100 xxxx               report temp/light           no
0101 xxxx               ??
0110 xxxx               ??
0111 xxxx               end transmission cycle      yes
```

To begin a transmission, send ``0xFF`` (= 0b11111111). When sending an 'incomplete' transmission, you will manually have to end the transmission. You can do this by sending an empty transmission of type 0111:

``transmit(0b01110000);``

Keep in mind that 0b0111000 is ALWAYS considered an instruction. Normally, after you send an incomplete instruction, the first nibble of the following bytes is no longer considered an instruction, rather part of the value. Again, this is not the case for the exit instruction. For example:

```
transmit(0b11111111);   // Start transmission
transmit(0b00010001);   // Set setting
transmit(0b01110000);   // Attempting to set the value of setting no 1 to 0b01110000
transmit(0b01110000);   // End transmission
```

Obviously, this won't work, because the second line triggers the end of the transmission cycle.

## 3. Float
If you're dealing with float numbers, you need to send two bytes. For example:

``22.25`` is saved as 22 and 25, meaning 0b00010110 and 0b00011001. They must be sent in that order.

## 4. Examples
**Set the value of setting no 1 to 22.25:**
```
transmit(0b11111111);   // Start transmission
transmit(0b00010001);   // Set setting
transmit(0b00010110);   // = 22 In this case the first nibble is NOT an instruction
transmit(0b00011001);   // = .25
transmit(0b01110000);   // End transmission
```