#.name 						ENDLINE
#.name"dasdas" stdsd		INSTRUCTION
#.name"dasdas" 124			INDIRECT
#.name"dasda" "sadsa"		STRING
#.name"dasda" %:dasdas		DIRECT_LABEL
#.name "dffd" %124			DIRECT
#.name"dasda" r99   			REGISTER
#.name "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"

.name "test"
#.ds "test"
.comment"bbbbbbbbbbb"
#.comment"bbbbbbbbbbb"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
