#.name 	MY NAME					#end
#.name 							#endline
#.name 	my name 1				#instruction
#.name"my name 1" stdsd			#instruction
#.name"my name 1" 124			#indirect
#.name"my name 1" "sadsa"		#string
#.name"my name 1" %:dasdas		#direct_label
#.name "my name 1" %124			#direct
#.name "my name 1" r99   		#register
#.name "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" #too long
#.name"my name 1" :fef			#indirect_label
#.name"my name 1" fef:			#label


.name "my first name"
#.name "my second name"
#.ds "test"
.comment"first comment" 
#.comment"second comment"

		
l2:sti r1, %:live, %1456 #dasd
		and r1,%0,r1
 
#tir:stir1,%:tirb,%1  		#separator

#.comment"bbbbbbbbbbb"

#live:	live dsdas
#live:	dsadsa
#live:	live %:llo
#live:	live %2, %1
#and r1, %1
#and r1, %2, 158
#and r1, %3, r2  live:

live:	live %1
		zjmp %:live

