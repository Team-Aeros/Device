# Data codes
## 1. Introduction
Transmissions sent to and by the controle room application have a specific format. Since it is easier to send numbers, all transmission have a certain prefix of 2 characters. These characters determine how the script should read the next numbers.

## 2. List of data codes
```
NO            ACTION                    COMPLETE
01      =     Roll up                   yes
02      =     Roll down                 yes
03      =     Temperature               yes
04      =     Light                     yes
05      =     Set min temperature       yes
06      =     Set min light lvl         yes
07      =     Set flag                  yes
08      =     Temperature               no (second transmission = decimal part of float)
09      =     Light                     no (second transmission = decimal part of float)
10      =     Set min temperature       no (second transmission = decimal part of float)
11      =     Set min light lvl         no (second transmission = decimal part of float)
99      =     End transmission          n/a
```

When sending an 'incomplete' transmission, you will manually have to end the transmission. You can do this by sending an empty transmission of type 99:

``transmit(99, 0);``