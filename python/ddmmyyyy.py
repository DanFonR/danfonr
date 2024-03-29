print("Hello! This program uses a given date to calculate which day of the week it was. It uses the Gregorian Calendar, and as such, it won't be accurate pre-1582.\n")
def d():
	while True:
		try:
			d = int(input("Please enter day: "))
			if d not in range(1, 32):
				raise Exception
		except Exception:
			print("Please enter a whole number between 1 and 31.")
		else:
			return d
d = d()
def m(d):
	m31 = [1, 3, 5, 7, 8, 10, 12]
	m30 = [4, 6, 9, 11]
	while True:
		try:
			m = int(input("Please enter month (1-12): "))
			if m not in range(1, 13):
				raise ValueError
			elif (m == 2 and d > 29) or (d > 31 and m in m31) or (d > 30 and m in m30):
				raise Exception
		except ValueError:
			print("Please enter a whole number between 1 and 12.")
		except Exception:
				print("Please enter a valid month.")
		else:
			return m
m = m(d)
def y(m, d):
	while True:
		try:
			y = int(input("Please enter year (2 digits for current century): "))
			leap = (y % 4 == 0 and (y % 400 == 0 or y % 100 != 0))
			if m == 2:
				if not leap and d > 28:
					raise ValueError
		except ValueError:
			print("The year is incompatible with day and month. Please try again")
		except Exception:
			print("Please enter a valid year.")
		else:
			return (y, leap)
y, leap = y(m, d)
twodigits = int(str(y)[-2:])
yval = (twodigits // 4 + twodigits % 7) % 7
if len(str(y)) == 2:
	y += 2000
valcor = [0, -1, -3, 2]
yval += valcor[(((y - 1900) % 400) // 100)]
mk = [1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6]
mval = mk[m - 1]
wval = (d + mval + yval) % 7
if (m == 1 or m == 2) and leap:
	wval -= 1
wday = ["saturday", "sunday", "monday", "tuesday", "wednesday", "thursday", "friday"]
print(f"That day was a {wday[wval]}.")
