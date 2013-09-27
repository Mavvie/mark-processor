files = [
	'main.cpp'
]

exec "g++ #{files.join " "} -o mark-processor"
