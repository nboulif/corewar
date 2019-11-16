#.name 	FSDS				END
#.name 						ENDLINE
#.name 	fssf				INSTRUCTION
#.name"dasdas" stdsd		INSTRUCTION
#.name"dasdas" 124			INDIRECT
#.name"dasda" "sadsa"		STRING
#.name"dasda" %:dasdas		DIRECT_LABEL
#.name "dffd" %124			DIRECT
#.name"dasda" r99   			REGISTER
#.name "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"

#.name"dasda" :fef			INDIRECT_LABEL
#.name"dasda" fef:			LABEL



.name "test"
#.ds "test"
.comment"bbbbbbbbbbb" 
#.comment"bbbbbbbbbbb"

		

l2: sti r1, %:live, %1456 #dasd
		and r1,%0,r1
 
#tir:stir1,%:tirb,%1  		SEPARATOR

#.comment"bbbbbbbbbbb"

#live:	live dsdas
#live:	dsadsa
#live:	live %:llo
#live:
#live:	live %1, %1
#and r1, %0
#and r1, %0, 158
#and r1, %0, r2  live:
#

live:	live %1
		zjmp %:live

