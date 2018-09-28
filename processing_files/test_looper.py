
data = [ [0, 1], [1, 1] ]
pressure_list = ['100', '200']
radii_list = ['.1', '.2', '.3']


for c, pressure in enumerate(pressure_list):
    #done = False
    #end_loop = False
    for i in radii_list:
        print 'pressure: ', pressure, ' radii: ', i
        #if end_loop == True:
        #    break
        #while done == False:
        #    if data[c][0] == data[c][1]:
        #        end_loop = True
        #    done = True
