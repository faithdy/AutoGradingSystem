import sys

file1 = sys.argv[1]
file2 = sys.argv[2]

f1 = open(file1, 'r')
f2 = open(file2, 'r')

list1 = []
list2 = []

for l in f1.readlines():
	list1.append(l.split('/')[2])

for l in f2.readlines():
	list2.append(l.split('/')[2])


result = [l1 for l1 in list1 if l1 not in list2]

print(len(result))
print(result)




f1.close()
f2.close()

