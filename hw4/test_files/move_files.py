import os, sys

starting_file_number = 5
last_file_number = 26
down_shift = 2
file_extension = '.in'

for i in range (starting_file_number, last_file_number):
	os.system('mv test' + str(i) + file_extension + ' test' + str(i - down_shift) + file_extension)