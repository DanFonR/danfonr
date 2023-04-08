#this program uses the gregorian calendar
#can be used for any year between 1000 ce and 2099 ce
d = int(input("enter day:"))
m = int(input("enter month:"))
y = int(input("enter year:"))

if y == 0:
	y = 2021

if m not in range(1, 13):
	print("invalid month.")
elif (m == 1 or m == 3 or m == 5 or m == 7 or m == 8 or m == 10 or m == 12) and d not in range(1, 32):
	print("invalid day")
elif (m == 4 or m == 6 or m == 9 or m == 11) and d not in range(1, 31):
	print("invalid day")
elif m == 2:
	if (y % 4 == 0 and (y % 400 == 0 or y % 100 != 0)) and d not in range(1, 30):
		print("invalid day")
	elif d not in range(1, 29):
		print("invalid day")
else:
	t = y - ((y // 100) * 100)
	key = (t // 4 + t % 7) % 7
	if y in range(1900, 2000):
		key = key
	elif y in range(2000, 2100):
		key -= 1
		if key == -1:
			key = 6
	elif y in range(1800, 1900):
		key += 2
		if key == 7:
			key = 0
		elif key == 8:
			key = 1
	elif y in range(1700, 1800):
		key -= 3
		if key == -3:
			key = 4
		elif key == -2:
			key = 5
		elif key == -1:
			key = 6
	elif y in range(1600, 1700):
		key -= 1
		if key == -1:
			key = 6
	elif y in range(1500, 1600):
		key = key
	elif y in range(1400, 1500):
		key += 2
		if key == 7:
			key = 0
		elif key == 8:
			key = 1
	elif y in range(1300, 1400):
		key -= 3
		if key == -3:
			key = 4
		elif key == -2:
			key = 5
		elif key == -1:
			key = 6
	elif y in range(1200, 1300):
		key -= 1
		if key == -1:
			key = 6
	elif y in range(1100, 1200):
		key = key
	elif y in range(1000, 1100):
		key += 2
		if key == 7:
			key = 0
		elif key == 8:
			key = 1

	if m == 1 or m == 10:
		n = 1
	elif m == 2 or m == 3 or m == 11:
		n = 4
	elif m == 4 or m == 7:
		n = 0
	elif m == 5:
		n = 2
	elif m == 6:
		n = 5
	elif m == 8:
		n = 3
	elif m == 9 or m == 12:
		n = 6

	wday = (d + n + key) % 7
	if (m == 1 or m == 2) and (y % 4 == 0 and (y % 400 == 0 or y % 100 != 0)):
		wday -= 1
	else:
		wday = wday
	if wday == 0:
		print("saturday")
	elif wday == 1:
		print("sunday")
	elif wday == 2:
		print("monday")
	elif wday == 3:
		print("tuesday")
	elif wday == 4:
		print("wednesday")
	elif wday == 5:
		print("thursday")
	elif wday == 6:
		print("friday")