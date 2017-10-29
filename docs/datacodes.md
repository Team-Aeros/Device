# Data codes
## 1. Introduction
Transmissions sent to and by the controle room application have a specific format. Since it is easier to send numbers, all transmission have a certain prefix of 2 characters. These characters determine how the script should read the next numbers.

## 2. List of data codes
```
NO            ACTION                    COMPLETE
10      =     Roll up                   yes
20      =     Roll down                 yes
30      =     Temperature               yes
40      =     Light                     yes
50      =     Set min temperature       yes
60      =     Set min light lvl         yes
70      =     Set flag                  yes
80      =     Temperature               no (second transmission = decimal part of float)
90      =     Light                     no (second transmission = decimal part of float)
11      =     Set min temperature       no (second transmission = decimal part of float)
12      =     Set min light lvl         no (second transmission = decimal part of float)
99      =     End transmission          n/a
```

When sending an 'incomplete' transmission, you will manually have to end the transmission. You can do this by sending an empty transmission of type 99:

``transmit(99, 0);``