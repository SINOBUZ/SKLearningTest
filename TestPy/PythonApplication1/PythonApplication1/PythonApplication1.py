time = int(input("현재 몇 시: "))
minute = int(input("현재 몇 분: "))
increment = int(input("몇 분 뒤에 알람이 울리나요? : "))

time = time + int(increment / 60)
minute = minute + (increment % 60)
if (minute >= 60):
    time = time + 1
    minute = minute - 60
if (time >= 24):
    time = time - 24

print('{}시 {}분에 알람이 울립니다.' .format(time, minute))