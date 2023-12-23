import os, sys
from time import sleep

RED = '\033[91m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
ORANGE = '\033[33m'
BLUE = '\033[94m'
PURPLE = '\033[95m'
CYAN = '\033[96m'
WHITE = '\033[97m'
END = '\033[0m'

def get_folder_size(start_path='.'):
	total_size = 0
	for dirpath, dirnames, filenames in os.walk(start_path):
		for f in filenames:
			fp = os.path.join(dirpath, f)
			total_size += os.path.getsize(fp)
	return total_size / (1024 * 1024)  # convert size to megabytes

def monitor_folder_sizes(start_path='.'):
	for dirpath, dirnames, filenames in os.walk(start_path):
		megabytes = get_folder_size(dirpath)
		path = dirpath.split('/')
		if ".git" not in path:
			print(f"{path[-1]} - Size: {megabytes:.2f} MB", end=' ')
			if megabytes > 50:
				print("%s [ALERT] %s" % (RED, END))
			else:
				print("%s [OK] %s" % (GREEN, END))


def main():
	while(1):
		os.system("clear")
		monitor_folder_sizes()
		sleep(2)

if __name__ == '__main__':
	main()