# UART_LED

Tika izmantots MSP430. UART komunikācija ir ieviesta izmantojot interupt, tādējādi nodrošinot iespēju momentāni nomainīt LED diodes stāvokli. Neēsmu vēl tik pazīstams ar MSP430 arhitektūru, bet šis bija vienīgais procesors kas bija man pieejams. UART komunikācija caur Serial monitor it kā saņēma ienākošos simbolus, taču kodā esošie if statements tomēr nemainīja LED stāvokli.
