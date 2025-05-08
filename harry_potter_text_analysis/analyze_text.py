# -*- coding: utf-8 -*-
"""

"""


#import numpy as np
import string



'''
########################################################################
Instructions from Christina ...

Project 1:
-------------
Please find the text from all of the Harry Potter novels. If Harry Potter is boring find another book series to do this with.

1) I want to know what the word count is for the total number of words. 
2) I want to know what is the word count for the total number of individual words. 
3) Words should be listed alphabetically, and by occurrence from greatest to smallest. 
########################################################################
'''


########################################################################
# Text source:
# https://github.com/formcept/whiteboard/blob/master/nbviewer/notebooks/data/harrypotter
########################################################################

text_file_name = 'books/01-The_Philosophers_Stone.txt'

with open( text_file_name, encoding = 'utf8' ) as text_file:
    raw_lines = text_file.readlines()


'''
########################################################################
20230725
------------------------------------------------------------------------
Johnson - The text file that I used is 'missing' some pages so keep that
          in mind when trying to work with page numbers and the number
          of pages.
########################################################################


page_lines = [ line for line in raw_lines if 'Harry Potter and the Philosophers Stone - J.K. Rowling' in line ]
#print( len( page_lines ) )
#print( page_lines )

page_numbers = np.array( [ int( line.split()[ 2 ] ) for line in page_lines ] )
#print(page_numbers)
#print( len( page_numbers ) )
#arr = np.arange( 2, 348 )
#print(arr)
#print( arr - page_numbers)

add_shift = 1

missing_numbers_list = [ ]

for num, number in enumerate( page_numbers ):
    if number != num + add_shift:
        missing_numbers_list.append( num + add_shift )
        add_shift = add_shift + 1


print( missing_numbers_list )
'''


#print( len( raw_lines ) )

lines_without_page_footnote = [ line for line in raw_lines if 'Harry Potter and the Philosophers Stone - J.K. Rowling' not in line ]

#print( len( lines_without_page_footnote ) )

#print( lines_without_page_footnote[1] )

non_empty_lines = [ line.strip('"') for line in lines_without_page_footnote if line.strip() ]

#print( len( non_empty_lines ) )

processed_lines = non_empty_lines[ 1: ]
#print( processed_lines[ :100 ] )

word_dict = {}

#for line in processed_lines[ :4 ]:
for line in processed_lines:
    word_list = [ word.lower() for word in line.split() ]
    #print( word_list )
    for word in word_list:
        word = word.translate( str.maketrans( '', '', string.punctuation ) )
        word = word.translate( str.maketrans( '', '', '.,!;:?' ) )
        
        if word not in word_dict:
            word_dict[ word ] = 1
            
        else:
            word_dict[ word ] += 1

#print( word_dict )

total_number_of_unique_words = sum( word_dict.values() )

print( total_number_of_unique_words )

sorted_word_dict_by_key = dict( sorted( word_dict.items() ) )

sorted_word_dict_by_value = sorted( word_dict, key = word_dict.get, reverse = True )




