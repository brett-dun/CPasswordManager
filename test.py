
#this file has been used for some quick debugging

str = "97 108 112 104 97 9 98 114 97 118 111 9 99 104 97 114 108 105 101 9 100 101 108 116 97 10 101 99 104 111 9 102 111 120 -79 -62 69 83 -88 74 -24 -94 -12 -116 29 91 -12 -52 -35 120".split()

for item in str:
	try:
		print( chr(int(item)) )
	except:
		print( item )