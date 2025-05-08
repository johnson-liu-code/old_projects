import os
import sys
import matplotlib.pyplot as plt


current_dir = os.getcwd() + '/'


comb_file_name = sys.argv[1]
coors_file_name = comb_file_name + '_coors.xyz'
bo_file_name = comb_file_name + '_bond_order.list'



a1 = sys.argv[2]
a2 = sys.argv[3]


frame_dist_a1_a2 = []

i = 0

with open(coors_file_name, 'r') as coors:
	lines = coors.readlines()

	a1_split = lines[int(a1)+2].split()
	a2_split = lines[int(a2)+2].split()

	frame_dist_a1_a2.append((i, ((float(a1_split[1])-float(a2_split[1]))**2+(float(a1_split[2])-float(a2_split[2]))**2+(float(a1_split[3])-float(a2_split[3]))**2)**(1./2)))


f = open(coors_file_name, 'r').read()
splitter = f.split('\n', 1)[0]
block = f.split('\n' + splitter + '\n')
frame_dist_a1_a2 = [(0,0)]

for b in block[1:]:
	lines = b.split('\n')
	a1_split = lines[int(a1)+1].split()
	a2_split = lines[int(a2)+1].split()

	frame_dist_a1_a2.append((i, ((float(a1_split[1])-float(a2_split[1]))**2+(float(a1_split[2])-float(a2_split[2]))**2+(float(a1_split[3])-float(a2_split[3]))**2)**(1./2)))

	i += 1



atom1 = block[0].split('\n')[int(a1)+2].split()[0]
atom2 = block[0].split('\n')[int(a2)+2].split()[0]


with open(bo_file_name, 'r') as raw:
    raw_list = raw.readlines()

bond_order = []

step_counter = 0
coord_index_correction_factor = 2

line_list = []

for line in raw_list:
	if 'frame' in line:
		line_list.append(line)


length = line_list[-1].split()[1]

fmt = '{:<2} {:>4}'
x = fmt.format(a1, a2)


for i in range(int(length)+1):	
	first_count = int(raw_list[step_counter])
	frame_list = []

	for j in range(step_counter,(step_counter + first_count + coord_index_correction_factor)):
		frame_list.append(raw_list[j])

	tick = 'reset'

	for l in frame_list:
		if x in l and atom1 in l and atom2 in l:
			bond_order.append(float(l.rsplit()[2]))
			tick = 0

	if tick == 'reset':
		bond_order.append(0)

	step_counter += int(first_count + coord_index_correction_factor)



f, d = zip(*frame_dist_a1_a2)



'''
n_name = current_dir + '/' + coors_file_name[:-10] + '_distance_and_bo_vs_frame_' + atom1 + a1 + '_' + atom2 + a2 + '.txt'

with open(n_name, 'w') as n:
	fmt = '{:<20}{:<20}{:<10}'

        n.write(fmt.format('Frame for ' + atom1 + a1 + '_' + atom2 + a2, 'Distance', 'Bond Order\n'))

        f, d = zip(*frame_dist_a1_a2)

        for i in range(len(f)):
                n.write(fmt.format(str(f[i]), str(d[i]), str(bo_values[i]) + '\n'))
'''



plt.plot(f, d, label = atom1 + a1 + ' - ' + atom2 + a2 + ' Distance')
plt.plot(f, bond_order, label = atom1 + a1 + ' - ' + atom2 + a2 +' Bond Order')


plt.xlim((0, len(f)))
plt.xlabel('Frame')
#plt.ylabel('Distance\n(Angstrom)', rotation = 0, labelpad = 40)
plt.legend(loc = 'center right')


plt.show()


#p_name = current_dir + '/' + coors_file_name[:-10] + '_distance_and_bo_vs_frame_' + atom1 + a1 + '_' + atom2 + a2 + '.png'
#plt.savefig(p_name)
